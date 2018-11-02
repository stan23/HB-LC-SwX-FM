# HB-LC-Sw2-FM     [![GitHub issues](https://img.shields.io/github/issues/stan23/HB-LC-Sw2-FM.svg)](https://github.com/stan23/HB-LC-Sw2-FM/issues)

HomeBrew-Version des HM-LC-Sw2-FM bei dem die Tasterkanäle exportiert sind.

Dies basiert auf der hervorragenden Arbeit von [pa-pa](https://github.com/pa-pa/AskSinPP) und [seiner Version](https://github.com/pa-pa/AskSinPP/tree/master/examples/custom/HM-LC-SW2-FM) [für FHEM](https://forum.fhem.de/index.php/topic,76623.msg685237.html#msg685237), und  [Jérôme](https://github.com/jp112sdl/Beispiel_AskSinPP).





# Hardware

1x HM-LC-Sw2-FM :)


### Programmieradapter
- 1x ISP (z.B. [diesen hier](https://www.diamex.de/dxshop/USB-ISP-Programmer-fuer-Atmel-AVR-Rev2))


# Software

### Fuses
High: 0xD0
Low:  0xA4

`C:\Program Files (x86)\Arduino\hardware\tools\avr\bin> .\avrdude -C ..\etc\avrdude.conf -p m32 -P com7 -c stk500v2 -U lfuse:w:0xA4:m -U hfuse:w:0xD0:m`

### Bootloader

Ein Bootloader wird nicht verwendet.

### Firmware

Benötigt werden die Bibliotheken [AskSinPP](https://github.com/pa-pa/AskSinPP) aus dem master-Branch, sowie die [HLW8012](https://github.com/xoseperez/hlw8012), die [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) und [Low-Power](https://github.com/rocketscream/Low-Power).

![Einstellungen IDE](https://github.com/stan23/HB-LC-Sw2-FM/blob/master/Bilder/ArduinoIDE_Auswahl_Controller.png)


### CCU-Unterstützung

Das [JP-HB-Devices-addon](https://github.com/jp112sdl/JP-HB-Devices-addon/releases) von Jérôme in Version 1.21 oder später.


# Bauanleitung

Den HM-LC-Sw2-FM öffnen und die 6 Leitungen des ISP anlöten.

Mit der Arduino IDE den Sketch mit Programmer hochladen, die Fuses per AVRdude Kommadozeile oder mit Atmel Studio brennen.

Anschließend kann das neue Gerät per Seriennummer an die CCUx angelernt werden.

# Bilder

![HM-LC-Sw2-FM geöffnet](https://github.com/stan23/HB-LC-Sw2-FM/blob/master/Bilder/HM-LC-Sw2-FM geöffnet.jpg)
![Anschluss ISP](https://github.com/stan23/HB-LC-Sw2-FM/blob/master/Bilder/Anschluss ISP.jpg)
![Pinbelegung ISP](https://github.com/stan23/HB-LC-Sw2-FM/blob/master/Bilder/Pinbelegung ISP.jpg)




