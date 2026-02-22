/*
    This is just example program for using AVR GCC with different microcontrollers
    - One LED is blinking on the port pin
    - Expander PCF8574T on default I2C bus drives 7 LEDs and its MSB bit stops output changes
    - Display with HD44780 controller connected to 6 bits of port changes one character
     Pins for display driving are defined in TinyLcd.h
     
    This is version for ATmega168
    
    For change to another type don't forget to edit .h files of the libraries
*/

// Default clock source is internal 8MHz RC oscillator (defined in makefile)

#include <avr/io.h>
#include <util/delay.h>
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
int main()
{
    DDRB |= 0x2;  // LED is on PortB bit 1
    TinyI2CMaster_init();
    _delay_ms(50);
    InitDisplay();
    SetDispPos(1,0);    // Write text on upper line
    WriteText((uint8_t*)"Chars");
    while (1)
    {
        if(ReadFromPCF8574T() & 0x80) SendToPCF8574T(DisChar | 0x80);  // Change LEDS if enabled
        SetDispPos(1,1);        // Character to display
        WriteChar(DisChar++);
        if(DisChar < 0x20) DisChar = 0x20;
        PORTB ^= 0x2;        // Blink LED
        _delay_ms(800);
    }
    return 0;
}
