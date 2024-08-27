/*
 * AllocatorTest.h
 *
 *  Created on: Aug 27, 2024
 *      Author: zolot
 */

#ifndef MYINC_ALLOCATORTEST_H_
#define MYINC_ALLOCATORTEST_H_

#include <cppMain.h>

#ifdef __cplusplus

enum IndexDir {
	fromStart,
	fromEnd
};


void Test_max_alloc(class Allocator& allocator, size_t& alloc_chunks_counter, char** allocated);
void Test_alloc_and_free(class Allocator& allocator, const char* test_name, IndexDir start_index);
void Test_alloc_and_free_through_one(class Allocator& allocator, const char* test_name, IndexDir start_index);
void Test_alloc_and_free_through_one_v2(class Allocator& allocator, const char* test_name, IndexDir start_index);

#endif /* __cplusplus */

#endif /* MYINC_ALLOCATORTEST_H_ */
