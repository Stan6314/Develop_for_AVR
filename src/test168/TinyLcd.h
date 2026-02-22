/* TinyLcd v1

   Small library for output to character display with HD44780 controller
   Implemented write only mode and needs 6 output pins on microcontroller

   Stan6314
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/
#ifndef TinyLcd
#define TinyLcd

// ******** Bit manipulation definitions ***********
// Write only, 4 bit bus and R/W pin must be GND
#define SETDISP_PORT DDRD |= 0xFC

#define DISP_E_0 PORTD &= ~(1<<3)  // LCD signals definition
#define DISP_E_1 PORTD |= 1<<3
#define DISP_INST PORTD &= ~(1<<2)
#define DISP_DATA PORTD |= 1<<2
#define DISP_DB7_0 PORTD &= ~(1<<7)
#define DISP_DB7_1 PORTD |= 1<<7
#define DISP_DB6_0 PORTD &= ~(1<<6)
#define DISP_DB6_1 PORTD |= 1<<6
#define DISP_DB5_0 PORTD &= ~(1<<5)
#define DISP_DB5_1 PORTD |= 1<<5
#define DISP_DB4_0 PORTD &= ~(1<<4)
#define DISP_DB4_1 PORTD |= 1<<4

// Display type - define MAXCHARS x MAXLINES
// LCD 2x16 chars
#define MAXCHARS 16 
#define MAXLINES 2

// Delay for display instructions
#define Delay1u _delay_us(1)
#define Delay50u _delay_us(50)
#define Delay2ms _delay_ms(2)

// Init port and display
void InitDisplay();

// Write null terminated string to display
void WriteText(unsigned char *character);

// Write one character to display
void WriteChar(unsigned char character);

// Set cursor position
void SetDispPos(uint8_t Xpos, uint8_t Ypos);

// Clear display, set position 0,0
void ClrDisp();

#endif
