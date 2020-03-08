
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////  2020 Hudson Alpha Tech Challenge - TROPHY DEMO CODE - BY ANDREW DENIO 
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
  THIS CODE WAS USED TO DEMO THE TROPHY FOR THE AWARD CEREMONY ON SUNDAY, MARCH 8, 2020.
  THERE WERE A LOT OF LESSONS LEARNED DURING THIS PROCESS.

  THE 'A' AND 'B' BUTTONS ARE PRIMARILY USED FOR SCROLLING.  
  THE 'C' BUTTON IS USED AS A SELECT BUTTON.
  THE 'D' BUTTON IS USED AS A SELECT BUTTON WHEN CHANGING THE TIME UNDER THE 'SET CLOCK' FUNCTION.
  
  IF YOU HAVE ANY QUESTIONS OR COMMENTS, FEEL FREE TO INITIATE AN ISSUE ON GITHUB.  I PLAN TO ADD ADDITIONAL COMMENTS IN THE CODE, AND MAYBE SOME MORE FEATURES!
  
  ALL LIBRARIES FOR COMPONENTS WILL BE INCLUDED IN GITHUB LINK, SO FEEL FREE TO TINKER AROUND!
  https://github.com/MakeItHackin/Hatch2020Trophy
 */


/*

HATCH 2020 TROPHY PINOUT

ARDUINO NANO CLONE


D1/TX - CONNECTED TO OFF-BOARD RESISTOR AND LED, OTHERWISE, DO NOT USE - USB COMMUNICATION
D0/RX - CONNECTED TO OFF-BOARD RESISTOR AND LED, OTHERWISE, DO NOT USE - USB COMMUNICATION
RST - RESET BUTTON
GND - CONNECTED TO GROUND PLANE
D2 - BUTTON C (save for interrupt button?)
D3 - BUTTON B
D4 - BUTTON A
D5 - BUTTON D
D6 - NEOPIXEL OUT
D7 - LED1
D8 - PIEZO BUZZER
D9 - LED2
D10 - LED3
D11/MOSI - LED4
D12/MISO - LED5

VIN - CONNECTED TO OUTPUT FROM BOOST CONVERTER
GND - CONNECTED TO GROUND PLANE
RST - RESET BUTTON
5V - CONNECTED TO 5V BUS
A7 -  LIGHT SENSOR / (cannot be used as digital pin)
A6 - battery voltage sensor/divider / (cannot be used as digital pin)
A5 - i2c (SCL)
A4 - i2c (SDA)
A3 - LED9
A2 - LED8
A1 - LED7
A0 - LED6
AREF - NOT CONNECTED
3V3 - CONNECTED TO 3V3 BUS and SAO (IS THIS NEEDED?)
D13/SCK - CONNECTED TO OFF-BOARD RESISTOR AND LED


*/


/*

AWARD TYPE:
0 - DEMO MODE
1 - HIGH SCHOOL FIRST PLACE
2 - HIGH SCHOOL SECOND PLACE
3 - PROFESSIONAL FIRST PLACE
4 - PROFESSIONAL SECOND PLACE
5 - PROFESSIONAL THIRD PLACE
6 - HUDSON ALPHA
7 - URBAN ENGINE
8 - ACCLINATE GENETICS
9 - HATCH
*/
int awardtype = 7; //CHAGE THIS VALUE TO CHANGE THE AWARD TYPE


// Music Notes for the Super Mario Bros Theme music
#define NOTE_G6  1568
#define NOTE_C7  2093
#define NOTE_E7  2637
#define NOTE_G7  3136

