---
layout: default
title: Aetherharp Software
description: Hosts information about the software tools utilized to create the Aetherharp
---

# The Bela IDE
![IDEScreenshot](/assets/images/IDE-Screenshot.png "Bela IDE")
The Bela IDE (Integrated Development Environment) is an in-browser tool used to program the Bela board. To program the Bela board, the user simply plugs the Bela board into their computer via USB, installs some drivers, and navigates to bela.local in their browser to begin programming. The user is greeted by the UI shown in above, giving them the ability to create projects, write code in several languages, and even view the pinouts of both types of Bela board. The IDE even has a built-in oscilloscope and javascript app developer so the user has several options for adding visual elements to their program.

# The C++ Code
The code that runs on the Bela board for this project is purely C++. The code initializes by checking the selected wavetable and key, then periodically polls the 7 sensors, and finally builds an output float to be played via the built in speakers. The source code can be found at https://github.com/EE-Emerge/EE-Emerge2022_LaserHarp/tree/main/Bela_Programming/Working_Code4-22-2022_picnicDayCode.cpp




[back](./)
