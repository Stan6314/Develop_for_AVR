REM For lfuse, hfuse and efuse parameters use AVR Fuse Bit Calculator on the web
avrdude -c stk500v2 -p attiny2313 -P COM4 -B 25kHz -U lfuse:w:0x64:m -U hfuse:w:0x9F:m -U efuse:w:0xFF:m