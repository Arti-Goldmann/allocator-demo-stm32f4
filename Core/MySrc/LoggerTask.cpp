/*
 * LoggerTask.cpp
 *
 *  Created on: Aug 15, 2024
 *      Author: zolot
 */


#include <cppMain.h>

namespace Tasks {

bool LoggerTask::_transmitting = false;

LoggerTask::LoggerTask(UART_HandleTypeDef* uart_handler)
		: Thread(config::LoggerTask::NAME,
			     config::LoggerTask::STACK_SIZE,
			     config::LoggerTask::PRIORITY),

	     _m_uart(uart_handler,
				 UARTConfig::MSG_SIZE_BYTES,
				 UARTConfig::MSG_TIMEOUT_MS)
{

}

void LoggerTask::Run()
{

    for(;;)
    {
       xSemaphoreTake(Logger::msgSemaphore, portMAX_DELAY);
       if(_transmitting == false) {
		   _transmitting = true;
		   uint8_t tx_data = '\0';
		   Status uartTxStatus = UART::tx(&tx_data, _m_uart.handle);
		   if(uartTxStatus == BAD) Error_Handler();
       }
    }
}


}/* namespace Tasks */


UART::UART(UART_HandleTypeDef* uart_handler, uint16_t msg_size, uint32_t msg_timeout) :
		                handle(uart_handler), _size(msg_size), _timeout(msg_timeout)
{
	HAL_UART_RegisterCallback(handle, HAL_UART_TX_COMPLETE_CB_ID, _tx_complete_callback);
}

void UART::_tx_complete_callback(UART_HandleTypeDef* huart){

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t tx_data = 0;

	if (xQueueReceiveFromISR(Logger::msgQueue, &tx_data, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY)
	{
		 Status uartTxStatus = UART::tx(&tx_data, huart);
		 if(uartTxStatus == BAD) Error_Handler();

	} else
		Tasks::LoggerTask::end_transmitting();

}

Status UART::tx(const uint8_t* data, UART_HandleTypeDef* huart)
{
	HAL_StatusTypeDef txCodeErr;
	txCodeErr = HAL_UART_Transmit_IT(huart, data, Tasks::LoggerTask::UARTConfig::MSG_SIZE_BYTES);
	if(txCodeErr != HAL_OK) return BAD;
	else return OK;
}

Status UART::rx(uint8_t* data)
{

	return BAD;
}


