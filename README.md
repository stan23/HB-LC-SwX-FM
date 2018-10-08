# HB-LC-Sw2-FM     [![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)     [![GitHub issues](https://img.shields.io/github/issues/stan23/HB-LC-Sw2-FM.svg)](https://github.com/stan23/HB-LC-Sw2-FM/issues)

HomeBrew-Version des HM-LC-Sw2-FM bei dem die Tasterkanäle exportiert sind.

Dies basiert auf der hervorragenden Arbeit von [pa-pa](https://github.com/pa-pa/AskSinPP) und [seiner Version](https://github.com/pa-pa/AskSinPP/tree/master/examples/custom/HM-LC-SW2-FM) [für FHEM](https://forum.fhem.de/index.php/topic,76623.msg685237.html#msg685237), und  [Jérôme](https://github.com/jp112sdl/Beispiel_AskSinPP).





# Hardware



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

Benötigt wird die AskSinPP aus dem master-Branch, der V3-Branch ist zu alt.

...


### CCU-Unterstützung

Das [JP-HB-Devices-addon](https://github.com/jp112sdl/JP-HB-Devices-addon/releases) von Jérôme in Version 1.21 oder später.


# Bauanleitung

...



# Bilder

...



[![Creative Commons Lizenzvertrag](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-sa/4.0/)

Dieses Werk ist lizenziert unter einer [Creative Commons Namensnennung - Nicht-kommerziell - Weitergabe unter gleichen Bedingungen 4.0 International Lizenz](http://creativecommons.org/licenses/by-nc-sa/4.0/).
