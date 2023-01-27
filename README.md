# Autonomer-Anemometer
Dieses Projekt befasst sich mit einem Arduino-basierten Anemometer, welches durch Solarenergie betrieben wird und die Windgeschwindigkeit erfassen kann. Das Gerät dient dazu Stürme zu erkennen, die in den Wintermonaten häufiger auftreten und dessen Windgeschwindigkeiten aufzuzeichnen, sodass die Werte mit den Werten vergangener Winterjahre verglichen werden können. Zusätzlich können die gemessenen Werte in Echtzeit an ein mobiles Endgerät gesendet werden. Auf diese Weise können die Werte auch unterwegs eingesehen werden und müssen nicht von Hand ausgelesen werden.

## Bedienungsanleitung
### 1. Einrichtung von Blynk
Erstelle ein neues Template in deiner Blynk App und bilde diese View in deiner App nach:

<img src="https://github.com/Lynncholy/Autonomer-Anemometer/blob/main/Bilder/Blynk_Editor.png" width="200" height="400" />
Wichtig ist hierbei, dass das obere "Labeled Value" Widget (die Anzeige für die aktuelle Windgeschwindigkeit) als Datastream den "Int Datastream 1 (v1)" erhält um die aktuelle Windgeschwindigkeit zu empfangen. Das zweite "Labeled Value"-Feld erhält als Datastream den "Double Datastream 1 (v5)" für die Durchschnittsgeschwindigkeit.

Bei den SuperChart-Widgets (die Diagrammfelder) können entsprechend der vorherigen Auswahl auch die Datastream eingetragen werden, also V1 für das aktuelle Windgeschwindigkeits-Diagramm und V5 für das Durchschnittsgewindigkeit-Diagramm.

Der Button für den Schlafmodus kann ignoriert werden.

### 2. Arduino vorbereiten
Kopiere den Code von hier https://github.com/Lynncholy/Autonomer-Anemometer/blob/main/Anemometer_Software.ino in deinen Arduino Editor.

Lade die Bibliotheken "Blynk" von Volodymyr Shymanskyy und den "WiFiManager" von tablatronix herunter für Arduino.

Im Programm code wird du eine Stelle finden, die so aussieht:

```
char auth[] = ""; //Your authentification token from the Blynk project
char ssid[] = "";  //Your SSID
char pass[] = ""; //Your WiFi password
```
Gib an dieser Stelle dein WLAN-Passwort und der Name deines WLAN-Routers ein. Den Authentifizierungs-Token für dein Projekt, kann du auf dem Dashboard der Blynk-Webanwendung finden.

### 3. Hardware zusammenbauen
#### Komponentenliste:
Akkupackung (3 Stück): 10,99 € (https://www.amazon.de/gp/product/B08HD4MDPQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

Schalen-Anemometer: 29,75 € (https://funduinoshop.com/elektronische-module/sensoren/bewegung-distanz/windstaerke-messgeraet-anemometer-fuer-arduino)

Solarzelle: 5,90 € (https://funduinoshop.com/diy-werkstatt/stromversorgung/solarzellen/solarzelle-2w-6v-11.0cm-13.6cm)

Solarenergie-Modul: 16,50 € (https://www.amazon.de/gp/product/B07P85QZ7D/ref=)

Micro-USB Kabel: 4,99 €

Installationsbox: 8,19 €

Wemos D1 mini: 5,95 € (https://funduinoshop.com/elektronische-module/wireless-iot/esp-wifi/wemos-d1-mini-nodemcu-lua-wifi-esp8266-entwicklungsboard)

Verbinde die einzelnen Komponenten bsaierend auf diesem Schema miteinander:

<img src="https://github.com/Lynncholy/Autonomer-Anemometer/blob/main/Bilder/Verkabelung_Komponenten.png" width="600" />

### 4. Einsatz des Geräts
Verbinde den Wemos D1 mini mit Arduino und lade das Programm darauf.

Danach kann der Mikrocontroller mit dem Solarenergie-Modul verbunden werden und darüber mit Strom versorgt werden.

Drücke den Reset-Knopf am Mikrocontroller, damit er eine Verbindung mit dem Internet aufbauen kann. Ab dann sollte der Controller selbstständig Werte an Blynk senden können.

Platziere den Anemometer ca. 2 bis 3 m über den Boden auf einer Leiste/Stange o.ä. Achte dabei darauf, dass der Anemometer möglichst frei steht und keine Gegenstände in der Nähe den Wind blockieren.

Platziere die Installationsbox mit dem Solarpanel und der inneren Elektronik an einem Platz, der möglichst viel Sonne abbekommen kann.

Das Gerät ist nun in Betrieb.

## Hinweis
Das Gerät kann nur etwa 12 Stunden ununterbrochen im Betrieb sein, da der Akku nicht schnell genug aufgeladen werden kann durch Solarenergie.
