/*
 * Monitor.cpp
 *
 *  Created on: Aug 12, 2024
 *      Author: zolot
 */

#include <cppMain.h>

namespace Tasks {

TaskStatus_t MonitorTask::_tasks_status_array[config::MonitorTask::MAX_TASKS_MONITOR];
TIM_HandleTypeDef* MonitorTask::_timer = NULL;

MonitorTask::MonitorTask(TIM_HandleTypeDef* timer_handler)
						 : Thread(config::MonitorTask::NAME,
								  config::MonitorTask::STACK_SIZE,
								  config::MonitorTask::PRIORITY),
						   _logger("MONITOR")

{
	_timer = timer_handler;
}

void MonitorTask::Run()
{

    for(;;)
    {
    	if(_logger.first_log) _logger.clear_terminal();
    	else
    	{
        	UBaseType_t task_count = uxTaskGetNumberOfTasks();
        	if (task_count <= config::MonitorTask::MAX_TASKS_MONITOR)
        	{
    			unsigned long _total_runtime;

    			TaskStatus_t _buffer[config::MonitorTask::MAX_TASKS_MONITOR];
    			task_count = uxTaskGetSystemState(_buffer, task_count, &_total_runtime);
    			_sort_tasks_by_number(_buffer, task_count);

    			for (UBaseType_t task = 0; task < task_count; task++)
    			{
    			  _logger.add_str( "[DEBG] %20s: %c, %u, %6u, %u",
    							   _tasks_status_array[task].pcTaskName,
    							   _task_state_to_char(_tasks_status_array[task].eCurrentState),
    							   (unsigned long)_tasks_status_array[task].uxCurrentPriority,
    							   (unsigned long)_tasks_status_array[task].usStackHighWaterMark,
    							   (unsigned long)(_tasks_status_array[task].ulRunTimeCounter / 1000));
    			}

    			_logger.add_str( " ");

    			_logger.add_str( "[DEBG] Current Heap Free Size: %u",
    							  (unsigned long)xPortGetFreeHeapSize());

    			_logger.add_str( "[DEBG] Minimal Heap Free Size: %u",
    							  (unsigned long)xPortGetMinimumEverFreeHeapSize());

    			_logger.add_str( "[DEBG] Total RunTime:  %u ms", _total_runtime / 1000);

    			_logger.add_str( "[DEBG] System Uptime:  %u ms\r\n",
        	 					  (unsigned long)xTaskGetTickCount() * portTICK_PERIOD_MS);
        	}
        	_logger.return_cursor();
    	}

		xSemaphoreGive(Logger::msgSemaphore);
    	vTaskDelay(pdMS_TO_TICKS(config::MonitorTask::SLEEP_TIME_MS));

    }
}

char MonitorTask::_task_state_to_char(eTaskState state)
{
	switch (state)
	{
		case eReady:		return 'R';
		case eBlocked:		return 'B';
		case eSuspended:	return 'S';
		case eDeleted:		return 'D';
		default:			return 'G';
	}
}

void MonitorTask::_sort_tasks_by_number(TaskStatus_t *status, UBaseType_t count)
{
	for (UBaseType_t task = 0; task < count; task++) {
		_tasks_status_array[status[task].xTaskNumber - 1] = status[task];
  	}
}

uint32_t MonitorTask::get_counter_value(){

	 static uint32_t _counter = 0;
	 if(_timer == NULL) return 0;

	 _counter += __HAL_TIM_GET_COUNTER(_timer);
	 __HAL_TIM_SET_COUNTER(_timer, 0);
	 return _counter;
}

void MonitorTask::config_timer(){

	if(_timer == NULL) return;
	HAL_TIM_Base_Start(_timer);
}

} /* namespace Tasks */