// Below are the Bitmaps used for the Sponsor Logos
const unsigned char AcclinateBitmap [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x91, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x91, 0x22, 0x42, 0x81, 0x00, 0x01, 0x20, 0x00, 0x20, 0x07, 0xc0, 0x00, 0x01, 0x20, 0x00, 
0x00, 0x91, 0x2b, 0x5a, 0x83, 0x00, 0x01, 0x00, 0x00, 0x20, 0x18, 0x40, 0x00, 0x01, 0x00, 0x00, 
0x00, 0x15, 0x2b, 0x5a, 0x82, 0x80, 0x01, 0x20, 0x00, 0x20, 0x10, 0x00, 0x00, 0x01, 0x20, 0x00, 
0x00, 0x15, 0x2b, 0x5a, 0x80, 0x87, 0x39, 0x27, 0xcf, 0x3b, 0x90, 0x0f, 0x7c, 0x73, 0xa3, 0xbc, 
0x00, 0x25, 0x2b, 0x5a, 0x87, 0xc4, 0x21, 0x26, 0x41, 0x26, 0x50, 0xe9, 0x26, 0xc9, 0x24, 0x24, 
0x00, 0x24, 0x2b, 0x5a, 0x84, 0x48, 0x41, 0x24, 0x47, 0x27, 0xd0, 0x4f, 0x26, 0xf9, 0x24, 0x1c, 
0x02, 0x24, 0x0b, 0x5a, 0x88, 0x4c, 0x61, 0x24, 0x4b, 0x26, 0x1c, 0x48, 0x26, 0xc1, 0x24, 0x24, 
0x02, 0x24, 0x08, 0x02, 0x1c, 0x77, 0xbf, 0xf6, 0x6f, 0xb3, 0x87, 0xc7, 0x76, 0x71, 0xf7, 0xbc, 
0x12, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x12, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x12, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const unsigned char UrbanEngineBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0xfc, 0x01, 0xfe, 0x00, 0x3e, 0x00, 0xf0, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0xfe, 0x01, 0xff, 0x00, 0x3e, 0x00, 0xf8, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0x8e, 0x01, 0xcf, 0x00, 0x3e, 0x00, 0xf8, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0x0f, 0x01, 0xc7, 0x00, 0x7f, 0x00, 0xfc, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0x0f, 0x01, 0xc7, 0x00, 0x7f, 0x00, 0xfe, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0x9e, 0x01, 0xff, 0x00, 0xf7, 0x80, 0xff, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0xfe, 0x01, 0xff, 0x00, 0xe3, 0x80, 0xef, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0xfc, 0x01, 0xff, 0x01, 0xe3, 0xc0, 0xe7, 0xf8, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x38, 0x1c, 0x07, 0xf8, 0x01, 0xc7, 0x81, 0xff, 0xc0, 0xe3, 0xf8, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x3c, 0x1c, 0x07, 0x3c, 0x01, 0xc3, 0x81, 0xff, 0xc0, 0xe1, 0xf8, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x3c, 0x3c, 0x07, 0x3c, 0x01, 0xc7, 0x83, 0xff, 0xe0, 0xe1, 0xf8, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x1f, 0xf8, 0x07, 0x1e, 0x01, 0xff, 0x83, 0x80, 0xe0, 0xe0, 0xf8, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x0f, 0xf8, 0x07, 0x0f, 0x01, 0xff, 0x07, 0x80, 0xf0, 0xe0, 0x78, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x07, 0xe0, 0x07, 0x07, 0x01, 0xfe, 0x07, 0x00, 0x70, 0xe0, 0x38, 
0x0f, 0xe0, 0xfe, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x0f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x7c, 0x06, 0x10, 0x03, 0x00, 0x60, 0x31, 0x80, 0xf8, 0x00, 
0x0f, 0xf0, 0x00, 0x0f, 0xe0, 0x00, 0x7c, 0x07, 0x30, 0x0f, 0xc0, 0x60, 0x31, 0x80, 0xf8, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x60, 0x07, 0x30, 0x1c, 0xc0, 0x60, 0x39, 0x80, 0xc0, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7c, 0x07, 0xb0, 0x18, 0x00, 0x60, 0x3d, 0x80, 0xf8, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7c, 0x07, 0xf0, 0x39, 0xc0, 0x60, 0x3f, 0x80, 0xf8, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x60, 0x06, 0xf0, 0x39, 0xe0, 0x60, 0x37, 0x80, 0xe0, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x60, 0x06, 0x70, 0x1c, 0xe0, 0x60, 0x37, 0x80, 0xc0, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7c, 0x06, 0x70, 0x0f, 0xe0, 0x60, 0x33, 0x80, 0xf8, 0x00, 
0x0f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x7c, 0x06, 0x30, 0x07, 0x80, 0x60, 0x31, 0x80, 0xf8, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char HudsonAlphaBitmap [] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x38, 0x18, 0xc1, 0x9f, 0xe0, 0xfc, 0x1f, 0x86, 0x0c, 0x0f, 0x03, 0x01, 0xfc, 0x60, 0xc0, 0xc0, 
0x38, 0x18, 0xc3, 0x9f, 0xf1, 0xfe, 0x3f, 0xc7, 0x0c, 0x1f, 0x83, 0x01, 0xfe, 0x60, 0xc1, 0xe0, 
0x3f, 0xf8, 0xc3, 0x98, 0x33, 0x80, 0x70, 0xe7, 0xcc, 0x19, 0x83, 0x01, 0x86, 0x60, 0xc1, 0xe0, 
0x3f, 0xf8, 0xc3, 0x98, 0x31, 0xf0, 0x60, 0xe7, 0xec, 0x39, 0xc3, 0x01, 0x8e, 0x7f, 0xc3, 0xf0, 
0x38, 0x18, 0xc3, 0x98, 0x30, 0xfe, 0x60, 0xe6, 0xfc, 0x7f, 0xe3, 0x01, 0xfe, 0x7f, 0xc7, 0x30, 
0x38, 0x18, 0xc3, 0x98, 0x30, 0x0e, 0x60, 0xe6, 0x7c, 0x7f, 0xe3, 0x01, 0xf8, 0x60, 0xc7, 0xf8, 
0x38, 0x18, 0xe3, 0x9c, 0x73, 0x8e, 0x70, 0xe6, 0x3c, 0xe0, 0x73, 0x01, 0x80, 0x60, 0xcf, 0xfc, 
0x38, 0x18, 0xff, 0x1f, 0xf3, 0xfc, 0x3f, 0xc6, 0x0c, 0xc0, 0x33, 0xf9, 0x80, 0x60, 0xcc, 0x0c, 
0x00, 0x00, 0x18, 0x00, 0x00, 0x70, 0x06, 0x02, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x29, 0x3b, 0xd7, 0xc3, 0xde, 0x7b, 0x9c, 0x7a, 0x77, 0xbb, 0xd2, 0x93, 0xa1, 0xce, 0x90, 0x00, 
0x2d, 0xe1, 0x92, 0x44, 0x90, 0x66, 0xf6, 0x6a, 0xda, 0x22, 0x12, 0xd4, 0xa2, 0x50, 0xf0, 0x00, 
0x2f, 0xb9, 0x12, 0x44, 0x9e, 0x7e, 0x7e, 0x7a, 0x9a, 0x3a, 0x1e, 0xf4, 0xa2, 0x56, 0x60, 0x00, 
0x2b, 0x89, 0x12, 0x6c, 0x90, 0x46, 0xfc, 0x4a, 0xda, 0x22, 0x12, 0xb4, 0xa2, 0x52, 0x20, 0x00, 
0x29, 0xf9, 0x12, 0x38, 0x9e, 0x43, 0xb6, 0x7a, 0x72, 0x3b, 0xd2, 0x97, 0xbd, 0xce, 0x20, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char HATCH2020Bitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x1f, 0x80, 0xff, 0xff, 0x07, 0xff, 0x01, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x1f, 0x81, 0xff, 0xff, 0x0f, 0xff, 0xc1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x1f, 0xc1, 0xff, 0xff, 0x1f, 0xff, 0xc1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x3f, 0xc1, 0xff, 0xff, 0x1f, 0xff, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x3f, 0xc0, 0x07, 0xc0, 0x3f, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x3f, 0xe0, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x7d, 0xe0, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x7d, 0xe0, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x80, 0x79, 0xf0, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0x80, 0x79, 0xf0, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0x80, 0xf8, 0xf0, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0x80, 0xf0, 0xf8, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0x80, 0xf0, 0xf8, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0x81, 0xf0, 0xf8, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x81, 0xff, 0xfc, 0x07, 0xc0, 0x3e, 0x00, 0x01, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x81, 0xff, 0xfc, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x83, 0xff, 0xfc, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x83, 0xff, 0xfc, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x83, 0xc0, 0x3e, 0x07, 0xc0, 0x3e, 0x03, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x87, 0xc0, 0x3e, 0x07, 0xc0, 0x1f, 0xff, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x87, 0xc0, 0x1e, 0x07, 0xc0, 0x1f, 0xff, 0xe1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x07, 0x87, 0x80, 0x1f, 0x07, 0xc0, 0x1f, 0xff, 0xc1, 0xe0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xf8, 0x0f, 0x8f, 0x80, 0x1f, 0x07, 0xc0, 0x0f, 0xff, 0xc1, 0xf0, 0x1f, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


////////////////////////////////////////////////////////////////
//////////  VARIABLES AND LIBRARIES
////////////////////////////////////////////////////////////////

// OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //#define SSD1306_I2C_ADDRESS   0x3C    #define SSD1306_128_64
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

//NEOPIXEL SETUP
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// Assign Input Pins (Buttons and Light sensor)
#define BUTTON_A_PIN 4
#define BUTTON_B_PIN 3
#define BUTTON_C_PIN 2
#define BUTTON_D_PIN 5
#define BATTERY_VOLTAGE_PIN A6
#define LIGHT_SENSOR_PIN A7
#define BUZZER_PIN 8

// LED Pin Assignments
int RX_LED_PIN = 0;
int TX_LED_PIN = 1;
int OnBoardLED_PIN = 13;
int LED_1_PIN = 7;
int LED_2_PIN = 9;
int LED_3_PIN = 10;
int LED_4_PIN = 11;
int LED_5_PIN = 12;
int LED_6_PIN = A0;
int LED_7_PIN = A1;
int LED_8_PIN = A2;
int LED_9_PIN = A3;

int NewLEDArray[] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN, LED_6_PIN, LED_7_PIN, LED_8_PIN, LED_9_PIN, OnBoardLED_PIN, RX_LED_PIN, TX_LED_PIN};
const int NewLEDArrayLength = sizeof(NewLEDArray) / sizeof(NewLEDArray[0]);

