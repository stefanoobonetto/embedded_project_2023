# Auto-Parking Car
This project has been developed by Mattia Rigon, Stefano Bonetto and Simone Roman as the exam for the uniTN course of Embedded Software for the Internet of Things.<br><br>
It's basically a Wi-Fi remoted controlled car, we can drive it in three modes:
<ol>
  <li>Normal joystick mode</li>
  <li>Joystick mode with ABS (autobraking system)</li>
  <li>Autoparking mode</li>
</ol>
When the autoparking mode is running, the car is able to find a space wide enough in the right side of the roadway and then execute a parallel park.

## Requirements
For our project we've used:
<ul>
  <li>2 x <a href="https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/SIMPLELINK_MSP432_SDK/1.20.00.45/exports/docs/simplelink_mcu_sdk/project0/project0/docs/MSP-EXP432P401R.html">MSP432P401R Launchpads</a></li>
  <li>2 x <a href="https://www.espressif.com/en/products/socs/esp32">ESP32</a> modules</li>
  <li><a href="https://www.ti.com/tool/BOOSTXL-EDUMKII">BOOSTXL-EDUMKII</a></li>
  <li><a href="https://components101.com/modules/l293n-motor-driver-module">L298N Motor Driver Module</a></li>
  <li><a href="https://www.electroschematics.com/hc-sr04-datasheet/">HC-SR04</a> ultrasonic module</li>
  <li><a href="https://education.makeblock.com/help/cyberpi-series-9g-micro-servo-metal-gear/">9g Micro Servo</a></li>
</ul>


