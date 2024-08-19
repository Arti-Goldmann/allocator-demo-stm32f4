#include "main.h"


void* malloc(size_t size)
{
    return pvPortMalloc(size);
}

void* calloc(size_t num, size_t size)
{
    return pvPortMalloc(num * size);
}

void free(void* ptr)
{
    return vPortFree(ptr);
}

void* operator new(size_t sz)
{
    return pvPortMalloc(sz);
}

void* operator new[](size_t sz)
{
    return pvPortMalloc(sz);
}

void operator delete(void* p)
{
    vPortFree(p);
}

void operator delete[](void* p)
{
    vPortFree(p);
}



void cppMain(){

	auto monitor_task = new Tasks::MonitorTask(&htim2);
	auto blink_task = new Tasks::BlinkTask();
	auto logger_task = new Tasks::LoggerTask(&huart2);

    vTaskStartScheduler();

    delete monitor_task;
    delete blink_task;
    delete logger_task;

    while(1){

    }

}

#if configGENERATE_RUN_TIME_STATS == 1

void vConfigureTimerForRunTimeStats(void)
{
	Tasks::MonitorTask::config_timer();
}

unsigned long vGetTimerForRunTimeStats(void)
{
	return Tasks::MonitorTask::get_counter_value();
}

#endif

