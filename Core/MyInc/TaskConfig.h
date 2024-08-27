/*
 * TaskConfig.h
 *
 *  Created on: Aug 12, 2024
 *      Author: zolot
 */

#ifndef MYINC_TASKCONFIG_H_
#define MYINC_TASKCONFIG_H_

#include <cppMain.h>

#ifdef __cplusplus

namespace Tasks {

namespace config {

	static constexpr uint32_t MIN_TASK_STACK_SIZE 	= configMINIMAL_STACK_SIZE;
	static constexpr uint32_t MIN_TASK_PRIORITY   	= 1;
	static constexpr uint32_t MAX_TASK_PRIORITY   	= configMAX_PRIORITIES;

	struct MonitorTask {
		static constexpr uint32_t STACK_SIZE 		= MIN_TASK_STACK_SIZE * 5;
		static constexpr const char NAME[]   		= "Monitor Task";
		static constexpr uint32_t PRIORITY   		= MIN_TASK_PRIORITY;
		static constexpr uint32_t SLEEP_TIME_MS 	= 100;
		static constexpr uint32_t MAX_TASKS_MONITOR = 10;
	};

	struct BlinkTask {
		static constexpr uint32_t STACK_SIZE 		= MIN_TASK_STACK_SIZE * 5;
		static constexpr const char NAME[]   		= "Blink Task";
		static constexpr uint32_t PRIORITY   		= MIN_TASK_PRIORITY;
		static constexpr uint32_t SLEEP_TIME_MS 	= 500;
	};

	struct LoggerTask {
		static constexpr uint32_t STACK_SIZE 		= MIN_TASK_STACK_SIZE * 5;
		static constexpr const char NAME[]   		= "Logger Task";
		static constexpr uint32_t PRIORITY   		= MIN_TASK_PRIORITY;
		static constexpr uint32_t SLEEP_TIME_MS 	= 0;
	};

	struct AllocatorTask {
		static constexpr uint32_t STACK_SIZE 		= MIN_TASK_STACK_SIZE * 5;
		static constexpr const char NAME[]   		= "Allocator Task";
		static constexpr uint32_t PRIORITY   		= MIN_TASK_PRIORITY;
		static constexpr uint32_t SLEEP_TIME_MS 	= 500;
	};

}	/* namespace config */

}	/* namespace Tasks */


#endif

#endif /* MYINC_TASKCONFIG_H_ */
