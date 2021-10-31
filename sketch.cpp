/*
This program is based on (1) and (2).

(1)BeeBotte Arduino tutorial
https://github.com/beebotte/bbt_arduino_examples
LICENSE: MIT

(2)赤外線リモコンの送信をしてみる by hamayan
http://tool-cloud.renesas.com/ja/atelier/detail.php?id=36
LICENSE: (Original Copyright as follows)
*/

/*

Infra-red IR-remote capture program version 1.0
by Kaz Kinoshita, Insutitute of Daiichi Technologies
date of 2014-10-23

*/
/* ------------------------------------------------------------------------ */
/* 赤外線リモコンの送信をしてみる                                           */
/*                                             designed by hamayan          */
/*                                             Copyright(C) hamayan         */
/*                                             since 2004 - 2016            */
/* ------------------------------------------------------------------------ */

/* ---------- */
/* DEFINITION */
/* ---------- */
#include <Arduino.h>

/* == for BeeBotte == */
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Wifi Settings
char ssid[] =    "";                   // Network SSID
char pass[] =    "";                   // Network password
int  status =    WL_IDLE_STATUS;       // the Wifi radio's status

// Broker Setting
#define BBT      "mqtt.beebotte.com"   // Domain name of Beebotte MQTT service
#define TOKEN    ""                    // Channel token for "MySmartHome"
#define CHANNEL  "MySmartHome"
#define RESOURCE "voice"

// IrSend PIN
#define IR_CONT  3                       // Ir LED ON/OFF

// Target IR data.
const unsigned char TVOnOff[] =    {0x40, 0xbf, 0x12, 0xed};

// Initialize the Ethernet client object
WiFiEspClient espClient;
PubSubClient  client(espClient);

void onMessage(char*, byte*, unsigned int);
boolean reconnect();
int  lastReconnectAttempt;

/* == for IR-SEND == */
#if !defined( _MULTITASK_H_ )
#define  dly_tsk(tim)  delay(tim)
#define  rot_rdq()
#define  loc_cpu()     interrupts()
#define  unl_cpu()     noInterrupts()
#endif /*_MULTITASK_H_ */

void irRemocon_txNEC(const byte data[], unsigned int sz);
void irRemocon_txAEHA(const byte data[], unsigned int sz);


/* ---------- */
/*  SETUP()   */
/* ---------- */

void setup()
{
  // initialize serial for debugging
  Serial.begin( 9600 );

/* == for BeeBotte == */

  // initialize serial for ESP module
  Serial6.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial6);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  client.setServer(BBT, 1883);
  // Set the on message callback
  // onMesage function will be called
  // every time the client received a message
  client.setCallback(onMessage);

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

  lastReconnectAttempt = 0;

/* == for IR-SEND == */

  analogWriteFrequency((uint32_t)38 * 1000);  //set IR carrier

}


/* ---------- */
/*   LOOP()   */
/* ---------- */

void loop()
{
 if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    delay(50);
    client.loop();
  }
}

char *itoh( char *dst, unsigned int value )
{
  sprintf( dst, "%02x", value );

  return dst;
}

/* ---------------------- */
/*  BeeBotte onMessage()  */
/* ---------------------- */

void onMessage(char* topic, byte* payload, unsigned int length) {
  // decode the JSON payload
  StaticJsonDocument<256> doc;

  // Test if parsing succeeds.
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  
  const char* room   = doc["data"][0]["room"];
  const char* device = doc["data"][0]["device"];
  const char* action = doc["data"][0]["action"];

  Serial.print("room  :");
  Serial.println(room);
  Serial.print("device:");
  Serial.println(device);
  Serial.print("action:");
  Serial.println(action);

  if( strcmp(room, "living") ){
    Serial.println("No action - not living");
    return;
  }

  if( strncmp (device, "テレビ", 3 ) ){
    Serial.println("No action - not TV");
    return;
  }

  // Send TV-ON
  Serial.println("TV on.");
  irRemocon_txNEC( TVOnOff, sizeof(TVOnOff) );
}


//A utility function to generate random ID for the MQTT connection
const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char id[17];