// New and Old state variables used for Buttons
bool buttonAOldState = HIGH;
bool buttonBOldState = HIGH;
bool buttonCOldState = HIGH;
bool buttonDOldState = HIGH;
bool buttonANewState;
bool buttonBNewState;
bool buttonCNewState;
bool buttonDNewState;


// Variables Used for menu options
bool oledMainMenu = 0;
bool NeoPixelMenuSelected = 0;
bool LEDMenuSelected = 0;
bool LightSensorMenuSelected = 0;
bool TemperatureMenuSelected = 0;
bool BuzzerMenuSelected = 0;
bool SAOMenuSelected = 0;
bool DemoMenuSelected = 0;

// Variables used for scrolling through menus.  
byte NewMenuVar = 10;
byte NewerMenuVar = 0;
byte MenuCount = 10;
byte OldMenuVar = MenuCount + 1; 

int OnOffBool = 0;
int OnOffBool1 = 0;
int OnOffBool2 = 0;
int OnOffBool3 = 0;
int OnOffBool4 = 0;
int OnOffBool5 = 0;
int OnOffBool6 = 0;
int OnOffBool7 = 0;
int OnOffBool8 = 0;
int OnOffBool9 = 0;
int OnOffBool10 = 0;


// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Variables used to set the time manually on the trophy
int NewHour = 0;
int NewMinute = 0;
int NewSecond = 0;
int NewDate = 1;
int NewMonth = 1;
int NewYear = 2020;
double LeapYear = 1;

// Temperature Variables
float TempC = 0;
float TempF = 0;


////////////////////////////////////////////////////////////////
//////////  SETUP LOOP
////////////////////////////////////////////////////////////////


void setup () {
  
  //Start Serial for feedback on Serial Monitor
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Uncomment to set clock to the computer's time at time of compile
  /*
  else {
    DateTime now = rtc.now();
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second()));
  }
*/
  DateTime now = rtc.now();
  
  //begin neopixels
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(0, 0, 0), 0); // Turn Off
  
  //Setup input pins
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);
  pinMode(BUTTON_D_PIN, INPUT_PULLUP);
  pinMode(BATTERY_VOLTAGE_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  //Setup output pins
  pinMode(BUZZER_PIN,OUTPUT);
  
  for (int i = 0; i <= NewLEDArrayLength-1; i++) {
    pinMode(NewLEDArray[i],OUTPUT);
  }

  TurnOffAllLEDs();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // Show image buffer on the display hardware.
  //display.display();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();
  
}



////////////////////////////////////////////////////////////////
//////////  MAIN LOOP
////////////////////////////////////////////////////////////////


void loop () {

  // Check Each button to see if they have been pressed
  CheckButtons(); 
  MenuChange();

  //Asssignment needed for menu
  OldMenuVar = NewMenuVar; 
  
}



//////////////////////////////


////////////////////////////////////////////////////////////////
//////////  OTHER FUNCTIONS
////////////////////////////////////////////////////////////////



///////////////////////////////////////////
///////////////////////////////////////////

//Check Each Button
void CheckButtons(){
  CheckbuttonA();
  CheckbuttonB();
  CheckbuttonC();
  CheckbuttonD();
}

////////////////////////////////////////////////////////////////

void CheckbuttonA(){

    // Get current button state.
  buttonANewState = digitalRead(BUTTON_A_PIN);

  // Check if state changed from high to low (button press).
  if (buttonANewState == LOW && buttonAOldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    buttonANewState = digitalRead(BUTTON_A_PIN);
    if (buttonANewState == LOW) {
      // BUTTON PRESSED
     Serial.println("BUTTON A PRESSED");
     
      ////if (oledMainMenu == 1 || NeoPixelMenuSelected == 1 || TemperatureMenuSelected == 1 || LEDMenuSelected == 1 || DemoMenuSelected == 1){
        NewMenuVar = OldMenuVar + 1;
          if (NewMenuVar == MenuCount+1) {
              NewMenuVar = 1;
          }
         
          ////startQuadMenuCounter();
        ////}
     Serial.println("button done");
    }
    else {
      // BUTTON NOT PRESSED 
    }
  }

  // Set the last button state to the old state.
  buttonAOldState = buttonANewState;

}

////////////////////////////////////////////////////////////////

void CheckbuttonB(){

    // Get current button state.
  buttonBNewState = digitalRead(BUTTON_B_PIN);

  // Check if state changed from high to low (button press).
  if (buttonBNewState == LOW && buttonBOldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    buttonBNewState = digitalRead(BUTTON_B_PIN);
    if (buttonBNewState == LOW) {
      // BUTTON PRESSED
     Serial.println("BUTTON B PRESSED");
   
     //// if (oledMainMenu == 1 || NeoPixelMenuSelected == 1 || LEDMenuSelected ==1 || TemperatureMenuSelected == 1 || DemoMenuSelected == 1){        
        NewMenuVar = OldMenuVar - 1;
          if (NewMenuVar == 0) {
              NewMenuVar = MenuCount;
          }

     ////     startQuadMenuCounter();
     ////   }
     Serial.println("button done");
    }
    else {
      // BUTTON NOT PRESSED 
    }
  }

  // Set the last button state to the old state.
  buttonBOldState = buttonBNewState;

}

////////////////////////////////////////////////////////////////

