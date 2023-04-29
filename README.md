# Building the project

Before you start, make sure to have [git](https://git-scm.com/) and [Python](https://www.python.org/downloads/) already installed.

Firstly, clone the source of **ESP Development Framework** and setup the build environment using a proper install script for your shell (**Windows PowerShell** in this example).
```shell
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.ps1
```
Run the export script in every new shell environment before using **ESP-IDF**.
```shell
./export.ps1
```
Then clone the source of **Copilot** and build it.
```shell
git clone --recursive https://github.com/copilot-app/copilot-obd.git
cd copilot-obd
idf.py build
```

# Assumptions

The aim of this project is to implement reading data from an OBD/OBD2 interface and enable remote access to real-time information.

# Theory and practice

The OBD2 diagnostic connector distinguishes two types: Type A, which is commonly found in passenger cars, while Type B can be found in medium and heavy-duty vehicles. Due to the fact that ISO standards have been adopted at different points in time, the cars currently driving on our roads may use different versions of these standards. Depending on the protocol used and the measurement systems present in the vehicle itself, the pool of information broadcasted by the CAN bus also changes.

[OBD2 Explained](https://www.csselectronics.com/pages/obd2-explained-simple-intro)

# Market solutions analysis

Wireless OBD adapters available on the market utilize a range of proven communication protocols, including Bluetooth, Bluetooth Low Energy, LoRaWAN, and WiFi. Most of them offer compatibility with many car models and the ability to read information from the OBD system to a greater or lesser extent. However, user reviews suggest relatively high unreliability when it comes to devices from the mid and low price range.

The capabilities of cheapest solutions are limited to retrieving information about existing errors. In the case of higher-end devices, the amount of available information increases, up to the point of reading all possible data in a given environment (where the limit is the amount of data available in a given car model).

In addition to the communication through the interface itself, there are solutions that offer recording of the collected data and their presentation for statistical purposes (through a dedicated mobile application).

After a thorough analysis of market solutions, we found it difficult to identify an opportunity to introduce a revolution in this area. Based on this, we have adopted an approach to this topic aimed at matching the technological aspects to the market level, while striving to maintain the product cost at the lowest possible level, while maintaining a high level of reliability.

### Avaliabe products

* [SparkFun RTL-10769](https://botland.com.pl/pozostale/1864-modul-diagnostyczny-obd-ii-car-diagnostics-kit-sparkfun-rtl-10769-845156001064.html#)
* [CANedge2: 2x CAN Bus Data Logger (SD + WiFi)](https://www.csselectronics.com/products/can-bus-data-logger-wifi-canedge2?variant=40254702059708)
* [Interfejs diagnostyczny Konwei KW903 BT OBD2](https://minexo.pl/sklep/interfejs-diagnostyczny-konnwei-kw903-bt-obd2/?CENEO-MINEXO&utm_source=ceneo&utm_medium=referral&ceneo_cid=34f6a00f-3b1a-1358-00bb-e230bd7b9178)
* [Interfejs diagnostyczny OBD2 Vgate iCar2 Bluetooth + SDPROG PL](https://smartmoto.pl/product-pol-7060-Interfejs-diagnostyczny-OBD2-Vgate-iCar2-Bluetooth-SDPROG-PL.html?utm_source=ceneo&utm_medium=referral&ceneo_cid=95da3a57-ae86-7c3d-cdb6-c4a0511753c6)
* [Analiza gotowych rozwiązań w pracy "Extraction and analysis of car driving data via OBD-II"](https://lcsi.umh.es/docs/pfcs/PFC_TFG_Bocanegra_Fernando.pdf)

# Project in relation to market

### Cost of product
Due to the unknown reliability and price range of components, it is difficult to estimate the exact cost and how it will compare to retail prices. However, we will strive to keep the cost as low as possible.

### Inspirations 
The dominant way of communication among devices that read data from the OBD interface is Bluetooth. Our solution is intended to include a sporadically used transmission method based on LoRaWAN, which is not commonly used in this area. This will enable remote access over a long range to the most important parameters and statistics of the vehicle.

In one of the projects carried out by others, the objectives were aimed at an intelligent car, where data access was through voice commands. They used ESP32 for reading information from the OBD, which provides a wide range of development options (Bluetooth, WiFi, and others).

Another project is an amateur project called "Car Diagnostics With A Raspberry". This project also uses the connection scheme: OBD dongle -> MCU, in this case, Raspberry Pi. The transmission is done via Bluetooth. After plugging in the OBD plug, the communication protocol is automatically detected, depending on model of car. The read data includes basic information about the vehicle parameters and the currently traveled route. The project includes integration with the GPS system. Collected data is presented on a display, whose interface was programmed in PyGame.

## Similar projects

1. [Vehicle Monitoring Using OBD2 and Alexa (SmartCar)](https://www.researchgate.net/publication/342732397_Vehicle_Monitoring_Using_OBD2_and_Alexa_SmartCar_Final_Year_Project_Report_for_the_Degree_of_Bachelor_in_Electronics_Engineering)
2. [Car hacking | How I added features by manipulating can bus](https://tbruno25.medium.com/car-hacking-how-i-added-features-by-manipulating-can-bus-and-how-you-can-too-b391fcea11f1)
3. [Car Diagnostics With A Raspberry PI](https://www.youtube.com/watch?v=DABytIdutKk)

### Strategy
The first step in our action plan will be to analyze the existing solution in practice. This aims to thoroughly examine the technical aspects of the OBD interface operation, such as the type of communication protocol, connector type, and so on.

The next stage of the plan will be prototyping and implementing our own solution. This will primarily involve successfully reading information from the OBD system, such as speed, error codes, fuel status, etc. The next problem to be solved will be the issue of wireless communication, understanding and implementing Bluetooth and LoRa transmission protocols.

Finally, the remaining time will be dedicated to refining the whole solution, ensuring its reliability, as well as optimizing the use of resources.

# Summary

Retrieving data from OBD system with ready-to-use open-source libraries:
- [Python](https://github.com/brendan-w/python-OBD)
- [C++](https://github.com/stanleyhuangyc/ArduinoOBD)

Sharing full diagnostic and statistical data using Bluetooth standard.

The final receiving device will be an Android-based phone, on which a dedicated application will be developed.

Sharing the most important data such as location or error codes through the LoRaWAN system.

## Hardware

* LoRaWAN transceiver
* [ESP32 development board](https://nettigo.pl/products/modul-rozwojowy-heltec-wifi-lora-32-v2-868mhz-esp32-lora-oled-0-96)