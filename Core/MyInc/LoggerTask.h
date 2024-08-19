/*
 * LoggerTask.h
 *
 *  Created on: Aug 15, 2024
 *      Author: zolot
 */

#ifndef MYINC_LOGGERTASK_H_
#define MYINC_LOGGERTASK_H_

#include <cppMain.h>

#ifdef __cplusplus


class UART {

public:
	static Status tx(const uint8_t* data, UART_HandleTypeDef* huart);
	static Status rx(uint8_t* data);

	UART_HandleTypeDef* handle;
	UART(UART_HandleTypeDef* uart_handler, uint16_t msg_size, uint32_t msg_timeout);
	~UART() = default;

private:
	static void _tx_complete_callback(UART_HandleTypeDef* huart);
	uint16_t _size;
	uint32_t _timeout;
};


namespace Tasks {

class LoggerTask : public Thread {

public:

	struct UARTConfig {
		static constexpr uint16_t MSG_SIZE_BYTES = 1;
		static constexpr uint32_t MSG_TIMEOUT_MS = 1000;
	};

	LoggerTask(UART_HandleTypeDef* uart_handler);
	~LoggerTask() = default;

	void Run();

	static void end_transmitting() {_transmitting = false;}

private:
	UART _m_uart;
	static bool _transmitting;
};

} /* namespace Tasks */

#endif /* __cplusplus */

#endif /* MYINC_LOGGERTASK_H_ */
