/*
 * AllocatorTask.h
 *
 *  Created on: Aug 27, 2024
 *      Author: zolot
 */

#ifndef MYINC_ALLOCATORTASK_H_
#define MYINC_ALLOCATORTASK_H_

#include <cppMain.h>

#ifdef __cplusplus

namespace Tasks {

class AllocatorTask : public Thread {

public:
	AllocatorTask();
	~AllocatorTask() = default;
	void Run();

private:

	void AllocatorTesting();
	Allocator allocator;
};

} /* namespace Tasks */

#endif /* __cplusplus */



#endif /* MYINC_ALLOCATORTASK_H_ */
