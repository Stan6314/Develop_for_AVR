/* TinyLcd v1

   Stan6314
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "TinyLcd.h"

// ************** Display ******************
// Write data to display - 4 bits bus
void WriteCom(uint8_t codedat)
{
	if(codedat & 0x80) DISP_DB7_1; else DISP_DB7_0;
	if(codedat & 0x40) DISP_DB6_1; else DISP_DB6_0;
	if(codedat & 0x20) DISP_DB5_1; else DISP_DB5_0;
	if(codedat & 0x10) DISP_DB4_1; else DISP_DB4_0;
	// Write upper nibble
	DISP_E_1;
	Delay1u;
	DISP_E_0;
	if(codedat & 0x08) DISP_DB7_1; else DISP_DB7_0;
	if(codedat & 0x04) DISP_DB6_1; else DISP_DB6_0;
	if(codedat & 0x02) DISP_DB5_1; else DISP_DB5_0;
	if(codedat & 0x01) DISP_DB4_1; else DISP_DB4_0;
	// Write lower nibble
	DISP_E_1;
	Delay1u;
	DISP_E_0;
	Delay50u;
}

// Write instruction code to display
void WriteIns(uint8_t codein)
{
	DISP_INST;	// Set display for instruction
	WriteCom(codein);
}

// Write data (char) to display
void WriteChar(uint8_t codein)
{
	DISP_DATA;	// Set display for data
	WriteCom(codein);
}

void InitDisplay()
{
    SETDISP_PORT;
// Display is 8bit after power-on so confirm it or change it to 
// this default state. Start must be clearly defined
	DISP_E_0;
	Delay2ms;
// Set 8 bit communication
	DISP_E_0;
	DISP_INST;
	DISP_DB7_0;
	DISP_DB6_0;
	DISP_DB5_1;
	DISP_DB4_1;
	DISP_E_1;
	Delay1u;
	DISP_E_0;
	Delay50u;
	DISP_DB7_0;	// This is only second half or empty command
	DISP_DB6_0;
	DISP_DB5_0;
	DISP_DB4_0;
	DISP_E_1;
	Delay1u;
	DISP_E_0;
	Delay2ms;
// Set 4 bit communication
	DISP_E_0;
	DISP_DB7_0;
	DISP_DB6_0;
	DISP_DB5_1;
	DISP_DB4_0;
	DISP_E_1;
	Delay1u;
	DISP_E_0;
	Delay2ms;
// Set 2 line, 4 bit communication, font 5x7
	WriteIns(0x28);
// Set 2 line, 4 bit communication, font 5x7
	WriteIns(0x28);
// Display ON, Cursor OFF, Blink on cursor OFF
	WriteIns(0x0C);
// Reset display, Set cursor 0,0 position
	WriteIns(0x01);
	Delay2ms;
// Set cursor increment
	WriteIns(0x06);
}

// Write null terminated string to display
void WriteText(unsigned char *character)
{
   while(*character) {
   		WriteChar(*character);
		character++;
	}
}

// Set cursor position
void SetDispPos(uint8_t Xpos, uint8_t Ypos)
{
	if((Xpos>=MAXCHARS) || (Ypos>=MAXLINES)) return;
	if(Ypos) WriteIns(Xpos | 0xC0);
		else WriteIns(Xpos | 0x80);
}

// Clear display, set position 0,0
void ClrDisp()
{
// Reset display, Set cursor 0,0 position
	WriteIns(0x01);
	Delay2ms;
}

