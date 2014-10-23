default:
	avr-g++ -L/usr/local/share/arduino/lib -I./ -I/usr/local/share/arduino/include -Wall -DF_CPU=16000000UL -Os -mmcu=atmega328p -o main.elf main.cpp -larduino
	avr-objcopy -O ihex -R .eeprom main.elf out.hex

upload: 
	avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -p atmega328p -c arduino -b115200 -P /dev/ttyACM0 -U flash:w:out.hex

all: default upload

# Output from Arduino IDE
#/usr/share/arduino/hardware/tools/avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -v -v -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:/tmp/build2405892125207585831.tmp/ldr.cpp.hex:i 