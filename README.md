# Analiza rozwiązań rynkowych

Bezprzewodowe adaptery OBD dostępne na rynku wykorzystują już pełen szereg sprawdzonych protokołów komunikacyjnych, między innymi Bluetooth, Bluetooth Low Energy, LoRaWAN, WiFi.

Większość obecnych na rynku rozwiązań oferuje szeroką kompatybilność z wieloma modelami samochodów, jak i odczyt informacji z samego systemu OBD w mniej lub bardziej bogatym zakresie.

Najtańszym rozwiązaniom rzędu kilkudziesięciu złotych zdarza się ograniczać do pobierania informacji o występujących błędach, a w przypadku urządzeń z coraz to wyższych półek cenowych jest uzupełnione o więcej informacji, aż do momentu wyciągnięcia wszystkich możliwych do uzyskania w danym środowisku (gdzie granicę stanowi ilość danych dostępnych w danym modelu samochodu).

Poza samą komunikacją poprzez interfejs, istnieją rozwiązania oferujące zapis pobranych danych i ich prezentację w celach statystycznych. 

Po dokładnej analizie rozwiązań rynkowych trudno było nam dostrzec okazję do wprowadzenia rewolucji w tym obszarze. Na tej podstawie obierzemy podejście do tego tematu mające na celu dorównanie aspektem technologicznym do poziomu rynkowego starając się o utrzymanie kosztu produktu na jak najniższym poziomie, jednocześnie zachowując wysoki poziom niezawodności.

# Q&A

**Ile będzie wynosił koszt produktu i czy będzie konkurencyjny?**

Ze względu na nieznajomość jeszcze niezawodności i cen podzespołów ciężko oszacować (duży rozrzut cenowy), ile wyniesie dokładny koszt i jak będzie sie odnosił do cen sklepowych. 

**Co będzie wyróżniało nasze rozwiązanie od innych?**

Dominującym sposobem komunikacji wśród urządzeń odczytujących dane z interfejsu OBD jest Bluetooth. Nasze rozwiązanie zawiera sporadycznie wykorzystywany w tym obszarze sposób transmisji oparty na LoRaWAN. Umożliwi to zdalny dostęp do parametrów oraz statystyk pojazdu. 

# Założenia

Pobieranie danych z systemu OBD
- [Python](https://github.com/brendan-w/python-OBD)
- [C++](https://github.com/stanleyhuangyc/ArduinoOBD)

Udostępnianie pełnych danych diagnostycznych i statystycznych przy użyciu standardu Bluetooth.

Końcowym urządzeniem odbiorczym będzie telefon z system operacyjnym Android, na który zostanie napisana dedykowana aplikacja.

Udostępnianie najważniejszych danych takich jak lokalizacja czy kody błędów poprzez system LoRaWAN.

# Źródła

1. [Vehicle Monitoring Using OBD2 and Alexa (SmartCar)](https://www.researchgate.net/publication/342732397_Vehicle_Monitoring_Using_OBD2_and_Alexa_SmartCar_Final_Year_Project_Report_for_the_Degree_of_Bachelor_in_Electronics_Engineering)
2. [Car hacking | How I added features by manipulating can bus](https://tbruno25.medium.com/car-hacking-how-i-added-features-by-manipulating-can-bus-and-how-you-can-too-b391fcea11f1)
3. [Extraction and analysis of car driving data via OBD-II](https://lcsi.umh.es/docs/pfcs/PFC_TFG_Bocanegra_Fernando.pdf)
