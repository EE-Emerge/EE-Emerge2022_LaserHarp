---
layout: default
title: Aetherharp Hardware
description: The Aetherharp utilizes 3 main hardware components: the Bela Board, the Bela HAT PCB, and the Sensor PCB.
---

# Hardware Design Revision 0.4

## The Bela Board
Purpose of the Bela board is to take inputs from the senssor PCBs and output sound to the built-in speakers. 
### Issues
During assembly and testing found following issues

1. Bela has no native support for playing instrument samples, so the team stuck to syntheic tones.
2. The Bela board's 5V output has very little power output capability, so each sensor has its own 5V supply.



## The Bela HAT PCB
Purpose of the Bela HAT PCB is to connect to the IO of the Bela Board and allow for easy connection between the Sensor PCB's outputs and the Bela Board's inputs. Featuring 7 RJ12 connectors, the Bela HAT PCB can accept input from all 7 sensor PCBs in addition to supplying the sensor PCBs with 9V power.
### Issues
During assembly and testing found following issues

1. The RJ12 connectors had slightly different footprints, so they had to be modified to fit on the PCB
2. The PCB was not well integrated with its housing, so the ports did not line up well.

## The Sensor PCB
Purpose of the sensor PCB is to power the Infrared Distance Sensor mounted on its surface and make sure that its analog output does not exceed 3.3V to prevent damage to the Bela Board.
### Issues
During assembly and testing found following issues

1. One of the 9V traces was placed too close to a ground trace, and soldering the voltage regulator improperly caused a short in one of the PCBs.
2. The bolts we recieved were not m3, so we had to grind threads into the PCB and into the distance sensor in order to mount the distance sensor to the PCB.

# Hardware Design Revision 1.2

## The Bela HAT PCB
The second iteration of teh Bela HAT PCB included a larger overall footprint capable of providing 5V power to the speakers and power/control of an LED strip. This iteration was desinged to fit well within its housing, making all necessary ports available on the back of the Aetherharp (USB, Ethernet, 9V Power, etc). We did not find issues in assembly because this revision was designed but was never implemented due to delays in the PCB manufacturing process.

![test_image](assets/css/octocat.png "Test Image")
