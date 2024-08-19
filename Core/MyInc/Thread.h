/*
 * Task.h
 *
 *  Created on: Aug 12, 2024
 *      Author: zolot
 */

#ifndef MYINC_THREAD_H_
#define MYINC_THREAD_H_

#include <cppMain.h>

#ifdef __cplusplus

class Thread {

protected:

	const char * const Name;
    const configSTACK_DEPTH_TYPE StackDepth;
    UBaseType_t Priority;
    static void TaskFunctionAdapter(void *pvParameters);

public:

    TaskHandle_t Handle {NULL};

    Thread( const char * const pcName,
    	    const configSTACK_DEPTH_TYPE usStackDepth,
    	    UBaseType_t uxPriority);

	virtual ~Thread();

	virtual void Run ();

};

#endif

#endif /* MYINC_THREAD_H_ */
