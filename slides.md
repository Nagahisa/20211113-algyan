<style type="text/css">
  .reveal h1,
  .reveal h2,
  .reveal h3,
  .reveal h4,
  .reveal h5,
  .reveal h6 {
    text-transform: none;
  }
</style>
# えっ!<br><span style="color:pink">GR-ROSE</span>って<br>　<span style="color:blue">A*m</span>じゃないの？<br>から始めた話

[https://nagahisa.github.io/20211113-algyan/#/](https://nagahisa.github.io/20211113-algyan/#/)

---

## About me

```json: aboutme
aboutme.json
{ 
    "name":　           "Kenzo Nagahisa",
    "twitter":          "@kenzonag",
    "screen_name" :     "けんぞう",
    "interest": [
        {
            "topic":   "電子工作",
            "level":    "全くの初心者"
        },
        {
            "topic":   "Elixir/Nerves",
            "level":    "永遠の初心者"
        }
    ] 
}
```

BLOG 最近全然サボってますが・・・<br>
[qiita.com/nagahisa](https://qiita.com/nagahisa),
[medium.com/@kenzonag](https://medium.com/@kenzonag)

---

## そもそもの極めて個人的な動機

***
* テレビのリモコンが壊れました orz
* ググって ラズパイゼロでこんなの作りました

---

## 我が家の一大プロジェクト

![構成概要](https://camo.qiitausercontent.com/8f39580060f22225cd45ac4162df511b8eb58c77/68747470733a2f2f71696974612d696d6167652d73746f72652e73332e616d617a6f6e6177732e636f6d2f302f3136343738362f35643731393961662d343036382d636139342d363731352d3939646337613563656237382e6a706567)

参考サイト<br>
[レッツラズパイ！〜Google HomeでLピカさせよう編〜](https://qiita.com/westvirginia/items/47437d547485cd2784ef)<br>
[赤外線LEDドライブ回路の決定版](https://vintagechips.wordpress.com/2013/10/05/%E8%B5%A4%E5%A4%96%E7%B7%9Aled%E3%83%89%E3%83%A9%E3%82%A4%E3%83%96%E5%9B%9E%E8%B7%AF%E3%81%AE%E6%B1%BA%E5%AE%9A%E7%89%88/)

---

 Wifiが不安定なので有線LANもつけました
<img src="img/20211030100151.jpg"
     alt="rpi0+有線LAN">

---

# 結構な不満(^^;
***
* 有線LANボード価格が本体の3倍
* Linux パッチ適用メンドイ
* OS起動時にPython動かすって
<br>
...OS要らんやろ
<br>
<br>

## 噂に聞く<span style="color:green">Arduino</span>とかで<br>何とかならんもんか？


---

## なんか、無料でトライ<br>出来るらしいぞ
---

```
「今回、ルネサスエレクトロニクス株式会社様の全面的なご協力のもと、
「がじぇっとるねさすプロジェクトのIoT Edgeデバイス
「GR-ROSE(ジーアール・ローズ)」と周辺部材をどんとご提供頂き、
コンテストを開催する運びとなりました！」
```
[GR-ROSE IoTシステム開発コンテスト meet up！](https://algyan.connpass.com/event/220366/)

---

## *ROS*とか*IoT Edge*とか<br>謎の呪文があるけど<br><span style="color:green">Arduino</span>って書いてあるし<br>まっ何とかなるか！

---


<blockquote class="twitter-tweet"><p lang="ja" dir="ltr"><a href="https://twitter.com/hashtag/ALGYAN?src=hash&amp;ref_src=twsrc%5Etfw">#ALGYAN</a> <a href="https://twitter.com/hashtag/%E3%81%8C%E3%81%98%E3%81%87%E3%82%8B%E3%81%AD?src=hash&amp;ref_src=twsrc%5Etfw">#がじぇるね</a><br>可愛いボードが届きましたー。<br>が、がんばらねば(^^; <a href="https://t.co/FGuDnYXB2c">pic.twitter.com/FGuDnYXB2c</a></p>&mdash; けんぞう (@kenzonag) <a href="https://twitter.com/kenzonag/status/1433687177586638852?ref_src=twsrc%5Etfw">September 3, 2021</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

---

# 「RX65N」搭載

---

## えっ、<span style="color:pink">GR-ROSE</span>って<br>　<span style="color:blue">A*m</span>じゃないの？？

---

# <span style="color:green">Arduino</span>って<br><span style="color:blue">　A*m</span>じゃないの？？


---

![勘違い](https://career-picks.com/wp-content/uploads/2018/10/%E5%8B%98%E9%81%95%E3%81%84%E3%81%AE%E6%84%8F%E5%91%B3%E3%81%A8%E3%81%AF.001.webp)

---

# と・と・とりあえず<br>頑張ろう

---

# Step.0
---
e2studioに出鼻を挫かれる<br>

---

# W.I.P 
##  Webコンパイラに救われました

---

# Step.1
---
BeeBotte Arduino Tutorialやってみる<br>

[Led Control](https://beebotte.com/tutorials/led_control)

```
This tutorial presents how Beebotte can be used
 to control a led connected to an Arduino board. 
We will use MQTT protocol to connect Arduino
 to Beebotte to subscribe to messages to turn ON or OFF the led.
```

---

コミュニティに泣きついたり<br>
[WebコンパイラでBeeBotte?](https://japan.renesasrulz.com/gr_user_forum_japanese/f/gr-rose-iot/7493/web-beebotte)

 ArduinoJsonとかの<br>バージョンに悩んだり<br>
 ・・・
<br>
<br>
 ### 奇跡的に自己解決


---

# Step.2
----
有線LANにトライする


---

今度もコミュニティに泣きついたら<br>
[有線固定IPでMQTT](https://japan.renesasrulz.com/gr_user_forum_japanese/f/gr-rose-iot/7533/ip-mqtt)

```
有線LANでのPubSubClientライブラリ向けのClientクラスの実装は
していません。
MQTTサンプルで以下のインスタンスを作ってますが、
これに相当するEthernetのClientはないです。
すみませんが、EthernetクラスはROS用、AWS用の残骸のようなものなので、
使用できません。
```

### ・・・<br>人生、そう甘くはない

---

# Step.3
----
赤外線にトライする


---

## W.I.P

ラズパイはググったコードで動いた<br>
```python
import 
python xxxx
```
Pythonモジュールの中身なんて理解していない

---

すごく勉強になりました! <br>
[赤外線リモコンを受ける その１](http://whatismcu.blogspot.com/2014/10/blog-post_17.html)<br>
[赤外線リモコンを受ける その２](http://whatismcu.blogspot.com/2014/10/blog-post_6.html)<br>
[赤外線リモコンを受ける その３](http://whatismcu.blogspot.com/2014/10/blog-post_23.html)

---


<img src="img/2021103095405.jpg"
     alt="赤外線受信時の接続">

---

# Step.4
----
赤外線受信する



---


GR-KURUMIの記事を参考に <br>
[GR-KURUMIの機能を使う 外部割り込み編](http://tool-cloud.renesas.com/ja/atelier/detail.php?id=36)

受信のスケッチ作って<br>TVリモコンで「１、８、電源」を押下
```
 remote control test.
type NEC:sz=4 code:40,bf,01,fe,
type NEC:sz=4 code:40,bf,08,f7,
type NEC:sz=4 code:40,bf,12,ed,
```

我が家のTV電源は<br>「type NEC:sz=4 code:40,bf,12,ed,」<br>を送れば良いみたい

---

# Step.5
----

赤外線送信する



---

### ラズパイで使っていた<br>送信回路をGR-ROSEへ

<img src="img/20211030100104.jpg"
     alt="rpi0からGR-ROSEへ">

---

GR-KURUMIの記事を参考に <br>
[GR-KURUMIの機能を使う 外部割り込み編](http://tool-cloud.renesas.com/ja/atelier/detail.php?id=36)

受信のスケッチ作ってループ実行

```
remote control test.
TV on.
TV on.
TV on.
```

---

# う・う・動いた

---

## 感動です

![感動](https://3.bp.blogspot.com/-KdDdg5JuVlA/VahRs57vf6I/AAAAAAAAvvg/Y5zyTEslbpg/s400/pose_kandou_man.png)

---

# Step.6
----

BeeBotte情報を解析する


---

# W.I.P.
CURL情報→ ArduinoJson表現


---

# Step.7
----

外部割込みで赤外線送信

---

# W.I.P.
参考記事


---

# Step.8
----
スケッチにまとめました

---

# W.I.P.
GitHub URL


---

# 大団円
----
感想とお礼

---

# W.I.P.
・まとめ
	rpi python はモジュールの中身 BlackBox
	今回もしA*mだったら同じようになっていた
	→ がじぇるねさん・先人の皆様に感謝
	次はGR-ROSE本来の使い方 ROSにも挑戦したい(有線LAN使えるみたいだし^^)
	謝辞で一旦終了

---


<img src="img/20211030102649.jpg"
     alt="めでたしめでたし">

---

# ちょっと<br>まったぁ〜

---

## 応募要件
---
GR-ROSE＋Azureを使って<br>IoTシステムのアイデアを具現化

---

# Azureを使って

---

# も、もちろん<br>
# 使っております

---

# W.I.P.
Webコンパイラ画面
IP Address : AzureのCLI

---

![ごめんなさい](https://3.bp.blogspot.com/-eB33fYMnmfk/USNoBWJQljI/AAAAAAAANP4/8mzUCL5TbFI/s1600/message_gomennasai.png)

