/*
    This is just example program for using AVR GCC with different microcontrollers
    - One LED is blinking on the port pin
    - Expander PCF8574T on default I2C bus drives 7 LEDs and its MSB bit stops output changes
    - Display with HD44780 controller connected to 6 bits of port changes one character
     Pins for display driving are defined in TinyLcd.h
     
    This is version for AVR128DB28 with 32kHz crystal (for auto-tune)
    
    For change to another type don't forget to edit .h files of the libraries
*/

// Default clock source is internal 24MHz RC oscillator (defined in makefile)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
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
    // Set oscillator 24 MHz
    _delay_ms(10);
    // Autocorrection of internal HF oscillator with 32KHz crystal
    // Set OSCHF clock to 24 MHz
    _PROTECTED_WRITE (CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
    // Enable external crystal oscillator
    _PROTECTED_WRITE (CLKCTRL.XOSC32KCTRLA, CLKCTRL_ENABLE_bm);
    // Set OSCHF as main clock
    _PROTECTED_WRITE (CLKCTRL.MCLKCTRLA, (CLKCTRL_CLKSEL_OSCHF_gc)); 
    cli();
    // Set OSCHF clock to 24 MHz and enable auto-tune
    _PROTECTED_WRITE (CLKCTRL.OSCHFCTRLA, (CLKCTRL_FRQSEL_24M_gc | CLKCTRL_AUTOTUNE_bm));
    _delay_ms(200);
    // Disable auto-tune and keep the 24 MHz clock
    _PROTECTED_WRITE (CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
    
    PORTD.DIR |= 0x80;  // LED is on PortD bit 7
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
        PORTD.OUTTGL = 0x80;        // Blink LED
        _delay_ms(800);
    }
    return 0;
}
