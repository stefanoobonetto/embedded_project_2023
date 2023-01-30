<!--![9gmicroservo](https://user-images.githubusercontent.com/106806808/215067945-51a1b6f7-f6f2-402e-8aef-3ad31b301457.jpeg)-->
<!--![boosterpack](https://user-images.githubusercontent.com/106806808/215067950-49bc8f13-a4d6-4c00-88ac-0c96e9958253.jpeg)-->
<!--![esp32](https://user-images.githubusercontent.com/106806808/215067952-5d63d106-3309-4f83-b30b-24070b61c561.jpeg)-->
<!--![hc-sr04](https://user-images.githubusercontent.com/106806808/215067953-f4d2a225-9489-486c-9252-10a160119215.jpeg)-->
<!--![L298N](https://user-images.githubusercontent.com/106806808/215067957-167178b5-6da6-4547-bd09-d2daf8359801.jpeg)-->
<!--![msp432](https://user-images.githubusercontent.com/106806808/215067958-aa9dbdce-7557-4647-be4b-ba4c161b3c81.png)-->


# Auto-Parking Car
This project has been developed by Mattia Rigon, Stefano Bonetto and Simone Roman as the exam for the UniTN course of Embedded Software for the Internet of Things.<br><br>
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

We've build the Joystick Controller with an <a href="https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/SIMPLELINK_MSP432_SDK/1.20.00.45/exports/docs/simplelink_mcu_sdk/project0/project0/docs/MSP-EXP432P401R.html">MSP432P401R Launchpad</a> connected to the <a href="https://www.ti.com/tool/BOOSTXL-EDUMKII">BOOSTXL-EDUMKII</a> and to the <a href="https://www.espressif.com/en/products/socs/esp32">ESP32 Wi-Fi and Bluetooth module</a>.<br>
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
The code is obviously divided in two parts: the code loaded into the controller and the code in the MSP432 of the car. Moreover we have setup the ESP32 with some arduino code to communicate between them using their Wi-Fi modules (this is the only part done with arduinoIDE, the rest of the project is coded in C language).<br><br>
We've used the UART serial communication to let MSP432 and ESP32 talk to each other: here is the example of the joystick mode, we store the results of the joystick movement (x-y frame) in the array resultsBuffer and we convert them into suitable data for the car MSP432: we'll send an 8 bit message with our UART connection (we could send more but 8 it's enough) so we dedicate the first 100 numbers to the x value, numbers from 100 to 200 will be the y value, the rest of the possible combinations will be used to call the functions (autopark, ABS). 

```c
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    
    if(status & ADC_INT1)
    {
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);

        int x = (int)(resultsBuffer[0]);
        int y = (int)(resultsBuffer[1]);

        x = (x - 8150)/82; 
        y = (y - 8150)/82;
        x = x/2 ; 
        y = y/2 ; 

        x = x +  49; // tra 0 e 100 trasmetto x
        y = y + 149; // tre 100 e 200 trasmetto y

        uint8_t X = (uint8_t)x;
        uint8_t Y = (uint8_t)y;
        
        if(cont ){
            UART_transmitData(EUSCI_A2_BASE, x);
            cont = 0 ;
        }else{
            UART_transmitData(EUSCI_A2_BASE, Y);
            cont = 1 ;
        }
    }
}
```


## Build, Burn and Run the project

## Other resources
These are some other resources:
<ul>
  <li><a href="">Youtube Video</a></li>
  <li><a href="">PP Presentation</a></li>
</ul>

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
</table>

