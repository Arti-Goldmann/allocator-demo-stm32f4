/*
 * cppMain.h
 *
 *  Created on: Aug 11, 2024
 *      Author: zolot
 */

#ifndef MYINC_CPPMAIN_HPP_
#define MYINC_CPPMAIN_HPP_

#ifdef __cplusplus

enum Status {
	OK = 0,
	BAD = 1,
};


#include <main.h>
#include <cstring>
#include <Thread.h>
#include <Logger.h>
#include <TaskConfig.h>
#include <MonitorTask.h>
#include <LoggerTask.h>
#include <BlinkTask.h>

extern Tasks::LoggerTask* logger_task;

void cppMain();

#endif

#endif /* MYINC_CPPMAIN_HPP_ */


