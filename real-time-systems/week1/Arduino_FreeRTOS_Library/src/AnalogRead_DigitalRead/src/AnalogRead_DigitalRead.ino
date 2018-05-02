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
