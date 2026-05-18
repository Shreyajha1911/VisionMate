## VisionMate — IoT-Based Smart Assistive Mobility Stick
An IoT-powered smart blind stick that goes beyond what a traditional blindstick can do; detecting obstacles, wet surfaces, smoke, and tracking the user's location in real time. Built as a final year project B.Tech project in Electronics & Communication Engineering.

## The problem
Traditional white canes rely solely on physical contact with obstacles. They can't detect hazards in advance, assess environmental conditions like wet surfaces or smoke, or allow caregivers to locate a user remotely. For the 253 million people worldwide living with visual impairment, this is a daily safety gap.
VisionMate was built to close it.

## What it does
The stick runs four detection systems at once — ultrasonic sensors scan the path ahead and trigger a buzzer plus a Bluetooth alert on the user's phone if an object is within 50cm, a moisture sensor at the base catches puddles before the user steps on them, an MQ6 gas sensor picks up smoke or hazardous gases above a safe threshold, and a GPS module streams live coordinates to ThingSpeak every 15 seconds so a caregiver can monitor location remotely from any browser. All four run on the same ESP32 simultaneously — we used millis() instead of delay() to keep the system responsive across all sensors without any one blocking the others. Every alert hits both the buzzer and the phone app, which reads it out loud via text-to-voice.

## System architecture

**Input — Sensors**
- HC-SR04 Ultrasonic Sensor
- Moisture Sensor
- MQ6 Gas Sensor
- uBlox Neo-M8N GPS Module

**Processing**
- ESP32 Microcontroller — receives all sensor data and handles real-time decisions

**Output — Alerts & Logging**
- Piezoelectric Buzzer — immediate local alert
- Bluetooth → Mobile App — audio and text feedback to user's phone
- WiFi → ThingSpeak — cloud logging of all sensor readings + live GPS tracking

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

## Obstacle detection — > ultrasonic sensor triggered buzzer and mobile app alert accurately at tested distances
## Water detection — > moisture sensor correctly identified wet surfaces and activated relay
## Smoke detection — > MQ6 sensor flagged gas presence with ThingSpeak logging confirmed
## GPS tracking — > live location streamed to ThingSpeak successfully, accessible remotely by caregiver


## Tech stack
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