void CheckbuttonC(){

    // Get current button state.
  buttonCNewState = digitalRead(BUTTON_C_PIN);

  // Check if state changed from high to low (button press).
  if (buttonCNewState == LOW && buttonCOldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    buttonCNewState = digitalRead(BUTTON_C_PIN);
    if (buttonCNewState == LOW) {
      // BUTTON PRESSED
     Serial.println("BUTTON C PRESSED");
     ////selectMenuItem();
     //oledMainMenu = 0;
     GoButtonC();
     Serial.println("button done"); 
    }
    else {
      // BUTTON NOT PRESSED 
    }
  }

  // Set the last button state to the old state.
  buttonCOldState = buttonCNewState;

}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void GoButtonC(){
        if (NewMenuVar == 1) {
            if (OnOffBool1 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 1; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else  {
                OnOffBool1 = 0;
              }   
          }
        else if (NewMenuVar == 2) {
            if (OnOffBool2 == 0) {
                OnOffBool2 = 1; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool2 = 0;
              }   
          } 
        else if (NewMenuVar == 3)
          {
            if (OnOffBool3 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 1; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else 
              {
                OnOffBool3 = 0;
              }   
          } 
        else if (NewMenuVar == 4) {
            if (OnOffBool4 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 1; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool4 = 0;
              }   
          } 
        else if (NewMenuVar == 5) {
            if (OnOffBool5 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 1; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool5 = 0;
              }   
          } 
        else if (NewMenuVar == 6) {
            if (OnOffBool6 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 1; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool6 = 0;
              }   
          }
        else if (NewMenuVar == 7) {
            if (OnOffBool7 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 1; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool7 = 0;
              }   
          }        
        else if (NewMenuVar == 8) {
            if (OnOffBool8 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 1; OnOffBool9 = 0; OnOffBool10 = 0;
              }
            else {
                OnOffBool8 = 0;
              }   
          }        
        else if (NewMenuVar == 9) {
            if (OnOffBool9 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 1; OnOffBool10 = 0;
              }
            else {
                OnOffBool9 = 0;
              }   
          }        
        else if (NewMenuVar == 10) {
            if (OnOffBool10 == 0) {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 1;
              }
            else {
                OnOffBool10 = 0;
              }   
          }       
        else {
                OnOffBool2 = 0; OnOffBool1 = 0; OnOffBool3 = 0; OnOffBool4 = 0; OnOffBool5 = 0; OnOffBool6 = 0; OnOffBool7 = 0; OnOffBool8 = 0; OnOffBool9 = 0; OnOffBool10 = 0;
              }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


void CheckbuttonD(){

    // Get current button state.
  buttonDNewState = digitalRead(BUTTON_D_PIN);

  // Check if state changed from high to low (button press).
  if (buttonDNewState == LOW && buttonDOldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    buttonDNewState = digitalRead(BUTTON_D_PIN);
    if (buttonDNewState == LOW) {
      // BUTTON PRESSED
     Serial.println("BUTTON D PRESSED");
    oledMainMenu = 1;
    //changeEPDToMainMenu();
    ////printEPDMenu("MAIN", "NEOPIXELS", "LIGHT SENSOR", "TEMPERATURE SENSOR", "ACCELEROMETER", "DEMO MODE", " ", 1);
    ////startQuadMenuCounter();
    Serial.println("button done");
    }
    else {
      // BUTTON NOT PRESSED 
    }
  }

  // Set the last button state to the old state.
  buttonDOldState = buttonDNewState;

}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


void MenuChange() {
  
         if (NewMenuVar == MenuCount+1) {
              NewMenuVar = 1;
             }
         
         if (NewMenuVar == 0) {
            NewMenuVar = MenuCount;
          }
      
        if (NewMenuVar == 1)
          {
                OnOffBool = OnOffBool1;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool1 == 0) {
                display.println("CLOCK ");
                ////display.drawCircle(120, 7, 5, WHITE); //OFF
                ////ReadTimeOnCurieForDisplay();
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW  ");
              }
            else {
             ///// display.println("CLOCK ");
              ////display.fillCircle(120, 7, 5, WHITE);  //ON
              //delay(2000);
              DisplayClockAndTemp();
            }
                display.display();    
          } 
        else if (NewMenuVar == 2)
          {
                OnOffBool = OnOffBool2;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool2 == 0) {
                display.println("SET CLOCK ");
                ////display.drawCircle(120, 7, 5, WHITE); //OFF
                ////ReadTimeOnCurieForDisplay();
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO CHANGE  ");
              }
            else {
              ////display.println("SET CLOCK ");
              ////display.fillCircle(120, 7, 5, WHITE);  //ON
              GoSetTime();
            }
                display.display();    
          }           
        else if (NewMenuVar == 3)
          {
                OnOffBool = OnOffBool3;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool3 == 0) {
                display.println("VIEW TEMP ");
                ////display.drawCircle(120, 7, 5, WHITE); //OFF
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW  ");
              }
            else {
              ////display.println("   ");
              ////display.fillCircle(120, 7, 5, WHITE);  //ON
              ////GoDetectTap();
              GetTemperature();
              DisplayTempOnScreen();
              
            }
                display.display();    
          }             
        else if (NewMenuVar == 4)
          {
                OnOffBool = OnOffBool4;  
                
                //display.clearDisplay();
                //display.setTextSize(2);
                //display.setCursor(0,0);
            if (OnOffBool4 == 0) {
              display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
                display.println("LITE SENSE");
                //display.drawCircle(120, 7, 5, WHITE); //OFF
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW ");
                display.display();                   
              }
            else {
              ////display.println("LITE SENSE");
              //display.fillCircle(120, 7, 5, WHITE);  //ON
              ////GoLEDPlay();
               DisplayLightSensor();
            }
                //display.display();    
          } 
        else if (NewMenuVar == 5)
          {
                OnOffBool = OnOffBool5;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool5 == 0) {
                display.println("NEOPIXELS ");
                //display.drawCircle(120, 7, 5, WHITE); //OFF
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW  ");  
              }
            else {
              display.println("NEOPIXELS ");
              display.setTextSize(1);
              display.println("WOW... LEDs..."); 
              display.display();
              //display.fillCircle(120, 7, 5, WHITE);  //ON
              ////GoDetectFreeFall();
              StartNeoPixels();
            }
                display.display();     
          } 
        else if (NewMenuVar == 6)
          {
                OnOffBool = OnOffBool6;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool6 == 0) {
                display.println("BUZZER ");
                ////display.drawCircle(120, 7, 5, WHITE); //OFF
                 display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW  "); 
              }
            else {
              display.println("BUZZER ");
              display.setTextSize(1);
              display.println("SONG ");
              display.display();
              ////display.fillCircle(120, 7, 5, WHITE);  //ON
              ////GoDetectMotion();
              PlayMarioSong();
            }
                display.display();    
          } 
        else if (NewMenuVar == 7)
          {
                OnOffBool = OnOffBool7;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool7 == 0) {
                display.println("LEDs");
                //display.drawCircle(120, 7, 5, WHITE); //OFF
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO VIEW  ");              }
            else {
              display.println("LEDs");
              ////display.fillCircle(120, 7, 5, WHITE);  //ON           
              ////LogRawIMUData();
              StartLEDSequence();
            }
                display.display();     
          } 
        else if (NewMenuVar == 8)
          {
                OnOffBool = OnOffBool8;
            if (OnOffBool8 == 0) {
                display.clearDisplay();
                display.setCursor(0,0);
                display.setTextSize(2);
                display.println("BATTERY");
                display.setTextSize(1);
                display.println("PRESS C TO VIEW  ");   
                display.display();             
              }
            else {  
                goViewBattery();
                //display.display(); 
            }
                //display.display();    
          } 
        else if (NewMenuVar == 9)
          {
                OnOffBool = OnOffBool9;  
                
                display.clearDisplay();
                display.setTextSize(2);
                display.setCursor(0,0);
            if (OnOffBool9 == 0) {
                display.println("DEMO MODE");
                //display.drawCircle(120, 7, 5, WHITE); //OFF
                display.setTextSize(1);
                ////display.setCursor(12,55);
                display.println("PRESS C TO ACTIVATE"); 
                display.println("PRESS RESET TO EXIT");
                //display.println("   PRESS RESET BUTTON");
              }
            else {
              display.println("DEMO MODE");
              //display.fillCircle(120, 7, 5, WHITE);  //ON
               display.setTextSize(1);
                ////display.setCursor(12,55);
               // display.println("PRESS C TO ACTIVATE"); 
                display.println("PRESS RESET TO EXIT");
              StartDemoMode();
            };
                display.display();     
          }           
        else if (NewMenuVar == 10)
          {
                OnOffBool = OnOffBool10;  
                
                //display.clearDisplay();
                //display.setTextSize(2);
                //display.setCursor(0,0);
            if (OnOffBool10 == 0) {
//                display.println("PLACEHOLDER");
//                display.drawCircle(120, 7, 5, WHITE); //OFF
//                display.setCursor(0,20);
//                display.print("PRESS 2       ");
//                display.setCursor(0,36);
//                display.print("TO START      ");    
                goToAwardMenu(); 
              }
            else {
              //display.println("PLACEHOLDER");
              //display.fillCircle(120, 7, 5, WHITE);  //ON
              ////GoDetectStep();
              goToAwardMenu();
            }
                //display.display();     
          }               
          
          else 
              {
               // OnOffBool1 = 0;
              }  

  //delay(100);        
}



