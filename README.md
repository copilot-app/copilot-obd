# Założenia

Celem projektu jest zrealizowanie odczytu danych z interfejsu OBD/OBD2 i umożliwienie zdalnego dostępu do informacji w czasie rzeczywistym.

# Teoria i praktyka

Złącze diagnostyczne OBD2 wyróźnia dwa typy A i B. Typ pierwszy spotykany jest w samochodach osobowych, z kolei ten drugi znajdziemy w pojazdach o większym gabarycie. Ze względu na to, że standardy ISO zostają przyjęte w różnych momentach czasowych, obecnie jeżdżące samochody po naszych drogach mogą korzystać z ich innych wersji. W zależności od użytego protokołu jak i systemów pomiarowych obecnych w samym pojeździe zmianie ulega również pula informacji które są rozgłaszane przez magistralę CAN.

[OBD2 Explained](https://www.csselectronics.com/pages/obd2-explained-simple-intro)

# Analiza rozwiązań rynkowych

Bezprzewodowe adaptery OBD dostępne na rynku wykorzystują szereg sprawdzonych protokołów komunikacyjnych, między innymi Bluetooth, Bluetooth Low Energy, LoRaWAN, WiFi. Większość z nich oferuje szeroką kompatybilność z wieloma modelami samochodów, jak i odczyt informacji z samego systemu OBD w mniej lub bardziej bogatym zakresie, jednak opinie użytkowników sugerują dość dużą zawodność, jeśli chodzi o urządzenia ze średniej i niskiej półki cenowej.

Najtańszym rozwiązaniom rzędu kilkudziesięciu złotych zdarza się ograniczać do pobierania informacji o występujących błędach, a w przypadku urządzeń coraz to wyższej klasy jest uzupełnione o więcej informacji, aż do momentu wyciągnięcia wszystkich możliwych do uzyskania w danym środowisku (gdzie granicę stanowi ilość danych dostępnych w danym modelu samochodu).

Poza samą komunikacją poprzez interfejs, istnieją rozwiązania oferujące zapis pobranych danych i ich prezentację w celach statystycznych (poprzez dedykowaną aplikację na urządzenia mobilne).

Po dokładnej analizie rozwiązań rynkowych trudno było nam dostrzec okazję do wprowadzenia rewolucji w tym obszarze. Na tej podstawie obierzemy podejście do tego tematu mające na celu dorównanie aspektem technologicznym do poziomu rynkowego starając się o utrzymanie kosztu produktu na jak najniższym poziomie, jednocześnie zachowując wysoki poziom niezawodności. 

### Przykłady gotowych rozwiązań

* [SparkFun RTL-10769](https://botland.com.pl/pozostale/1864-modul-diagnostyczny-obd-ii-car-diagnostics-kit-sparkfun-rtl-10769-845156001064.html#)
* [CANedge2: 2x CAN Bus Data Logger (SD + WiFi)](https://www.csselectronics.com/products/can-bus-data-logger-wifi-canedge2?variant=40254702059708)
* [Interfejs diagnostyczny Konwei KW903 BT OBD2](https://minexo.pl/sklep/interfejs-diagnostyczny-konnwei-kw903-bt-obd2/?CENEO-MINEXO&utm_source=ceneo&utm_medium=referral&ceneo_cid=34f6a00f-3b1a-1358-00bb-e230bd7b9178)
* [Interfejs diagnostyczny OBD2 Vgate iCar2 Bluetooth + SDPROG PL](https://smartmoto.pl/product-pol-7060-Interfejs-diagnostyczny-OBD2-Vgate-iCar2-Bluetooth-SDPROG-PL.html?utm_source=ceneo&utm_medium=referral&ceneo_cid=95da3a57-ae86-7c3d-cdb6-c4a0511753c6)
* [Analiza gotowych rozwiązań w pracy "Extraction and analysis of car driving data via OBD-II"](https://lcsi.umh.es/docs/pfcs/PFC_TFG_Bocanegra_Fernando.pdf)

# Projekt względem rynku

### Koszt produktu
Ze względu na nieznajomość jeszcze niezawodności i cen podzespołów ciężko oszacować (duży rozrzut cenowy), ile wyniesie dokładny koszt i jak będzie sie odnosił do cen sklepowych.

### Inspiracje i kontrastowe rozwiązania
Dominującym sposobem komunikacji wśród urządzeń odczytujących dane z interfejsu OBD jest Bluetooth. Nasze rozwiązanie z założenia ma zawierać sporadycznie wykorzystywany w tym obszarze sposób transmisji oparty na LoRaWAN. Umożliwi to zdalny dostęp do najistotniejszych parametrów oraz statystyk pojazdu.

W jednym z realizowanych projektów przez innych założenia celowały w inteligentny samochód, gdzie dostęp do danych był poprzez komendy głosowe. Do odczytywania informacji z OBD posłużyli się ESP32, które daje szerokie opcje rozwoju (Bluetooth, WiFi i inne).

Innym z projektów jest amatorski projekt Car Diagnostics With A Raspebrry. Projekt ten również bazuje na schemacie połączeniowym: OBD dongle -> MCU, w tym przypadku Raspebrry Pi. Transmijsa odbywa się za pomocą Bluetooth. Po podłączeniu wtyczki OBD następuje automatyczna detekcja protokołu komunikacyjnego zależnego od marki i/lub modelu samochodu. Odczytywane dane to podstawowe informacje dotyczące pojazdu oraz akutalnie przebywanej trasy. Projekt zawiera integrację z systemem GPS. Umożliwia to nakładka na mikrokontroler, która łączy się z satelitą. Zebrane dane są prezentowane na wyświetlaczu, którego interfejs został zaprogramowany w PyGame. 

### Obrana strategia
Po dokładnej analizie rynku, naturalnym pierwszym krokiem w planie naszego działania będzie analiza gotowego rozwiązania w praktyce. Ma to na celu dokładne zbadanie technicznych aspektów działania samego interfejsu OBD, takich jak rodzaj protokołu komunikacyjnego, rodzaj złącza itp.

Następnym etapem działania będzie prototypowanie i implementacja własnego rozwiązania. Przede wszystkim pomyślny odczyt informacji z systemu OBD, takich jak prędkość, kody błędów, stan paliwa itp. Kolejnym problemem do rozwiązania będzie kwestia komunikacji bezprzewodowej, zrozumienie i zaimplementowanie protokołów transmisji Bluetooth i LoRa.

Końcowo pozostały czas poświęcimy na dopracowanie całości i zadbanie o niezawodność rozwiązania, jak i optymalizację użytych zasobów.

## Podobne projekty

1. [Vehicle Monitoring Using OBD2 and Alexa (SmartCar)](https://www.researchgate.net/publication/342732397_Vehicle_Monitoring_Using_OBD2_and_Alexa_SmartCar_Final_Year_Project_Report_for_the_Degree_of_Bachelor_in_Electronics_Engineering)
2. [Car hacking | How I added features by manipulating can bus](https://tbruno25.medium.com/car-hacking-how-i-added-features-by-manipulating-can-bus-and-how-you-can-too-b391fcea11f1)
3. [Car Diagnostics With A Raspberry PI](https://www.youtube.com/watch?v=DABytIdutKk)

# Podsumowanie

Pobieranie danych z systemu OBD
- [Python](https://github.com/brendan-w/python-OBD)
- [C++](https://github.com/stanleyhuangyc/ArduinoOBD)

Udostępnianie pełnych danych diagnostycznych i statystycznych przy użyciu standardu Bluetooth.

Końcowym urządzeniem odbiorczym będzie telefon z system operacyjnym Android, na który zostanie napisana dedykowana aplikacja.

Udostępnianie najważniejszych danych takich jak lokalizacja czy kody błędów poprzez system LoRaWAN.

## Potencjalny hardware

* ESP32
* Kable
* Nadajnik-odbiornik LoRaWAN
* [Moduł rozwojowy WiFi, LoRa](https://nettigo.pl/products/modul-rozwojowy-heltec-wifi-lora-32-v2-868mhz-esp32-lora-oled-0-96)
