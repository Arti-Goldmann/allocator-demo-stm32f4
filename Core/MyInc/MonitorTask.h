/*
 * Monitor.h
 *
 *  Created on: Aug 12, 2024
 *      Author: zolot
 */

#ifndef MYINC_MONITORTASK_H_
#define MYINC_MONITORTASK_H_

#include <cppMain.h>
#include <Allocator.h>

#ifdef __cplusplus

namespace Tasks {

class MonitorTask : public Thread {

public:
	MonitorTask(TIM_HandleTypeDef* timer_handler);
	~MonitorTask() = default;
	void Run();

	static uint32_t get_counter_value();
	static void config_timer();

private:
	static TaskStatus_t _tasks_status_array[config::MonitorTask::MAX_TASKS_MONITOR];
	static TIM_HandleTypeDef* _timer;

	char _task_state_to_char(eTaskState state);
	void _sort_tasks_by_number(TaskStatus_t *status, UBaseType_t count);
	Logger _logger;
};

} /* namespace Tasks */

#endif /* __cplusplus */

#endif /* MYINC_MONITORTASK_H_ */