/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void StartDemoMode(){
  int demodelay = 2000;
  int theaterChaseDelay = 100;
  int neoPixelIntensity = 64; // (255 is max, 0 is min)

  StartLEDSequence();
  display.clearDisplay(); // Make sure the display is cleared
  display.drawBitmap(0, 0, HudsonAlphaBitmap, 128, 32, WHITE);
  display.display();
  //delay(3000);

  theaterChase(strip.Color(0, 0, neoPixelIntensity), theaterChaseDelay); // blue
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  display.clearDisplay(); // Make sure the display is cleared
  display.drawBitmap(0, 0, UrbanEngineBitmap, 128, 32, WHITE);
  display.display();
  //delay(3000);

  theaterChase(strip.Color(0, neoPixelIntensity, 0), theaterChaseDelay); // blue
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
  
  //colorWipe(strip.Color(0, 0, 255), 200); // blue

  StartLEDSequence();
  display.clearDisplay(); // Make sure the display is cleared
  display.drawBitmap(0, 0, AcclinateBitmap, 128, 32, WHITE);
  display.display();
  //delay(3000);

  theaterChase(strip.Color(neoPixelIntensity, 0, 0), theaterChaseDelay); // red
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  display.clearDisplay();
  display.setCursor(1,10);
  display.setTextSize(3);
  display.println("PRESENT");
  display.display();
  //delay(3000);

  theaterChase(strip.Color(neoPixelIntensity, neoPixelIntensity, neoPixelIntensity), theaterChaseDelay); // white
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  display.clearDisplay(); // Make sure the display is cleared// drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(0, 0, HATCH2020Bitmap, 128, 32, WHITE);
  display.display();
  //delay(3000);

  theaterChase(strip.Color(0, 0, neoPixelIntensity), theaterChaseDelay); // Blue
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(2);
  display.println("HACK THIS");
  display.println("TROPHY !!!");
  display.display();
  //delay(3000);

  theaterChase(strip.Color(neoPixelIntensity, neoPixelIntensity, neoPixelIntensity), theaterChaseDelay); // white
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  //delay(1000); // wait for console opening

  StartLEDSequence();
  
  goToAwardMenu();
  delay(demodelay);

  StartLEDSequence();
  rainbow2(100);
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  PlaySong();
  delay(demodelay);
  
  //StartLEDSequence();
  //delay(demodelay);

  StartLEDSequence();
  DisplayLightSensorForDemo();

  StartLEDSequence();
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(2);
  display.println("HACK THIS");
  display.println("TROPHY !!!");
  display.display();

  delay(demodelay);

  StartLEDSequence();
  rainbowCycle2(20); //20
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  DisplayClockForDemo();
  delay(demodelay);

  StartLEDSequence();
  theaterChaseRainbow2(50); //50
  colorWipe(strip.Color(0, 0, 0), 0);    // Black/off

  StartLEDSequence();
  DisplayTempForDemo();
  delay(demodelay);

  StartLEDSequence();

  //OnOffBool9 = 0;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void goViewBattery(){

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("BATTERY VOLTAGE");
    
  for(int i=0; i<20; i++){
    display.setCursor(0,10);
    display.setTextSize(3);
    display.print(getBatteryVoltage());
    display.println(" V  ");
    display.display();
    delay(100);
  }
  OnOffBool8 = 0;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////


float getBatteryVoltage() {
    float measuredvbat = analogRead(BATTERY_VOLTAGE_PIN);

    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 5;  // Multiply by 5V, our reference voltage
    measuredvbat /= 1024; // convert to voltage

    return measuredvbat;
}  

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void StartNeoPixels(){
  colorWipe(strip.Color(255, 0, 0), 50);  // Red
  colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
  colorWipe(strip.Color(0, 255, 0), 50);  // Green
  colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
  colorWipe(strip.Color(0, 0, 255), 50);  // Blue
  colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
  
  OnOffBool5 = 0;
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////


void PlaySong(){
  tone(8, 400, 200);
  //delay(1000);
  //noTone(8);
  OnOffBool6 = 0;
}

/*
 *   NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 */

void PlayMarioSong(){
  
  byte toneduration = 120;
  byte tonedelay = toneduration * 1.3;
  
  tone(8, NOTE_E7, toneduration);
  delay(tonedelay);
  tone(8, NOTE_E7, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, NOTE_E7, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, NOTE_C7, toneduration);
  delay(tonedelay);
  tone(8, NOTE_E7, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, NOTE_G7, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, NOTE_G6, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  tone(8, 0, toneduration);
  delay(tonedelay);
  OnOffBool6 = 0;
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void TurnOffAllLEDs() {
  for (int i = 0; i <= NewLEDArrayLength; i++) {
    digitalWrite(NewLEDArray[i],LOW);
  }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void StartLEDSequence(){
  TurnOffAllLEDs();
  delay(200);
  for (int i = 0; i <= NewLEDArrayLength-2; i++) {
    digitalWrite(NewLEDArray[i],HIGH);
    delay(100);
  }
  TurnOffAllLEDs();
  OnOffBool7 = 0;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void DisplayTempOnScreen(){
  display.setTextSize(2);
  display.print(TempF);
  display.println(" F");
  display.setTextSize(2);
  display.print(TempC);
  display.println(" C     ");
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void DisplayLightSensor(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  //display.setTextSize(2);
  display.print("VALUE ");
  display.print(analogRead(LIGHT_SENSOR_PIN));
  display.println(" ");
  display.setTextSize(1);
  display.println("MIN (DARK): 0   ");
  display.println("MAX (BRIGHT): 1023     ");
  display.display();
}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void DisplayLightSensorForDemo(){
  
  for (int i=0; i < 100; i++){
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10,0);
    display.println("LIGHT SENSOR VALUE");
    display.setCursor(35,10);
    display.setTextSize(3);
    display.print(analogRead(LIGHT_SENSOR_PIN));
    display.println(" ");
    display.display();
    delay(50);
  }
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void GoSetTime() {

  //delay(100);
  
  DateTime now = rtc.now();

  NewHour = now.hour();
  NewMinute = now.minute();
  NewSecond = now.second();
  NewDate = now.day();
  NewMonth = now.month();
  NewYear = now.year();

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("HOUR: ");
  display.display();

  //delay(50);

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
          ////display.setCursor(0,35);
          ////display.print("    ");
        NewHour++;
        if (NewHour > 23) {
       // delay(1000);
       NewHour = 0;
       Serial.println(NewHour);
       delay(50);
        }
      }
            if (digitalRead(BUTTON_A_PIN) == LOW) {
          ////display.setCursor(0,35);
          ////display.print("    ");
        NewHour--;
        if (NewHour < 0) {
       // delay(1000);
       NewHour = 23;
       Serial.println(NewHour);
       delay(50);
        }
      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewHour));
    print2digitsDisplay(NewHour);
    display.println("");
    ////display.print("    ");
    //delay(1000);
    display.display();
    
    delay(100); //DEBOUNCE
  }

  display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(2);
 display.print("MINUTE:           ");

delay(500);

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewMinute++;
        if (NewMinute > 59) {
       // delay(1000);
       NewMinute = 0;
       delay(50);
        }
      }
        if (digitalRead(BUTTON_A_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewMinute--;
        if (NewMinute < 0) {
       // delay(1000);
       NewMinute = 59;
       delay(50);
        }
      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewMinute));
    print2digitsDisplay(NewMinute);
    display.println("");
    //delay(1000);
    display.display();

    delay(100);  // DEBOUNCE
  }

  display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(2);
 display.print("SECOND:           ");

delay(500);

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
         //// display.setCursor(0,35);
        ////  display.print("    ");
        NewSecond++;
        if (NewSecond > 59) {
       // delay(1000);
       NewSecond = 0;
       delay(50);
        }
      }
        if (digitalRead(BUTTON_A_PIN) == LOW) {
         //// display.setCursor(0,35);
        ////  display.print("    ");
        NewSecond--;
        if (NewSecond < 0) {
       // delay(1000);
       NewSecond = 59;
       delay(50);
        }
      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewSecond));
    print2digitsDisplay(NewSecond);
    display.println("");
    display.display();

    delay(100);
  }
  
  display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(2);
 display.print("YEAR:");

