

#include "FreeRTOS.h"
#include "task.h"

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

static void communication_task()
{
	while (1) {
		printf("Sending data...\n");
		fflush(stdout);
		vTaskDelay(100);
		printf("Data sent!\n");
		fflush(stdout);
		vTaskDelay(100);
	}
}

static void prioritysettask()
{
	while(1){

		portDOUBLE comm_milisec_duration = 1000.0 * ( (portDOUBLE) comm_ticks_per_iter)/( (portDOUBLE) configTICK_RATE_HZ);
		portDOUBLE mat_sec_duration =  ((portDOUBLE) mat_ticks_per_iter)/( (portDOUBLE) configTICK_RATE_HZ);

		if(comm_milisec_duration > 1000.0){
			vTaskPrioritySet(communication_handle,4);
		}
		else if(comm_milisec_duration <=200.0){
			vTaskPrioritySet(communication_handle,2);
		}
		printf("period of 'matrixtask' is %f seconds\n",mat_sec_duration);
		vTaskDelay(2000);
		//taskYIELD();
	}
}

int main ( void ) {

	comm_delay = 0;
	comm_ticks_per_iter = 0;
	comm_ticks = 0;

	/*priority 3*/
	xTaskCreate((pdTASK_CODE)matrix_task, MAT_NAME, 1000, NULL, 3, &matrix_handle);

	/*priority 1*/
	xTaskCreate((pdTASK_CODE)communication_task, COMM_NAME, configMINIMAL_STACK_SIZE, NULL, 1, &communication_handle);

	xTaskCreate((pdTASK_CODE)prioritysettask, PRIO_NAME, configMINIMAL_STACK_SIZE, NULL, 0, NULL);

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
