# The MCU model
MCU=atmega168
# Name of main PROJ.c file and name for temporary output files
PROJ=test168
# CPU clock frequency
CLOCK=8000000UL
# Type of programmer
PROGRAMMER=stk500v2
# COM port for programmer
PORT=COM4

default:
# Compile C source and library files - every *.c to *.o
	avr-gcc -mmcu=$(MCU)  -DF_CPU=$(CLOCK) -Wall -Os -c *.c
# Link compiled files to -elf
	avr-gcc -mmcu=$(MCU) -o $(PROJ).elf *.o

# Create HEX file
	avr-objcopy -j .text -j .data -O ihex $(PROJ).elf $(PROJ).hex
# Show memory usage
	avr-size -G $(PROJ).elf
# Upload file to microcontroller (parameter -B 125kHz is suitable for longer cable)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -B 125kHz -U flash:w:$(PROJ).hex
# Here you can clean up temporary files (if you prefer)
#	del /f *.hex *.elf *.o