delay(500);

 
  
if (NewYear < 2021) {
  NewYear = 2020;
}

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewYear++;
        if (NewYear > 2030) {
       // delay(1000);
       NewYear = 2020;
       delay(50);
        }
      }
        if (digitalRead(BUTTON_A_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewYear--;
        if (NewYear < 2020) {
       // delay(1000);
       NewYear = 2030;
       delay(50);
        }
      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewYear));
    print2digitsDisplay(NewYear);
    display.println("");
    display.display();

    delay(100);
  }

 display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(2);
 display.print("MONTH:");

delay(500);

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
         // display.setCursor(0,35);
         // display.print("    ");
        NewMonth++;
        if (NewMonth > 12) {
       // delay(1000);
       NewMonth = 1;
       delay(50);
        }
      }
        if (digitalRead(BUTTON_A_PIN) == LOW) {
         // display.setCursor(0,35);
         // display.print("    ");
        NewMonth--;
        if (NewMonth < 1) {
       // delay(1000);
       NewMonth = 12;
       delay(50);
        }
      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewMonth));
    print2digitsDisplay(NewMonth);
    display.println("");
    display.display();

    delay(100);
  }

 display.clearDisplay();
 display.setCursor(0,0);
 display.setTextSize(2);
 display.print("DATE:");

