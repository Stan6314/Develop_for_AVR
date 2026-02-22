/* TinyI2C v2.0.1

   David Johnson-Davies - www.technoblogy.com - 5th June 2022
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/
*/
// Library downloaded from github/technoblogy/tiny-i2c
// This version is only transformed from C++ to plain C and get rid of Arduino instructions by Stan6314

#ifndef TinyI2CMaster_h
#define TinyI2CMaster_h

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// Define for microcontrollers with USI
// Example tested for ATtiny2313
#define PORT_USI PORTB   // PORT of SDA bit
#define DDR_USI DDRB   // DDR of SDA bit
#define PORT_USI_CL PORTB   // PORT of SCL bit
#define DDR_USI_CL DDRB   // DDR of SCL bit
#define PIN_USI_SDA 5  // Bit SDA on port
#define PIN_USI_SCL 7   // Bit SCL on port
#define PIN_USI_CL PINB   // Register for SCL reading

// Define for microcontrollers with TWI for most of the original ATmega processors
// Example tested for ATmega168
#define SET_PIN_TWI_SCL PORTC |= 1<<7   // Set Bit SCL on port
#define SET_PIN_TWI_SDA PORTC |= 1<<6   // Set Bit SCL on port

// Define for microcontrollers with TWI for - the new 0-series and 1-series ATtiny and ATmega microcontrollers
// Example tested for ATtiny414
#define SET_INPUT_PULLUP_TWI_SCL PORTB.DIRCLR = 0x01; PORTB.PIN0CTRL = PORT_PULLUPEN_bm  // SCL input with pullup
#define SET_INPUT_PULLUP_TWI_SDA PORTB.DIRCLR = 0x02; PORTB.PIN1CTRL = PORT_PULLUPEN_bm  // SDA input with pullup

// Example tested for AVR128DB28
#define DXCORE


#define TWI_NACK_BIT 0 // Bit position for (N)ACK bit.

void TinyI2CMaster_init(void);
uint8_t TinyI2CMaster_read(void);
uint8_t TinyI2CMaster_readLast(void);
bool TinyI2CMaster_write(uint8_t data);
bool TinyI2CMaster_start(uint8_t address, int32_t readcount);
bool TinyI2CMaster_restart(uint8_t address, int32_t readcount);
void TinyI2CMaster_stop(void);

#endif

