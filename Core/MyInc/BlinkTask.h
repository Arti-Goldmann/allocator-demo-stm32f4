/*
 * BlinkTask.h
 *
 *  Created on: Aug 13, 2024
 *      Author: zolot
 */

#ifndef MYINC_BLINKTASK_H_
#define MYINC_BLINKTASK_H_

#include <cppMain.h>

#ifdef __cplusplus

namespace Tasks {

class BlinkTask : public Thread {

private:


public:
	BlinkTask();
	~BlinkTask() = default;

	void Run();

};

} /* namespace Tasks */

#endif /* __cplusplus */

#endif /* MYINC_BLINKTASK_H_ */