delay(500);

  while (digitalRead(BUTTON_D_PIN) == HIGH) {
        if (digitalRead(BUTTON_B_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewDate++;
        if (NewMonth == 1 || NewMonth == 3 || NewMonth == 5 || NewMonth == 7 || NewMonth == 8 || NewMonth == 10 || NewMonth == 12 ) {

             if (NewDate > 31) {
             NewDate = 1;
       delay(50);
            }
        }
        else if (NewMonth == 4 || NewMonth == 6 || NewMonth == 9 || NewMonth == 11) {
             
             if (NewDate > 30) {
             NewDate = 1;
       delay(50);
            }
        }
        else if (NewMonth == 2) {

             LeapYear = NewYear % 4;

             if (LeapYear == 0) {
                   if (NewDate > 29) {
                   NewDate = 1;
       delay(50);
                  }
             }
            else {

                   if (NewDate > 28) {
                   NewDate = 1;
       delay(50);
                  }
            }
        }
        else {
          //
        }

      }
if (digitalRead(BUTTON_A_PIN) == LOW) {
          //display.setCursor(0,35);
          //display.print("    ");
        NewDate--;
        if (NewMonth == 1 || NewMonth == 3 || NewMonth == 5 || NewMonth == 7 || NewMonth == 8 || NewMonth == 10 || NewMonth == 12 ) {

             if (NewDate < 1) {
             NewDate = 31;
       delay(50);
            }
        }
        else if (NewMonth == 4 || NewMonth == 6 || NewMonth == 9 || NewMonth == 11) {
             
             if (NewDate < 1) {
             NewDate = 30;
       delay(50);
            }
        }
        else if (NewMonth == 2) {

             LeapYear = NewYear % 4;

             if (LeapYear == 0) {
                   if (NewDate < 1) {
                   NewDate = 29;
       delay(50);
                  }
             }
            else {

                   if (NewDate < 1) {
                   NewDate = 28;
       delay(50);
                  }
            }
        }
        else {
          //
        }

      }
    display.setCursor(0,15);
    display.setTextSize(2);
    //display.println(print2digitsDisplay(NewDate));
    print2digitsDisplay(NewDate);
    display.println("");
    display.display();

    delay(100);
  }

delay(100);
  
////setTime(NewHour, NewMinute, NewSecond, NewDate, NewMonth, NewYear);
////delay(100);
rtc.adjust(DateTime(NewYear, NewMonth, NewDate, NewHour, NewMinute, NewSecond));

delay(100);

display.clearDisplay();
display.setCursor(0,0);
display.setTextSize(2);
display.println("CLOCK SET!");
display.display();

delay(500);

////BlueEnding();

OnOffBool2 = 0;

}


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

   
void selectMenuItem(){

  if (oledMainMenu == 1){
          if (NewMenuVar == 1) {
            NeoPixelMenuSelected = 1;
            LightSensorMenuSelected = 0;
            TemperatureMenuSelected = 0;
            //AccelMenuSelected = 0;
            DemoMenuSelected = 0;
            
            //goToNeoPixelMenu();
            ////printEPDMenu("NEOPIXEL", "COLOR WIPE", "RAINBOW", "RAINBOW CYCLE", "THEATER CHASE", "RAINBOW CHASE", "SHOW MODE", 1);
          } 
        else if (NewMenuVar == 2) {
            NeoPixelMenuSelected = 0;
            LightSensorMenuSelected = 1;
            TemperatureMenuSelected = 0;
            //AccelMenuSelected = 0;
            DemoMenuSelected = 0;
            
            //goToLightSensorMenu();
            ////printEPDMenu("LIGHT SENSOR", "SEE DISPLAY BELOW", "FOR SENSOR VALUE", " ", "0 IS MIN", "1024 IS MAX", " ", 0);
          }     
        else if (NewMenuVar == 3) {
            NeoPixelMenuSelected = 0;
            LightSensorMenuSelected = 0;
            TemperatureMenuSelected = 1;
            //AccelMenuSelected = 0;
            //QuadMenuSelected = 0;
            DemoMenuSelected = 0;

            //goToTemperatureMenu();
            ////printEPDMenu("TEMPERATURE", "SEE DISPLAY BELOW", "FOR TEMPERATURE", " ", "(IN DEGREES F)", " ", " ", 0);
          }  
         else if (NewMenuVar == 4) {

            NeoPixelMenuSelected = 0;
            LightSensorMenuSelected = 0;
            TemperatureMenuSelected = 0;
            //AccelMenuSelected = 1;
            //QuadMenuSelected = 0;
            DemoMenuSelected = 0;
            
            //goToAccelMenu();
            ////printEPDMenu("ACCELEROMETER", "X ACCELERATION", "Y ACCELERATION", "Z ACCELERATION", " ", " ", " ", 1);
          }              
          else if (NewMenuVar == 5) {
            NeoPixelMenuSelected = 0;
            LightSensorMenuSelected = 0;
            TemperatureMenuSelected = 0;
            //AccelMenuSelected = 0;
            //QuadMenuSelected = 0;
            DemoMenuSelected = 1;
            
           // goToAwardMenu2(1);
          }   
          
          else if (NewMenuVar == 6) {
              return;
          }               
           else  {
               // done
          }  
     oledMainMenu = 0;
  }
   
  if (NeoPixelMenuSelected == 1){
          if (NewMenuVar == 1) {
              colorWipe(strip.Color(255, 0, 0), 50);  // Red
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(0, 255, 0), 50);  // Green
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(0, 0, 255), 50);  // Blue
              colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
              colorWipe(strip.Color(255, 255, 255), 50);  // Blue
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          } 
        else if (NewMenuVar == 2) {
              rainbow(20);
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          }     
        else if (NewMenuVar == 3) {
              rainbowCycle(20);
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          }  
         else if (NewMenuVar == 4) {
              theaterChase(strip.Color(127, 127, 127), 50); // White
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChase(strip.Color(127,   0,   0), 50); // Red
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
              theaterChase(strip.Color(  0,   0, 127), 50); // Blue
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          }              
          else if (NewMenuVar == 5) {
              theaterChaseRainbow(50);
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          }   
          else if (NewMenuVar == 6) {
              ////showModeAndQuad(50,0);
              colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
          }                      
           else  {
               // done
          }  
////    quadDisplayString("----");    
  }
  if (LightSensorMenuSelected == 1){
    for (int i = 0; i < 100; i++)  {
////       printLEDNumber(analogRead(LIGHT_SENSOR_PIN)); 
       delay(150);     
    }
////    quadDisplayString("----");   
  }
  if (TemperatureMenuSelected == 1){
    for (int i = 0; i < 100; i++)  {
////       printLEDNumber(checkTempF()); 
       delay(150);     
    }
////    quadDisplayString("----");   
  }

    /*
    if (AccelMenuSelected == 1){
          if (NewMenuVar == 1) {
               for (int i = 0; i < 100; i++)  {
                 printLEDNumber(checkXaccel()); 
                 delay(150);     
              }
          } 
        else if (NewMenuVar == 2) {
               for (int i = 0; i < 100; i++)  {
                 printLEDNumber(checkYaccel()); 
                 delay(150);     
              }
          }     
        else if (NewMenuVar == 3) {
              for (int i = 0; i < 100; i++)  {
                 printLEDNumber(checkZaccel()); 
                 delay(150);     
              }
          }
        else if (NewMenuVar == 4) {
          }  
        else if (NewMenuVar == 5) {
          }  
        else if (NewMenuVar == 6) {
          }                        
           else  {
               // done
          }  
    quadDisplayString("----");    
  }

  */
}

