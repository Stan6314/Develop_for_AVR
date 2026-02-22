/*
    This is just example program for using AVR GCC with different microcontrollers
    - One LED is blinking on the port pin
    - Expander PCF8574T on default I2C bus drives 7 LEDs and its MSB bit stops output changes
    - Display with HD44780 controller connected to 6 bits of port changes one character
     Pins for display driving are defined in TinyLcd.h
     
    This is version for ATtiny414
    
    For change to another type don't forget to edit .h files of the libraries

*/

// Default clock source is internal 20MHz RC oscillator (defined in makefile)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include "TinyLcd.h"
#include "TinyI2CMaster.h"


// Write one byte to PCF8574T
void SendToPCF8574T(uint8_t data)
{
    TinyI2CMaster_start(0x20,0);
    TinyI2CMaster_write(data);
    TinyI2CMaster_stop();
}
// Read one byte from PCF8574T
unsigned char ReadFromPCF8574T(void)
{
    TinyI2CMaster_start(0x20,1);
    uint8_t data=TinyI2CMaster_read();
    TinyI2CMaster_stop();
    return data;
}

uint8_t DisChar=0x20;
unsigned char Text[] = "Chars";

int main()
{
    // Set oscillator - internal 20 MHz
    _delay_ms(2);
    ccp_write_io((void*) &(CLKCTRL.MCLKCTRLA), CLKCTRL_CLKSEL_OSC20M_gc); // 20MHz Internal Oscillator (OSC20M)
    ccp_write_io((void*) &(CLKCTRL.MCLKCTRLB), ~CLKCTRL_PEN_bm);  // Prescaler disabled
    
    PORTA.DIR |= 0x2;   // LED is on PortD bit 7
    TinyI2CMaster_init();
    _delay_ms(50);
    InitDisplay();
    SetDispPos(1,0);    // Write text on upper line
    WriteText(Text);
    while (1)
    {
        if(ReadFromPCF8574T() & 0x80) SendToPCF8574T(DisChar | 0x80);  // Change LEDS if enabled
        SetDispPos(1,1);        // Character to display
        WriteChar(DisChar++);
        if(DisChar < 0x20) DisChar = 0x20;
        PORTA.OUTTGL = 0x02;        // Blink LED
        _delay_ms(800);
    }
    return 0;
}
