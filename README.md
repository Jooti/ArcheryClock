Archery Clock
======
Archery Clock is an Arduino DIY project to make a countdown timer for archers. It's easy to make and needs elementary knowledge of working with Arduino. The [simulation] of the project is available at Wokwi:
https://wokwi.com/projects/383802552909274113

Using Archery Clock
------
Archery Clock is so simple, It has two buttons: 

  1. Start / Stop button: Start count down time or emergency stop of the shooting line.

  2. Configuration button: Change the timer duration (90, 120, 180, 240, 30)

In the [simulation] the start button is above the config button.
Using the configuration button set the appropriate time and then press the start button. It would play a double beep for the archers to get in the shooting line and after ten seconds the single beep of shooting would be sounded.

There would be a single short beep for warning of 30 sec remaining at all configurations except for the 30 seconds itself.
When the time is up or the start button is pressed again, the three beeps of time up are played.

Do It Yourself
------
To make this archery clock you need the following parts:
1. Arduino Nano * 1
2. Push buttons * 2
3. Resistors (1 KΩ) * 2
4. Buzzer * 1 (or a more powerful speaker and an amplifier for better sound)
5. LCD 1602 * 1 (Optional)
6. Potentiometer (50KΩ) * 1 (For LCD contract adjustment)
7. Breadboard * 1
8. Jumper wires

Connect the above parts as shown in the following image. Then clone this repository, open the [ArcheryClock.ino] in [Arduino IDE] and, upload it to your Arduino board.

![Archery clock circuit](https://raw.githubusercontent.com/Jooti/ArtcheryClock/main/Diagram.png)




[simulation]: https://wokwi.com/projects/383802552909274113
[Arduino IDE]: https://www.arduino.cc/en/software
[ArcheryClock.ino]: https://github.com/Jooti/ArtcheryClock/blob/main/ArcheryClock.ino