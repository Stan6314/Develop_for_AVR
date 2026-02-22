REM For lfuse, hfuse and efuse parameters use AVR Fuse Bit Calculator on the web
avrdude -c stk500v2 -p atmega168 -P COM4 -B 25kHz -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xF9:m