////////////////////////////////////////////////////////////////

void startQuadMenuCounter(){
          if (NewMenuVar == MenuCount+1) {
              NewMenuVar = 1;
             }
         
         if (NewMenuVar == 0) {
            NewMenuVar = MenuCount;
          }
        if (NewMenuVar == 1) {
            ////printLEDString("1");
          } 
        else if (NewMenuVar == 2) {
            ////printLEDString("2");
          }     
        else if (NewMenuVar == 3) {
           //// printLEDString("3");
          }  
         else if (NewMenuVar == 4) {
           //// printLEDString("4");
          }              
          else if (NewMenuVar == 5) {
           //// printLEDString("5");
          }   
          else if (NewMenuVar == 6) {
           //// printLEDString("6");
          }                      
           else  {
               // done
          }   
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


/*
String print2digitsDisplay(int number) {
  if (number >= 0 && number < 10) {
    return (String("0" + String(number)));
  }
  else {
    return (String(number));
  }
}
*/

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void print2digitsDisplay(int number) {
  if (number >= 0 && number < 10) {
    display.print('0');
  }
  display.print(number);
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void GetTemperature(){
  TempC = rtc.getTemperature();
  TempF = (TempC*1.8)+32;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void DisplayClockForDemo(){
  
  DateTime now = rtc.now();
  display.clearDisplay();
  display.setCursor(0, 7);
  display.setTextSize(3); 
  display.print(" ");
  //display.print(print2digitsDisplay(now.hour()));
  print2digitsDisplay(now.hour());
  display.print(":");
  //display.println(print2digitsDisplay(now.minute()));
  print2digitsDisplay(now.minute());
  display.println("");
  display.display();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void DisplayTempForDemo(){
    GetTemperature();
    display.clearDisplay();
    display.setCursor(0, 7);
    display.setTextSize(3);
    //display.println(TempC); display.setCursor(105, 7); display.print("C");// Uncomment to display Celsius
    display.print(TempF); display.setCursor(105, 7); display.print("F"); // Uncomment to display Fahrenheit
    display.drawCircle(95, 9, 3, WHITE); //OFF
    display.display();
  }
  
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void DisplayClockAndTemp(){

  GetTemperature();
  
  DateTime now = rtc.now();

/*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */
    
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(" Temp: ");
  //display.println(TempC); // Uncomment to display Celsius
  display.println(TempF); // Uncomment to display Fahrenheit
  
  //second row
  display.setTextSize(2); 
  //display.print(print2digitsDisplay(now.hour()));
  print2digitsDisplay(now.hour());
  display.print(":");
  //display.print(print2digitsDisplay(now.minute()));
  print2digitsDisplay(now.minute());
  display.print(":");
  //display.println(print2digitsDisplay(now.second()));
  print2digitsDisplay(now.second());
  display.println("");
  
  //third row
  display.setTextSize(1);
  //display.print(print2digitsDisplay(now.month()));
  print2digitsDisplay(now.month());
  display.print("/");
  //display.print(print2digitsDisplay(now.day()));
  print2digitsDisplay(now.day());
  display.print("/");
  display.print(now.year(), DEC);
  display.println("           ");
  display.display();
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

void goToAwardMenu(){
  display.clearDisplay();
  display.setCursor(0, 0);

  if (awardtype == 0){
    //DEMO MODE
    display.setCursor(12, 10);
    display.setTextSize(2);
    display.println("DEMO MODE");
  }
  else if (awardtype == 1){
    //HIGH SCHOOL FIRST PLACE
    display.setCursor(35, 5);
    display.setTextSize(1);
    display.println("HIGH SCHOOL");
    display.setCursor(15, 18);
    display.setTextSize(2);
    display.println("1st PLACE");   
  }
  else if (awardtype == 2){
    //HIGH SCHOOL SECOND PLACE
    display.setCursor(35, 5);
    display.setTextSize(1);
    display.println("HIGH SCHOOL");
    display.setCursor(15, 18);
    display.setTextSize(2);
    display.println("2nd PLACE");
  }
  else if (awardtype == 3){
    //PROFESSIONAL FIRST PLACE
    display.setCursor(35, 5);
    display.setTextSize(1);
    display.println("PROFESSIONAL");
    display.setCursor(15, 18);
    display.setTextSize(2);
    display.println("1st PLACE");
  }
  else if (awardtype == 4){
    //PROFESSIONAL SECOND PLACE
    display.setCursor(35, 5);
    display.setTextSize(1);
    display.println("PROFESSIONAL");
    display.setCursor(15, 18);
    display.setTextSize(2);
    display.println("2nd PLACE");
  }
  else if (awardtype == 5){
    //PROFESSIONAL THIRD PLACE
    display.setCursor(35, 5);
    display.setTextSize(1);
    display.println("PROFESSIONAL");
    display.setCursor(15, 18);
    display.setTextSize(2);
    display.println("3rd PLACE");
  }
  else if (awardtype == 6){
    //HUDSON ALPHA
    display.drawBitmap(0, 0, HudsonAlphaBitmap, 128, 32, WHITE);
  }
  else if (awardtype == 7){
    //URBAN ENGINE
    display.drawBitmap(0, 0, UrbanEngineBitmap, 128, 32, WHITE);
  }  
  else if (awardtype == 8){
    //ACCLINATE GENETICS
    display.drawBitmap(0, 0, AcclinateBitmap, 128, 32, WHITE);
  }
  else if (awardtype == 9){
    //HATCH
    display.drawBitmap(0, 0, HATCH2020Bitmap, 128, 32, WHITE);
  }
  else {
    //do nothing
    //PLACE HOLDER
  }
  display.display();        
}

////////////////////////////////////////////////////////////////
//      NEOPIXEL FUNCTIONS
////////////////////////////////////////////////////////////////

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow2(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<60; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel2((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle2(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<60*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel2(((i * 60 / strip.numPixels()) + j) & 60));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow2(uint8_t wait) {
  for (int j=0; j < 60; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel2( (i+j) % 60));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel2(byte WheelPos) {
  WheelPos = 60 - WheelPos;
  if(WheelPos < 20) {
    return strip.Color(60 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 40) {
    WheelPos -= 20;
    return strip.Color(0, WheelPos * 3, 60 - WheelPos * 3);
  }
  WheelPos -= 40;
  return strip.Color(WheelPos * 3, 60 - WheelPos * 3, 0);
}
