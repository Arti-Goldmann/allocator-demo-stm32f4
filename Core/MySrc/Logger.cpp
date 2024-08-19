/*
 * Logger.cpp
 *
 *  Created on: Aug 15, 2024
 *      Author: zolot
 */


#include <cppMain.h>

bool Logger::_init = false;
uint32_t Logger::msgQueueErr = 0;
uint32_t Logger::_num_of_strings = 0;
QueueHandle_t Logger::msgQueue = nullptr;
SemaphoreHandle_t Logger::msgSemaphore= nullptr;

Logger::Logger(const char* class_name){

	if(!_init){
		msgQueue = xQueueCreate(loggerConfig::QUEUE_LENGTH_BYTES, loggerConfig::QUEUE_ITEM_SIZE_BYTES);
		msgSemaphore = xSemaphoreCreateBinary();
		_init = true;
	}

	snprintf(_buffer_to_send, loggerConfig::LOGGER_HEADER_LENGTH, "\r\n%s:", class_name);
	uint32_t header_len = strlen(_buffer_to_send);

	for (uint32_t i = header_len; i < loggerConfig::LOGGER_HEADER_LENGTH; i++)
		_buffer_to_send[i] = ' ';

}

void Logger::add_str(const char *format, ...){

	_num_of_strings++;
	va_list arglist;
	va_start(arglist, format);

    char buffer[loggerConfig::LOGGER_MESSAGE_LENGTH];
    for(uint32_t i = 0; i < loggerConfig::LOGGER_MESSAGE_LENGTH; i++){
    	buffer[i] = ' ';
    }

    vsnprintf(buffer, loggerConfig::LOGGER_MESSAGE_LENGTH, format, arglist);
    uint32_t len = strlen(buffer);
    add_buf(buffer, len);

	va_end(arglist);

}

void Logger::add_buf(const char *buff, uint16_t len){

	if(!len)
		return;

	while (len != 0)
	{
		if (len < loggerConfig::LOGGER_MESSAGE_LENGTH)
		{
			snprintf(&_buffer_to_send[loggerConfig::LOGGER_HEADER_LENGTH], len + 1, buff);
			len -= len;
			_to_queue(_buffer_to_send);
		}

		else
		{
			snprintf(&_buffer_to_send[loggerConfig::LOGGER_HEADER_LENGTH], loggerConfig::LOGGER_MESSAGE_LENGTH, buff);
			len  -= (loggerConfig::LOGGER_MESSAGE_LENGTH - 1);
			buff += (loggerConfig::LOGGER_MESSAGE_LENGTH - 1);
			_to_queue(_buffer_to_send);
		}
	}
}

void Logger::clear_terminal(){

	if(first_log) {
		char clear_terminal[] = "\033c\r";
		_to_queue(clear_terminal);
		first_log = false;
	}
	_num_of_strings = 0;
}

void Logger::return_cursor(){

	char clear_rows[] = "\033[A\r";
	for(uint32_t index = 0; index <= _num_of_strings; index++){
		_to_queue(clear_rows);
	}
	_num_of_strings = 0;
}


void Logger::_to_queue(const char *buff)
{
	char end_of_string = '\0';
	for (uint32_t i = 0; i < strlen(buff); i++) {
		if(xQueueSendToBack(msgQueue, &buff[i], 0) != pdPASS) msgQueueErr++;
	}
	if(xQueueSendToBack(msgQueue, &end_of_string, 0) != pdPASS) msgQueueErr++;

}



