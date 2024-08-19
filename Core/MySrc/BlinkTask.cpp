/*
 * BlinkTask.cpp
 *
 *  Created on: Aug 13, 2024
 *      Author: zolot
 */

#include <cppMain.h>

namespace Tasks {


BlinkTask::BlinkTask() : Thread(config::BlinkTask::NAME,
								config::BlinkTask::STACK_SIZE,
								config::BlinkTask::PRIORITY)
{

}

void BlinkTask::Run()
{

    for(;;)
    {

        vTaskDelay(pdMS_TO_TICKS(config::BlinkTask::SLEEP_TIME_MS));
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

    }
}

} /* namespace Tasks */

