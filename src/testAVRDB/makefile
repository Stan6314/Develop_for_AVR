# The MCU model
MCU=avr128db28
# Name of main PROJ.c file and name for temporary output files
PROJ=testAVRDB
# CPU clock frequency
CLOCK=24000000UL
# Type of programmer
PROGRAMMER=serialupdi
# COM port for programmer
PORT=COM3

default:
# Compile C source and library files - every *.c to *.o
	avr-gcc -mmcu=$(MCU)  -DF_CPU=$(CLOCK) -Wall -Os -c *.c
# Link compiled files to -elf
	avr-gcc -mmcu=$(MCU) -o $(PROJ).elf *.o

# Create HEX file
	avr-objcopy -j .text -j .data -O ihex $(PROJ).elf $(PROJ).hex
# Show memory usage
	avr-size -G $(PROJ).elf
# Upload file to microcontroller
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$(PROJ).hex
# Here you can clean up temporary files (if you prefer)
#	del /f *.hex *.elf *.o
