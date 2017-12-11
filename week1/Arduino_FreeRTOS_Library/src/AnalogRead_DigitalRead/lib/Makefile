SC = croutine.c event_groups.c heap_3.c  list.c  port.c  queue.c  tasks.c  timers.c

OC = croutine.o event_groups.o heap_3.o  list.o  port.o  queue.o  tasks.o  timers.o

SCPP = variantHooks.cpp
OCPP = variantHooks.o

all: $(OC) $(OCPP)


$(SC:%.c=%.o):
	/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/cores/arduino/avr-libc   -o $@ -c $(@:%.o=%.c)

$(SCPP:%.cpp=%.o):
	/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/cores/arduino/avr-libc   -o $@ -c $(@:%.o=%.cpp)
