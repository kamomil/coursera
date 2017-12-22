

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
TaskHandle_t matrix_handle = NULL;
TaskHandle_t communication_handle = NULL;


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

void vTimerCallback(TimerHandle_t pxTimer);

typedef struct {
	char symbol;
	unsigned long delay;
} TaskParams;

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

	while (1) {
		/*
		* In an embedded systems, matrix multiplication would block the CPU for a long time
		* but since this is a PC simulator we must add one additional dummy delay.
		*/
		long simulationdelay;
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
		vTaskDelay(100);
	}
}

static TaskHandle_t aperiodic_handle;

static void aperiodic_task()
{
	printf("Aperiodic task started!\n");
	fflush(stdout);
	volatile long i;
	for (i = 0; i<1000000000; i++); //Dummy workload
	printf("Aperiodic task done!\n");
	fflush(stdout);
	vTaskDelete(aperiodic_handle);
}

/* A variable to hold a count of the number of times the timer expires. */
long lExpireCounters = 0;
void vTimerCallback(TimerHandle_t pxTimer)
{
	printf("Timer callback!\n");
	xTaskCreate((pdTASK_CODE)aperiodic_task, (char *)"Aperiodic", configMINIMAL_STACK_SIZE, NULL, 2, &aperiodic_handle);
	long lArrayIndex;
	const long xMaxExpiryCountBeforeStopping = 10;
	/* Optionally do something if the pxTimer parameter is NULL. */
	configASSERT(pxTimer);
	/* Increment the number of times that pxTimer has expired. */
	lExpireCounters += 1;
	/* If the timer has expired 10 times then stop it from running. */
	if (lExpireCounters == xMaxExpiryCountBeforeStopping) {
		/* Do not use a block time if calling a timer API function from a
		   timer callback function, as doing so could cause a deadlock! */
		xTimerStop(pxTimer, 0);
	}
}

int main ( void ) {

	comm_delay = 0;
	comm_ticks_per_iter = 0;
	comm_ticks = 0;

	/*priority 3*/
	//low priority numbers are low priority task
	//the idle task has priority 0
	xTaskCreate((pdTASK_CODE)matrix_task, MAT_NAME, 1000, NULL, 3, &matrix_handle);

	TimerHandle_t timer  = xTimerCreate("aperiodicTaskTimer",pdMS_TO_TICKS(5000) ,pdTRUE /*auto reload*/, ( void * ) 0,vTimerCallback);

	if(timer == NULL){
		printf("could not create timer");
		exit(1);
	}

	if( xTimerStart( timer, 0 ) != pdPASS ){
		printf("could not start timer");
		exit(1);
	}
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
