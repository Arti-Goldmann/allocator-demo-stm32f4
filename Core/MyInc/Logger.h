/*
 * Logger.h
 *
 *  Created on: Aug 15, 2024
 *      Author: zolot
 */

#ifndef MYINC_LOGGER_H_
#define MYINC_LOGGER_H_

#include <cppMain.h>

#ifdef __cplusplus

class Logger {

public:

	struct loggerConfig {
		static constexpr uint32_t QUEUE_ITEM_SIZE_BYTES     = 1;
		static constexpr uint32_t QUEUE_LENGTH_BYTES        = 5420;
		static constexpr uint32_t LOGGER_HEADER_LENGTH      = 16;
		static constexpr uint32_t LOGGER_MESSAGE_LENGTH     = 255;
		static constexpr uint32_t MAX_STRING_LENGHT         = LOGGER_HEADER_LENGTH + LOGGER_MESSAGE_LENGTH;
	};

	static uint32_t          msgQueueErr;
	static QueueHandle_t     msgQueue;
	static SemaphoreHandle_t msgSemaphore;

	Logger(const char* class_name);
	~Logger() = default;

	void clear_terminal();
	void return_cursor();
	void add_str(const char *format, ...);
	void add_buf(const char *buff, uint16_t len);
	void get_queue_item();
	bool first_log = {true};

private:

	static uint32_t _num_of_strings;
	static bool _init;

	char _buffer_to_send[loggerConfig::MAX_STRING_LENGHT];
	void _to_queue(const char *buff);
};


#endif /* __cplusplus */

#endif /* MYINC_LOGGER_H_ */
