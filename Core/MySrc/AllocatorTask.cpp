/*
 * Allocator.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: zolot
 */

#include <cppMain.h>

namespace Tasks {

AllocatorTask::AllocatorTask()
						 : Thread(config::AllocatorTask::NAME,
								  config::AllocatorTask::STACK_SIZE,
								  config::AllocatorTask::PRIORITY),
						   allocator()
{
}

void AllocatorTask::Run()
{

    for(;;)
    {	//В данном случае AllocatorTask служит лишь для запуска тестирования
    	//Можно создать экземпляр класса Allocator в той задаче, где он нужен
    	AllocatorTesting();
    	vTaskDelay(pdMS_TO_TICKS(config::AllocatorTask::SLEEP_TIME_MS));
    }
}

void AllocatorTask::AllocatorTesting() {

	//Выделим максимальное кол-во блоков, а потом освободим по порядку с конца или с начала
	Test_alloc_and_free(allocator, "TEST 1", fromStart);
	Test_alloc_and_free(allocator, "TEST 2", fromEnd);
	//Выделим максимальное кол-во блоков, а потом будем освобождать через один с конца или с начала
	Test_alloc_and_free_through_one(allocator, "TEST 3", fromStart);
	Test_alloc_and_free_through_one(allocator, "TEST 4", fromEnd);
	//Выделим максимальное кол-во блоков, освободим блоки через один, потом опять выделим все
	Test_alloc_and_free_through_one_v2(allocator, "Test 5", fromStart);
	Test_alloc_and_free_through_one_v2(allocator, "Test 6", fromEnd);
}

} /* namespace Tasks */


