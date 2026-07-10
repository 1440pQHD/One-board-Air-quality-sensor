# One-board-Air-quality-sensor
A simple, cheap-to-build PCB that actively monitors air quality and prevents invisible hazards. It makes protection from environmental hazards accessible to everyone.

The brains of the project are the ESP32 C3-Wroom-02
<img width="450" height="450" alt="image-removebg-preview (4)" src="https://github.com/user-attachments/assets/8346db70-0451-4311-9c58-4063bef42dd6" />


<b> Why did I choose this board? </b>

Because it includes: Wifi, Bluetooth, more than enough GPIO to last me days, and most importantly,
It's dirt cheap

List of sensors used:
BME280 (Temp & Humidity)
<br> MQ-135 (Hazardous Gas)

<p>
  Powering everything is as simple as plugging in a USB-C cable, something we should all have by now.
</p>
<p>
  The information can be read from a website that the microcontroller hosts on the local network that it's connected to.
</p>

The complete parts list includes:
1. ESP32 C3 Wroom O2
2. MQ-135 GAS sensor (Specifically the one with the digital out pin)
3. BMP280 (We love Bosh)
4. 2x 10K Ohm resistors
5. 1x 5.1KOhm resistor
6. USB-C Breakout module (6pin)
7. 2x 6mm Push buttons
8. LD1117
9. 4 Channel Logic converter

The total parts list comes to about 15 euros, which is fairly cheap.
Right now, only the hardware side has been really figured out, the software side has yet to be worked on.
