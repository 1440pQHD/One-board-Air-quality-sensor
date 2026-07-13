# BreatheEasy - One-board-Air-quality-sensor
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
4. 1x 20k Ohm resistors
5. 3x 10K Ohm resistors
6. 1x 5.1KOhm resistor
7. Sparkfun USB-C Breakout module (6-pin)
8. 2x 6mm Push buttons
9. LD1117
    
The total parts list comes to about 15 euros, which is fairly cheap.
Right now, only the hardware side has been really figured out; the software side is still in early development.


The final PCB design has already been made available for anyone who wants to take a look and/or assemble the PCB.

<h1> The first iteration of the website has been released!</h1>

<img width="833" height="819" alt="image" src="https://github.com/user-attachments/assets/0e7d0a35-a07e-4678-8a0b-1d6fbf9a4945" />

The website includes:
1. The current humidity
2. The current temperature
3. The current alcohol levels (this prototype uses an MQ-3 instead of an MQ-135)
4. The latest event (High temperature, Low temperature, high alcohol, etc.)
5. Uptime and time since last update
6. An alarm played through the browser.

<h2> How does it work? </h2>

The ESP32 reads the MQ-135 and DHT11 values through a voltage divider, since the sensor outputs up to 5v but the ESP32 can handle only 3.3V, and sends them in a JSON string to the browser you're viewing the website from.

The neat part is that, since the browser does all the heavy lifting, the ESP32 doesn't use much computing power.

I'm hoping by the end of the week I'll have gotten all the parts to build the final device. 







