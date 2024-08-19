/*
 * Task.cpp
 *
 *  Created on: Aug 12, 2024
 *      Author: zolot
 */

#include <cppMain.h>

Thread::Thread( const char * const pcName,
	            const configSTACK_DEPTH_TYPE usStackDepth,
	            UBaseType_t uxPriority) :
				Name(pcName), StackDepth(usStackDepth), Priority(uxPriority)
{
	xTaskCreate(TaskFunctionAdapter, Name, StackDepth, this, Priority, &Handle);
}

Thread::~Thread() {

}

void Thread::Run() {

}


void Thread::TaskFunctionAdapter(void *pvParameters)
{
    Thread *thread = static_cast<Thread *>(pvParameters);

    thread->Run();

    vTaskDelete(thread->Handle);
}

