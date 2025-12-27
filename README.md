# STM32 PPG Heart Rate Monitor (Pulse Monitor)

This project measures real-time heart rate (BPM) using an **STM32F103C6** microcontroller and an optical **PPG (Photoplethysmography)** sensor. Signal processing algorithms are used to clean noisy sensor data and convert it into meaningful pulse data. Additionally, an LED blinks in sync with each detected heartbeat to provide real-time visual feedback.

## Features

* **Real-Time Monitoring:** Instant tracking of heart rate changes.
* **Signal Processing:** Digital filters are applied to reduce noise on raw data.
* **Low Cost:** Works with the STM32F103 series and standard pulse sensors.
* **Visualization:** Data can be read instantly from a 16x2 LCD screen.

## Hardware Requirements

* **Microcontroller:** STM32F103C6T6 (Blue Pill).
* **Sensor:** Pulse Sensor (Amped) or KY-039.
* **Programmer:** ST-Link V2.
* **Display:** 16x2 LCD Display (with I2C Module - PCF8574).

## Wiring Diagram (Pinout)

The table below shows the connections between the sensor and the microcontroller.

| PPG Sensor | STM32 Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V or 5V | Power Supply |
| **GND** | G | Ground |
| **S (Signal)** | **PA0** (ADC1) | Analog Signal Input |

| I2C LCD Display | STM32 Pin |
| :--- | :--- |
| **VCC** | 5V |
| **GND** | G |
| **SCL** | PB6 |
| **SDA** | PB7 |

> **Wiring Diagram:** ![baglanti](https://github.com/user-attachments/assets/c39b312a-50a8-4d3c-81e4-0a1811ffdf19)

## Software and Installation

1.  Clone this repository to your computer:
    ```bash
    git clone [https://github.com/gamzeferizli/STM32-PPG-Monitor.git](https://github.com/gamzeferizli/STM32-PPG-Monitor.git)
    ```
2.  Open **STM32CubeIDE**.
3.  Select the project folder via `File > Open Projects from File System`.
4.  Ensure that the compiler settings are selected for **STM32F103C6**.
5.  Build the project and upload (Run) it to the board using ST-Link.

## How It Works?

1.  The STM32 continuously reads sensor data via the ADC (Analog-to-Digital Converter).
2.  The read raw data is passed through filters within the software (e.g., Moving Average Filter).
3.  A "heartbeat" is detected when a specific threshold value is exceeded.
4.  The time between two beats (IBI) is calculated to find the BPM (Beats Per Minute).
5.  The result is printed on the LCD screen.

## Screenshots
![gosterim](https://github.com/user-attachments/assets/9b309568-39d2-43b2-91d7-5a91d880dcfa)



---
*This project was developed by **Gamze Ferizli**.*
