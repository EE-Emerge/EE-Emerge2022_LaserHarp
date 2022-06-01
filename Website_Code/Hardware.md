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

## The Bela HAT PCB
Purpose of the Bela HAT PCB is to connect to the IO of the Bela Board and allow for easy connection between the Sensor PCB's outputs and the Bela Board's inputs. Featuring 7 RJ12 connectors, the Bela HAT PCB can accept input from all 7 sensor PCBs in addition to supplying the sensor PCBs with 9V power.
### Issues
During assembly and testing found following issues

1. The RJ12 connectors had slightly different footprints, so they had to be modified to fit on the PCB
2. The PCB was not well integrated with its housing, so the ports did not line up well.
