VisionMate — IoT-Based Smart Assistive Mobility Stick
An IoT-powered smart blind stick that goes beyond what a traditional white cane can do — detecting obstacles, wet surfaces, smoke, and tracking the user's location in real time. Built as a final year B.Tech project in Electronics & Communication Engineering.

The problem
Traditional white canes rely solely on physical contact with obstacles. They can't detect hazards in advance, assess environmental conditions like wet surfaces or smoke, or allow caregivers to locate a user remotely. For the 253 million people worldwide living with visual impairment, this is a daily safety gap.
VisionMate was built to close it.

What it does
FeatureSensor/ModuleHow it worksObstacle detectionHC-SR04 Ultrasonic SensorDetects objects in the path and triggers buzzer + mobile app alertWet surface warning12V Moisture Sensor + RelayWarns user before stepping on slippery groundSmoke/gas detectionMQ6 Gas SensorAlerts user to presence of smoke or hazardous gasesReal-time GPS trackinguBlox Neo-M8N GPS ModuleStreams live location to ThingSpeak — accessible by caregivers remotelyAudio + text feedbackBluetooth + Arduino BT Text-to-Voice appConverts alerts into spoken audio on the user's phoneData visualisationThingSpeak IoT PlatformLogs all sensor readings — obstacle, moisture, smoke, GPS — to a cloud dashboard

System architecture
Sensors (Ultrasonic, Moisture, Gas, GPS)
        │
        ▼
ESP32 Microcontroller (real-time processing)
        │
        ├──► Piezoelectric Buzzer (immediate local alert)
        ├──► Bluetooth → Mobile App (audio + text feedback)
        └──► WiFi → ThingSpeak (cloud logging + GPS tracking)

## Hardware components

ESP32 Microcontroller — core processing unit, handles WiFi + Bluetooth
HC-SR04 Ultrasonic Sensor — obstacle detection
MQ6 Gas Sensor — smoke and gas detection
Moisture Sensor (12V) + Relay Module — wet surface detection
uBlox Neo-M8N GPS Module — location tracking
Piezoelectric Buzzer — local audio alert
L298N Motor Driver Module — sensor power management
Rechargeable Battery — portable power supply


## Results
All four detection systems were tested and verified:

--> Obstacle detection — ultrasonic sensor triggered buzzer and mobile app alert accurately at tested distances
--> Water detection — moisture sensor correctly identified wet surfaces and activated relay
--> Smoke detection — MQ6 sensor flagged gas presence with ThingSpeak logging confirmed
--> GPS tracking — live location streamed to ThingSpeak successfully, accessible remotely by caregiver


##Tech stack
ESP32; Arduino; HC-SR04; MQ6; uBlox Neo-M8N; GPS; ThingSpeak; Bluetooth; L298N; C++; IoT

## Repository structure

src/ — Arduino/ESP32 source code
report/ — Full project report (PDF)
paper/ — Published research paper
images/ — Hardware photos and circuit diagrams
README.md — this file


## Research Paper

This project was also written up as a research paper submitted for publication:

> *VisionMate: An IoT-Based Smart Assistive Mobility Stick for the Visually Impaired*
> Kolli Hema Sri Sruthi, Shreya Jha, G. Vyshnavi
> Sreenidhi Institute of Science and Technology, Hyderabad (2025)


Final year B.Tech project — Electronics & Communication Engineering, Sreenidhi Institute of Science and Technology, Hyderabad (2025)
