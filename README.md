# 🤖 FSM-Based Smart Autonomous Patrol System

A smart autonomous security patrol robot built with Arduino Uno and a multi-sensor array. Developed as part of a university project submitted to ICENSTED 2026.

## 📌 What It Does

The robot continuously monitors its environment using the **Sense-Decide-Act** cycle. It manages four operational modes controlled by a **Finite State Machine (FSM)**:

| Priority | Mode | Trigger |
| :--- | :--- | :--- |
| 1 (Highest) | Intruder Alert 🚨 | PIR motion detected |
| 2 | Obstacle Avoidance 🔴 | Distance < 20 cm |
| 3 | Night Mode 🌙 | Low light (LDR < 400) |
| 4 (Default) | Patrol Mode ✅ | No triggers |

## 🛠️ Hardware

* Arduino Uno
* HC-SR04 Ultrasonic Sensor
* PIR Sensor
* LDR (Light Dependent Resistor)
* Micro Servo Motor
* Piezo Buzzer
* Red & Yellow LEDs

## 👥 Authors
* **Asude Salık** - Computer Engineering, Maltepe University
* **Pelin Tetik** - Computer Engineering, Maltepe University
* **Emre Atlıer Olca** — Software Engineering, Maltepe University
