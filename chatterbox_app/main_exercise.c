/* FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 * NOTE: Windows will not be running the FreeRTOS project threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this project application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Windows
 * port for further information:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *
 * NOTE 2:  This file only contains the source code that is specific to exercise 2
 * Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 * NOTE:  Console input and output relies on Windows system calls, which can
 * interfere with the execution of the FreeRTOS Windows port.  This demo only
 * uses Windows system call occasionally.  Heavier use of Windows system calls
 * can crash the port.
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/*Priorities at which the tasks are created.*/
#define priority_taskInstanceTHREE ( tskIDLE_PRIORITY + 1 )                //Heighest
#define priority_taskInstanceTWO   ( tskIDLE_PRIORITY + 2 )
#define priority_taskInstanceONE   ( tskIDLE_PRIORITY + 3 )                //Lowest

/* output frequencey */
# define mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS 500                       //Output Frequency set to 500ms

/*-----------------------------------------------------------*/

/* data structure */
struct ChatterbotInstanceInfo_t
{
	uint8_t occuraceFlag;                                                //Holds the Value for Occurance Flag, 0: Infinate; 1:5 Times
	char opString[10];                                                   //Holds the output string
};

/* C function (prototype) for task */
 //void chatterbotInstance1(struct ChatterbotInstanceInfo_t *data);
 //void chatterbotInstance2(struct ChatterbotInstanceInfo_t *data);
 //void chatterbotInstance3(struct ChatterbotInstanceInfo_t *data);
 void chatterbotInstance1(void *pvParameters);
 void chatterbotInstance2(void *pvParameters);
 void chatterbotInstance3(void *pvParameters);
/*-----------------------------------------------------------*/

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_exercise( void )
{
/* Initialize data structures and Function Call*/
	struct ChatterbotInstanceInfo_t data1;
	struct ChatterbotInstanceInfo_t data2;
	struct ChatterbotInstanceInfo_t data3;

	// Task Instance 1
	data1.occuraceFlag = 0U;                      //Infinate Occurances
	strcpy(data1.opString, "TASK1");              //Output String for Indicating Instance 1 is running
	//chatterbotInstance1(&data1);                  //Call

     // Task Instance 2
	data2.occuraceFlag = 0U;                      //Infinate Occurances
	strcpy(data2.opString, "TASK2");              //Output String for Indicating Instance 2 is running
	//chatterbotInstance2(&data2);                  //Call

     // Task Instance 3
	data3.occuraceFlag = 1U;                      //5 occurances
	strcpy(data3.opString, "TASK3");              //Output String for Indicating Instance 3 is running
 	//chatterbotInstance3(&data3);

	//Call
	xTaskCreate(chatterbotInstance1, "Task1", configMINIMAL_STACK_SIZE, &data1, priority_taskInstanceONE, NULL);
	xTaskCreate(chatterbotInstance2, "Task2", configMINIMAL_STACK_SIZE, &data2, priority_taskInstanceTWO, NULL);
	xTaskCreate(chatterbotInstance3, "Task3", configMINIMAL_STACK_SIZE, &data3, priority_taskInstanceTHREE, NULL);

	vTaskStartScheduler();
	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* C function for tasks */
void chatterbotInstance1 (void *pvParameters)
{
	struct ChatterbotInstanceInfo_t *data1 = (struct ChatterbotInstanceInfo_t *)pvParameters;
	if (data1->occuraceFlag == 0)
	{
		while(1)
		{
			printf("%s\n",data1->opString);
			vTaskDelay(mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);

		}
	}
	else if(data1->occuraceFlag == 1)
	{
		for (int i = 0; i<5; i++)
		{
			printf("%s\n",data1->opString);
			vTaskDelay(mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);

		}
	}
}

void chatterbotInstance2 (void *pvParameters)
{
	struct ChatterbotInstanceInfo_t *data2 = (struct ChatterbotInstanceInfo_t *)pvParameters;
		if (data2->occuraceFlag == 0)
	{
		while(1)
		{
			printf("%s\n",data2->opString);
			vTaskDelay(mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);

		}
	}
	else if(data2->occuraceFlag == 1)
	{
		for (int i = 0; i<5; i++)
		{
			printf("%s\n",data2->opString);
			vTaskDelay(mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);

		}
	}
}

void chatterbotInstance3 (void *pvParameters)
{
	struct ChatterbotInstanceInfo_t *data3 = (struct ChatterbotInstanceInfo_t *)pvParameters;
		if (data3->occuraceFlag == 0)
	{
		while(1)
		{
			printf("%s\n",data3->opString);
		}
	}
	else if(data3->occuraceFlag == 1)
	{
		for (int i = 0; i<5; i++)
		{
			printf("%s\n",data3->opString);
			vTaskDelay(mainTASK_CHATTERBOX_OUTPUT_FREQUENCY_MS);
			//Final Cycle
			if (i == 4)
			{
				printf ("%s\n", "Terminating Instance 3...");
				vTaskDelay(5);
				printf ("%s\n", "Instance 3 Deleted!");

			}
		}
		
	}
}
