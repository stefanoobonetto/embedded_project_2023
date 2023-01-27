<!--![9gmicroservo](https://user-images.githubusercontent.com/106806808/215067945-51a1b6f7-f6f2-402e-8aef-3ad31b301457.jpeg)-->
<!--![boosterpack](https://user-images.githubusercontent.com/106806808/215067950-49bc8f13-a4d6-4c00-88ac-0c96e9958253.jpeg)-->
<!--![esp32](https://user-images.githubusercontent.com/106806808/215067952-5d63d106-3309-4f83-b30b-24070b61c561.jpeg)-->
<!--![hc-sr04](https://user-images.githubusercontent.com/106806808/215067953-f4d2a225-9489-486c-9252-10a160119215.jpeg)-->
<!--![L298N](https://user-images.githubusercontent.com/106806808/215067957-167178b5-6da6-4547-bd09-d2daf8359801.jpeg)-->
<!--![msp432](https://user-images.githubusercontent.com/106806808/215067958-aa9dbdce-7557-4647-be4b-ba4c161b3c81.png)-->


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

<table>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067958-aa9dbdce-7557-4647-be4b-ba4c161b3c81.png" style="width:175px"></td>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067952-5d63d106-3309-4f83-b30b-24070b61c561.jpeg" style="width:175px"></td>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067950-49bc8f13-a4d6-4c00-88ac-0c96e9958253.jpeg" style="width:175px"></td>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067957-167178b5-6da6-4547-bd09-d2daf8359801.jpeg" style="width:175px"></td>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067953-f4d2a225-9489-486c-9252-10a160119215.jpeg" style="width:175px"></td>
    <td><img src="https://user-images.githubusercontent.com/106806808/215067945-51a1b6f7-f6f2-402e-8aef-3ad31b301457.jpeg" style="width:175px"></td>
  </tr>
</table>

