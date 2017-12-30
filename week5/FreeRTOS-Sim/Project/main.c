#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

TaskHandle_t matrix_handle = NULL;
QueueHandle_t queue;
UBaseType_t uxQueueLength;

/*
 * Prototypes for the standard FreeRTOS callback/hook functions implemented
 * within this file.
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationTickHook( void );

/* The variable into which error messages are latched. */
//static char *pcStatusMessage = "OK";

/*-----------------------------------------------------------*/


struct AMessage
{
    long ucMessageID;
    double** c;
};

#define SIZE 10
#define ROW SIZE
#define COL SIZE
static void matrix_task()
{
	int i;
	double **a = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) a[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **b = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) b[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **c = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) c[i] = (double *)pvPortMalloc(COL * sizeof(double));

	double sum = 0.0;
	int j, k, l;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			a[i][j] = 1.5;
			b[i][j] = 2.6;
		}
	}

	long counter = 0;
	while (1) {
		/*
		* In an embedded systems, matrix multiplication would block the CPU for a long time
		* but since this is a PC simulator we must add one additional dummy delay.
		*/
		volatile long simulationdelay;
		for (simulationdelay = 0; simulationdelay<1000000000; simulationdelay++)
			;
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				c[i][j] = 0.0;
			}
		}

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				sum = 0.0;
				for (k = 0; k < SIZE; k++) {
					for (l = 0; l<10; l++) {
						sum = sum + a[i][k] * b[k][j];
					}
				}
				c[i][j] = sum;
			}
		}
		struct AMessage msg;
		msg.ucMessageID = counter++;
		msg.c = c;

		//the queue get the item size when it is created so it knows how much to copy (it uses memcpy)
		/*BaseType_t r =*/ xQueueSendToBack(queue, &msg, 0);
		//if(r == errQUEUE_FULL)
		//	printf("error sending to queue %d\n",msg.counter);
		vTaskDelay(100);
	}
}

static void reader_task(){

	struct AMessage msg;

	while(1){
		//portMAX_DELAY - wait forever to the queue
		BaseType_t r = xQueueReceive(queue,&msg,portMAX_DELAY);

		if(r == pdFALSE)
			printf("error sending to queue %ld\n",msg.ucMessageID);

		printf("--------- from reader_task: %ld value of c: --------\n",msg.ucMessageID);
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				printf("%f ",msg.c[i][j]);
			}
			printf("\n");
		}
		printf("---------------------------------------------------\n");
	}

}



int main ( void ) {

	/*priority 3*/
	//low priority numbers are low priority task
	//the idle task has priority 0

	uxQueueLength = 1024;

	xTaskCreate((pdTASK_CODE)matrix_task, MAT_NAME, 1000, NULL, 3, &matrix_handle);
	xTaskCreate((pdTASK_CODE)reader_task, "reader", 1000, NULL, 10, NULL);

	//the uxQueueLength is the number of items
	//
	queue = xQueueCreate( uxQueueLength, sizeof(struct AMessage) );


	/* Start the scheduler itself. */
	vTaskStartScheduler();

	/* Should never get here unless there was not enough heap space to create
	the idle and other system tasks. */
	return 0;
}

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
 	taskENTER_CRITICAL();
	{
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
	}
	taskEXIT_CRITICAL();
	exit(-1);
}
