#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1
#define configUSE_IDLE_HOOK						0
#define configUSE_TICK_HOOK						0
#define configTICK_RATE_HZ				( ( portTickType ) 1000 )
#define configMINIMAL_STACK_SIZE		( ( unsigned portSHORT ) 64 ) /* This can be made smaller if required. */
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 64 * 1024 ) )
#define configMAX_TASK_NAME_LEN			( 16 )
#define configUSE_TRACE_FACILITY    	0
#define configUSE_16_BIT_TICKS      	0
#define configIDLE_SHOULD_YIELD			1
#define configUSE_MUTEXES				1
#define configCHECK_FOR_STACK_OVERFLOW	0 /* Do not use this option on the PC port. */
#define configUSE_RECURSIVE_MUTEXES		1
#define configQUEUE_REGISTRY_SIZE				20
#define configUSE_MALLOC_FAILED_HOOK			0
#define configUSE_APPLICATION_TASK_TAG			1
#define configUSE_COUNTING_SEMAPHORES			1
#define configUSE_ALTERNATIVE_API				0
//#define configMAX_SYSCALL_INTERRUPT_PRIORITY	1

#define configUSE_QUEUE_SETS					1
#define configUSE_TASK_NOTIFICATIONS			1

/* Software timer related configuration options. */
#define configUSE_TIMERS						1
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				20
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

#define configMAX_PRIORITIES		( 10 )

#define configGENERATE_RUN_TIME_STATS		1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function.  In most cases the linker will remove unused
functions anyway. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_uxTaskGetStackHighWaterMark 	0 /* Do not use this option on the PC port. */
#define INCLUDE_xTaskGetSchedulerState			1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1
#define INCLUDE_xTaskGetIdleTaskHandle			1
#define INCLUDE_pcTaskGetTaskName				1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xSemaphoreGetMutexHolder		1
#define INCLUDE_xTimerPendFunctionCall			1
#define INCLUDE_xTaskAbortDelay					1
#define INCLUDE_xTaskGetHandle					1

/* It is a good idea to define configASSERT() while developing.  configASSERT()
uses the same semantics as the standard C assert() macro. */
extern void vAssertCalled( unsigned long ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMM_NAME "Communication"
#define MAT_NAME "Matrix"
#define PRIO_NAME "Prio"

#if(configUSE_16_BIT_TICKS == 0)
volatile uint32_t comm_delay;
volatile uint32_t comm_ticks_per_iter;
volatile uint32_t comm_ticks;

volatile uint32_t mat_ticks_per_iter;
volatile uint32_t mat_ticks;
#else
volatile uint16_t comm_delay;
volatile uint16_t comm_ticks_per_iter;
volatile uint16_t comm_ticks;
volatile uint16_t mat_ticks_per_iter;
volatile uint16_t mat_ticks;

#endif

volatile void* aperiodic_handle;

#define traceTASK_SWITCHED_IN() aperiodic_handle = pxCurrentTCB;

#define traceTASK_DELETE(xTask)                                         \
  do{                                                                   \
    portDOUBLE time = 1000.0 * ( (portDOUBLE) xTaskGetTickCountFromISR())/( (portDOUBLE) configTICK_RATE_HZ); \
    printf("task %p deleted %f ms after vTaskStartScheduler was called\n",xTask,time); \
  }while(0);

#endif /* FREERTOS_CONFIG_H */