const char * generateID()
{
  randomSeed(analogRead(0));
  int i = 0;
  for(i = 0; i < sizeof(id) - 1; i++) {
    id[i] = chars[random(sizeof(chars))];
  }
  id[sizeof(id) -1] = '\0';

  return id;
}


// reconnects to Beebotte MQTT server
boolean reconnect() {
  if (client.connect(generateID(), TOKEN, "")) {
    char topic[64];
    sprintf(topic, "%s/%s", CHANNEL, RESOURCE);
    client.subscribe(topic);

    Serial.println("Connected to Beebotte MQTT");
  }
  return client.connected();
}


/*************************************************************************/
/* NECタイプのデータ送信                                                 */
/*************************************************************************/
void irRemocon_txNEC(const byte data[], unsigned int sz)
{
//#define T_VALUE  562UL
#define T_VALUE  555UL
#define PPM_ON   170
#define PPM_OFF  255

  loc_cpu();
  analogWrite(IR_CONT,0);
  //frame ppm on
  analogWrite(IR_CONT,PPM_ON);
  delayMicroseconds(T_VALUE * 16);  //16T
  //frame ppm off
  analogWrite(IR_CONT,PPM_OFF);
  delayMicroseconds(T_VALUE * 8);  //8T

  for(int i = 0; i < sz; i++)
  {
    byte temp = data[i];
    for(int j = 0; j < 8; j++)
    {
      if(temp & 0x01)
      {
        //frame ppm on
        analogWrite(IR_CONT,PPM_ON);
        delayMicroseconds(T_VALUE * 1);  //1T
        //frame ppm off
        analogWrite(IR_CONT,PPM_OFF);
        delayMicroseconds(T_VALUE * 3);  //3T
      }
      else
      {
        //frame ppm on
        analogWrite(IR_CONT,PPM_ON);
        delayMicroseconds(T_VALUE * 1);  //1T
        //frame ppm off
        analogWrite(IR_CONT,PPM_OFF);
        delayMicroseconds(T_VALUE * 1);  //1T
      }
      temp >>= 1;
    }
  }

  //stop bit
  //frame ppm on
  analogWrite(IR_CONT,PPM_ON);
  delayMicroseconds(T_VALUE * 1);  //1T
  //frame ppm off
  analogWrite(IR_CONT,PPM_OFF);
  unl_cpu();
}

/*************************************************************************/
/* AEHAタイプのデータ送信                                                */
/*************************************************************************/
void irRemocon_txAEHA(const byte data[], unsigned int sz)
{
#undef T_VALUE
#define T_VALUE  425UL
//#define PPM_ON   170  //170
//#define PPM_OFF  255

  loc_cpu();
  analogWrite(IR_CONT,0);
  //frame ppm on
  analogWrite(IR_CONT,PPM_ON);
  delayMicroseconds(T_VALUE * 8);  //8T
  //frame ppm off
  analogWrite(IR_CONT,PPM_OFF);
  delayMicroseconds(T_VALUE * 4);  //4T

  for(int i = 0; i < sz; i++)
  {
    byte temp = data[i];
    for(int j = 0; j < 8; j++)
    {
      if(temp & 0x01)
      {
        //frame ppm on
        analogWrite(IR_CONT,PPM_ON);
        delayMicroseconds(T_VALUE * 1);  //1T
        //frame ppm off
        analogWrite(IR_CONT,PPM_OFF);
        delayMicroseconds(T_VALUE * 3);  //3T
      }
      else
      {
        //frame ppm on
        analogWrite(IR_CONT,PPM_ON);
        delayMicroseconds(T_VALUE * 1);  //1T
        //frame ppm off
        analogWrite(IR_CONT,PPM_OFF);
        delayMicroseconds(T_VALUE * 1);  //1T
      }
      temp >>= 1;
    }
  }

  //stop bit
  //frame ppm on
  analogWrite(IR_CONT,PPM_ON);
  delayMicroseconds(T_VALUE * 1);  //1T
  //frame ppm off
  analogWrite(IR_CONT,PPM_OFF);
  unl_cpu();
  dly_tsk(10);
}
