Thanks for visiting this page to learn more about your HATCH trophy!

The trophy uses open source code and hardware, so please hack it to make it do what you want.  It comes loaded with some demo code to test each of the components.

There will be updates to this page in the coming weeks, but if you have any questions or comments, please initiate a "Issue" on github, and I will answer as soon as I can.

With the demo code loaded, the trophy will boot to the 'award' screen.  
Press buttons 'A' or 'B' to scroll through the menu.
'A' and 'B' buttons serve as scrolling features through the submenus as well.
The 'C' button is used as a 'select' button
The 'D' button is used as a 'select' button during the 'Set Clock' Function

When you go into the 'Demo Mode' Function, the program will loop forever.  To exit the loop, just press the reset button.

The following functions are loaded with the demo software:
View Clock (see the date/time/temperature from the DS3231 Real Time Clock module)
Set Clock (change the clock's time)
View Temp (see the temperature from the DS3231 Real Time Clock Module)
Lite Sense (view the analog signal from the light sensor.  Minimum is 0 / dark and Maximum is 1023 / very very bright)
Neopixels (cycles through a red/green/blue 'color wipe' animation)
Buzzer (plays the Super Mario theme song)
LEDs (cycles through LEDs on the DNA strand)
Battery (view battery voltage)
Demo Mode (scrolls through all features, sensors, and animations)

The trophies feature the following major components:
Arduino Nano (clone) microcontroller
DS3231 Real Time Clock (with temperature Sensor)
18650 Battery, along with charging circuit and DC-DC boost coverter to power the Arduino
128x32 Pixel OLED display
Piezo Buzzer
Light Sensor
Neopixel (WS2812v3) RGB LEDs
Surface mount LEDs
SAO v1.69 Connector




