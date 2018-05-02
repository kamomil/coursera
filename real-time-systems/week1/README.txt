solution for week1 is for arduino uno plus (arduino compatible)

Didn’t want to use the stupid ide, so I installled:

sudo apt install arduino-core

Adn a tool called ino:

pip install ino

Now, since the pip was without uno, 

Cased my code on:

https://github.com/feilipu/Arduino_FreeRTOS_Library

ino expect a src and a lib dirs when runninf “ino build”

First I run “ino build” this creates the initial mafefiles and stuff in .build/uno
But it does not find the headers in lib

So I put the freerots h and c files in the lib dir , but ino didn’t find them,
Eventually I wrote the following Makefile myself:


SC = croutine.c event_groups.c heap_3.c  list.c  port.c  queue.c  tasks.c  timers.c

OC = croutine.o event_groups.o heap_3.o  list.o  port.o  queue.o  tasks.o  timers.o

SCPP = variantHooks.cpp
OCPP = variantHooks.o

all: $(OC) $(OCPP)


$(SC:%.c=%.o):
	/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/cores/arduino/avr-libc   -o $@ -c $(@:%.o=%.c)

$(SCPP:%.cpp=%.o):
	/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/cores/arduino/avr-libc   -o $@ -c $(@:%.o=%.cpp)

In the directory 
/home/dafna/arduino/Arduino_FreeRTOS_Library/src/AnalogRead_DigitalRead/lib

Where the freertos c and cpp and h files are,~
So I cd to /home/dafna/arduino/Arduino_FreeRTOS_Library/src/AnalogRead_DigitalRead/lib
Run make and then copied all the created .o file to the parent: 
/home/dafna/arduino/Arduino_FreeRTOS_Library/src/AnalogRead_DigitalRead/

Then I run 


/home/dafna/.local/bin/ino preproc -o .build/uno/src/AnalogRead_DigitalRead.cpp src/AnalogRead_DigitalRead.ino

This creates the cpp file from the ino file
Also I changed the ~/arduino/Arduino_FreeRTOS_Library/src/AnalogRead_DigitalRead/.build/uno/Makefile to have:


OC = croutine.o event_groups.o heap_3.o  list.o  port.o  queue.o  tasks.o  timers.o variantHooks.o



.build/uno/firmware.elf : .build/uno/src/AnalogRead_DigitalRead.o .build/uno/arduino/libarduino.a $(OC)
        @echo ESC[92mLinking firmware.elfESC[0m
        @/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm



Then run:

dafna@guri:~/arduino/Arduino_FreeRTOS_Library/src/AnalogRead_DigitalRead$ make -f .build/uno/Makefile all

This creates the firmware.hex then, when minicom is not connected
Ino upload 

Then the problem I had is that I had to add vTaskStartScheduler();  at the end of setup() and also at beggining I set the stack size of one of the tasks to 1000, this is probably too big, the whole SRAM is only 2K so I set both stack to 100, and it wroks.

The code is:

#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
//#include <EEPROM.h>

void Task1( void *pvParameters );
void Task2( void *pvParameters );

int addr = 0;

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  Serial.println("bla");

  xTaskCreate(
    Task1
    ,  (const portCHAR *) "Task1"
    ,  100  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL );

  xTaskCreate(Task2,  (const portCHAR *) "Task2",100,NULL,1,NULL);

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
  vTaskStartScheduler();
}

void loop()
{
  // Empty. Things are done in Tasks.
}

void Task1( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  for (;;){
    Serial.println("This is task 1");
    Serial.flush();
    //EEPROM.write(addr,(int)'T');//his is task 1");
    addr++;
    vTaskDelay(100);
  }
}

void Task2( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  for (;;){
    Serial.println("This is task 2");
    Serial.flush();
    //EEPROM.write(addr,(int)'R');//his is task 1");
    addr++;
    vTaskDelay(500);
  }
}

