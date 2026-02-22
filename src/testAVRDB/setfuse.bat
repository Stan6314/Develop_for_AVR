REM For lfuse, hfuse and efuse parameters use AVR Fuse Bit Calculator on the web
avrdude -c serialupdi -p attiny414 -P COM3 -U afuse:w:0x00:m -U bfuse:w:0x01:m -U sfuse:w:0x00:m  -U tfuse:w:0x00:m