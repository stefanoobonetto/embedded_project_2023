<!--![9gmicroservo](https://user-images.githubusercontent.com/106806808/215067945-51a1b6f7-f6f2-402e-8aef-3ad31b301457.jpeg)-->
<!--![boosterpack](https://user-images.githubusercontent.com/106806808/215067950-49bc8f13-a4d6-4c00-88ac-0c96e9958253.jpeg)-->
<!--![esp32](https://user-images.githubusercontent.com/106806808/215067952-5d63d106-3309-4f83-b30b-24070b61c561.jpeg)-->
<!--![hc-sr04](https://user-images.githubusercontent.com/106806808/215067953-f4d2a225-9489-486c-9252-10a160119215.jpeg)-->
<!--![L298N](https://user-images.githubusercontent.com/106806808/215067957-167178b5-6da6-4547-bd09-d2daf8359801.jpeg)-->
<!--![msp432](https://user-images.githubusercontent.com/106806808/215067958-aa9dbdce-7557-4647-be4b-ba4c161b3c81.png)-->


# Smart Car
<div align=center>
<img src="https://user-images.githubusercontent.com/106806808/215711438-e02d5343-26c1-4949-85cc-87c8c4540e76.jpg" style="text-align: center; width: 500px ">
</div>
This project has been developed by Mattia Rigon, Stefano Bonetto and Simone Roman as the exam for the UniTN course of Embedded Software for the Internet of Things.<br><br>
It's basically a Wi-Fi remoted controlled car, we can drive it in three modes:
<ol>
  <li>Normal joystick mode</li>
  <li>Joystick mode with anticollision system</li>
  <li>Autoparking mode</li>
</ol>
When the autoparking mode is running, the car is able to find a space wide enough in the right side of the roadway and then execute a parallel park.

## Requirements
For our project we've used:
<ul>
  <li>2 x <a href="https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/SIMPLELINK_MSP432_SDK/1.20.00.45/exports/docs/simplelink_mcu_sdk/project0/project0/docs/MSP-EXP432P401R.html">MSP432P401R Launchpads</a></li>
  <li>2 x <a href="https://www.espressif.com/en/products/socs/esp32">ESP32</a> modules</li>
  <li><a href="https://www.ti.com/tool/BOOSTXL-EDUMKII">BOOSTXL-EDUMKII</a></li>
  <li><a href="https://components101.com/modules/l293n-motor-driver-module">L298N</a> Motor Driver Module</li>
  <li><a href="https://www.electroschematics.com/hc-sr04-datasheet/">HC-SR04</a> ultrasonic module</li>
  <li><a href="https://education.makeblock.com/help/cyberpi-series-9g-micro-servo-metal-gear/">9g Micro Servo</a></li>
  <li>9V battery</li>
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

We've build the Joystick Controller with an <a href="https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/SIMPLELINK_MSP432_SDK/1.20.00.45/exports/docs/simplelink_mcu_sdk/project0/project0/docs/MSP-EXP432P401R.html">MSP432P401R</a> Launchpad connected to the <a href="https://www.ti.com/tool/BOOSTXL-EDUMKII">BOOSTXL-EDUMKII</a> and to the <a href="https://www.espressif.com/en/products/socs/esp32">ESP32</a> Wi-Fi and Bluetooth module.<br>
We've used as our chassis the <a href="https://www.elegoo.com/products/elegoo-smart-robot-car-kit-v-4-0">ELEGOO UNO R3 Project Smart Robot Car V 4.0</a> with his built-in motors and wheels, but it's not mandatory, you can use whatever chassis you prefer, we have use four <a href="https://www.adafruit.com/product/3777">DC motor</a> (from 3V to 6V).

## Project Layout
```

├──MSP432_SENDER            #controller's code 
|     ├──Debug
|     ├──LcdDriver
|     ├──targetConfigs
|     ├──ConnectionUart.c
|     ├──ConnectionUart.h
|     ├──Display.c
|     ├──Display.h
|     ├──Joystick.c
|     ├──Joystick.h
|     ├──main.c
|     ├──msp432p401r.cmd
|     ├──startup_msp432p401r_ccs.c
|     └──system_msp432p401r.c
|
├──MSP432_RECEIVER           #car's code
|     ├──Debug
|     ├──LcdDriver
|     ├──targetConfigs
|     ├──ConnectionUart.c
|     ├──ConnectionUart.h
|     ├──Motor.c
|     ├──Motor.h
|     ├──UltrasonicSensor.c
|     ├──UltrasonicSensor.h
|     ├──main.c
|     ├──msp432p401r.cmd
|     ├──startup_msp432p401r_ccs.c
|     └──system_msp432p401r.c
|
├──ESP32_SENDER              #esp32 connected to the controller
|     └──ESP32_SENDER.ino
|
└──ESP32_RECEIVER              #esp32 connected to the car
      ├──ESP32_RECEIVER.ino
      ├──ESP32_Servo.cpp
      └──ESP32_Servo.h
```
As you can see, the code is divided in four parts: the code loaded into the controller (MSP432_SENDER) and the code in the MSP432 of the car (MSP432_RECEIVER) are the main parts, moreover we have setup the two ESP32 with some arduino code to communicate between them using their Wi-Fi modules (this is the only part done with arduinoIDE, the rest of the project is coded in C language).<br><br>

### UART communication
We've used the UART serial communication to let MSP432 and ESP32 talk to each other: 
<div align=center><img src="https://user-images.githubusercontent.com/106806808/215796807-f615ca3a-822e-4557-a7a2-4fbd6a86f0cb.png" style="width: 600 px"></div><br>
We have setup a unilateral UART connection because it was enough for our project, but it' easily implementable a bilateral communication between the two devices.<br><br>

### Display
The graphic part is composed basically by the functions that allow us to print elements on the LCD screen:
<ul>
	<li>The <i>graphicsInit()</i> function setup the LCD screen and projects the WELCOME screen.</li>
	<li>The <i>graphics_first_menu()</i> function projects the menu screen.</li>
	<li>The <i>joystick_mode_graphics(int sel1)</i> function projects the joystick mode screen, some strings (the one which communicate us if we are going straight 	on or in retro mode and the one that indicates turn) are projected by a function <i>draw()</i> in <i>joystick_mode_setup()</i> in <i>Joystick.c</i>.</li>
	<li>The <i>auto_park_mode_graphics()</i> function projects the autopark mode screen.</li>
</ul><br>

### Joystick
The joystick code include all the button's interrupts_handler:
<ul>
	<li>Boosterpack's S1 and S2 buttons interrupt handlers</li>
	<li>MSP432's S1 button interrupt handler</li>
</ul>	
They all works in the same way: when they're invoked they all check the value of the sel variable to undeerstand in which screen the user is, then every handler do a different thing based on sel and on the button pressed.<br>
Then we have the mode function:
<ul>
	<li><i>joystick_mode_setup()</i> calls his graphic's function and then check the ADC14 x and y values, converts them and send them to the car.</li>
	<li><i>keep_distance(bool on)</i> if on send to the car 3 times the code 202 (enable anticollision) else it send 203 (disable anticollision).</li>
	<li><i>auto_park_mode()</i> calls his graphic's function and then send the code 201 to the car til the BACK button is released.</li>
</ul><br>

## Build, Burn and Run the project
### How to setup Code Composer Studio Project
If you haven't done it already download the latest version of Code Composer Studio at <a href="https://www.ti.com/tool/download/CCSTUDIO/12.1.0">this link</a>.
First of all clone this repo and then import the folder as a project in CCS. Then you have to download driverlib at <a href="https://drive.google.com/file/d/1krZfBNAFiE6yAChQfHZVE-b0wfuDitgV/view">this link</a> and then add it to your current project, following these lines:
<ol>
	<li>Extract simplelink_msp432p4_sdk_3_40_01_02.zip file. </li>
	<li>Open CSS and left click on Project Folder to select Properties</li>
	<li>Select CSS Build</li>
	<li>Click ARM Compiler and then Include Options</li>
	<li>Add "simplelink_msp432p4_sdk_3_40_01_02/source" directory to "Add dir to #include search path" window.  </li>
	<li>Click ARM Linker and File Search Path</li>
	<li>Add "simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" to "Include library file..." window</li>
	<li>Add "simplelink_msp432p4_sdk_3_40_01_02\source\ti\grlib\lib\ccs\m4f\grlib.a" to "Include library file..." window</li>

</ol>

### Pin Mapping<br>

#### MSP432 Receiver
<table style="text-align: center">
  <tr>
    <td><b>PIN</b></td>
    <td><b>FUNCTION</b></td>
    <td><b>NOTES</b></td>
  </tr>
  <tr>
    <td>3.2</td> 
    <td>RX</td>
    <td>it's connected to ESP's pin G16. From there, the board receive controller's 	messages</td>
  </tr>
  <tr>
    <td>2.7</td>
    <td>Echo</td>
    <td>Connected to Ultrasonic Sensor's Echo pin</td>
  </tr>
  <tr>
    <td>2.6</td>
    <td>Trig</td>
	<td>Connected to Ultrasonic Sensor's Trig pin</td>
  </tr>
  <tr>
    <td>2.4</td>
    <td>EN_2</td>
    <td>Connected to L298N's EN_B pin</td>
  </tr>
  <tr>
    <td>5.6</td>
 	<td>EN_1</td>
    <td>Connected to L298N's EN_A pin</td>
  </tr>
  <tr>
    <td>5.7</td>
    <td>IN2_2</td>
    <td>Connected to L298N's IN3 pin</td>
  </tr>
   <tr>
    <td>1.7</td>
    <td>IN1_1</td>
    <td>Connected to L298N's IN1 pin</td>
  </tr>
   <tr>
    <td>5.0</td>
    <td>IN2_1</td>
    <td>Connected to L298N's IN2 pin</td>
  </tr>
   <tr>
    <td>5.2</td>
    <td>IN1_2</td>
    <td>Connected to L298N's IN4 pin</td>
  </tr>  
</table>
We've connected the board to a power-bank with his micro-USB connector.<br><br>

#### L298N
L298N is designed to have two motors connected, since we wanted to control four, we connected the left motors to OUT1 and OUT2 in pairs and similarly we connected the right motors to OUT3 and OUT4.
At the beginning we were using a motor shield which wasn't able to serve four motors simultaneously because it accepted only 5V power; so we have bought a new motor shield (L298N) and ae provide 9V power supply.<br><br>

#### MSP Sender
<table style="text-align: center">
  <tr>
    <td><b>PIN</b></td>
    <td><b>FUNCTION</b></td>
    <td><b>NOTES</b></td>
  </tr>
  <tr>
    <td>3.3</td> 
    <td>TX</td>
    <td>it's connected to ESP's pin G17. From there, the board send messages to the car</td>
  </tr>
</table>
<br><br>

## Other resources
<ul>
  <li><a href="https://youtu.be/69KgFIKE7XY">Youtube Video</a></li>
  <li><a href="https://docs.google.com/presentation/d/1h2l9AZ-rZWvKXyS_umFpl_V0j3etKmsssWN0EkKLERQ/edit#slide=id.p">PowerPoint Presentation</a></li>
</ul>
<br>

## Job Division
<table>
  <tr>
    <td>Motors setup and movement alghoritms</td><td>Mattia Rigon</td>
  </tr>
  <tr>
    <td>UART and Wi-Fi communication</td><td>Simone Roman</td>
  </tr>
  <tr>
    <td>Joystick interface, graphics and message sending</td><td>Stefano Bonetto</td>
  </tr>
  <tr>
    <td>Sensors setup, Autoparking mode and ABS mode</td><td>Stefano Bonetto, Simone Roman, Mattia Rigon</td>
  </tr>
  <tr>
    <td>Project debug and test</td><td>Stefano Bonetto, Simone Roman, Mattia Rigon</td>
  </tr>
</table><br>

## Contact us
Stefano Bonetto: stefano.bonetto@studenti.unitn.it <br>
Simone Roman: simone.roman@studenti.unitn.it <br>
Mattia Rigon: mattia.rigon@studenti.unitn.it <br>

