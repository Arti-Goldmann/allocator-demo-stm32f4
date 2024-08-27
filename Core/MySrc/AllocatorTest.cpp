#include <cppMain.h>


void Test_max_alloc(Allocator& allocator, size_t& alloc_chunks_counter, char** allocated){
	
    while(allocator.get_free_chunks_num() != 0) {
		char* tmp = (char*)allocator.m_alloc_chunk();

		//Проверим выделенный адрес
		size_t start_adress = allocator.get_heap_start_adress();
		size_t expected_adress = start_adress + Allocator::CHUNK_INFO_BYTES + alloc_chunks_counter * Allocator::TOTAL_CHUNK_BYTES;
		assert_param(expected_adress == (size_t)tmp);

		allocated[alloc_chunks_counter] = tmp;
		alloc_chunks_counter++;

		//Проверим, что кол-во свободных и выделенных блоков сходится
		assert_param(alloc_chunks_counter == allocator.get_chunks_num_in_use());
		assert_param((allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES - alloc_chunks_counter) == allocator.get_free_chunks_num());
	}

	//Проверим, что если попытаемся выделить еще блок, то получим NULL
	assert_param((char*)allocator.m_alloc_chunk() == NULL);
	//Проверим, что в списке свободных блоков нет
	assert_param(allocator.get_size_of_free_list() == 0);
}

void Test_alloc_and_free(Allocator& allocator, const char* test_name, IndexDir start_index){

	//std::cout << test_name << " start" << std::endl;
	//Allocator allocator = Allocator();
	char* allocated[Allocator::config::NUM_OF_CHUNKS_IN_HEAP] = {};

	size_t alloc_chunks_counter = 0;
	//Выделим столько блоков, сколько сможем и проверим
	Test_max_alloc(allocator, alloc_chunks_counter, allocated);

	//Будем освобождать с начала или с конца
	size_t index = 0;
	if(start_index == fromStart)    index = 0;
	else if(start_index == fromEnd) index = alloc_chunks_counter - 1;
		
	while(alloc_chunks_counter > 0){
		allocator.m_free(allocated[index]);

		if(start_index == fromStart)    index++;
		else if(start_index == fromEnd) index--;

		alloc_chunks_counter--;

		//Проверим, что кол-во свободных и выделенных блоков сходится
		assert_param(alloc_chunks_counter == allocator.get_chunks_num_in_use());
		assert_param((allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES - alloc_chunks_counter) == allocator.get_free_chunks_num());
		//Проверим, что всего только одна непрерывная свободная область памяти
		assert_param(allocator.get_size_of_free_list() == 1);
	}

	//Вся память должна быть освобождена
	assert_param(allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES == allocator.get_free_chunks_num());
	assert_param(allocator.get_chunks_num_in_use() == 0);

	//std::cout << test_name <<" passed" << std::endl;
}

void Test_alloc_and_free_through_one(Allocator& allocator, const char* test_name, IndexDir start_index){
	
	//std::cout << test_name << " start" << std::endl;
	//Allocator allocator = Allocator();
	char* allocated[Allocator::config::NUM_OF_CHUNKS_IN_HEAP] = {};

	size_t alloc_chunks_counter = 0;
	//Выделим столько блоков, сколько сможем и проверим
	Test_max_alloc(allocator, alloc_chunks_counter, allocated);

	size_t num_of_chunks = alloc_chunks_counter;
	size_t index = 0;
	size_t expected_size_of_list = 0;
	//Переменная, чтобы можно было поменять направление изменение индекса
	size_t index_direction = 0; 
	
	//Будем освобождать сначала четные блоки, потом нечетные
	//Начиная с начала или с конца
	for(size_t offset = 0; offset <= 1; offset++){

		if(start_index == fromStart) {
			index = offset;
			index_direction = 0;
		}
		else if(start_index == fromEnd) {
			index = num_of_chunks - 1 - offset;
			index_direction = num_of_chunks - 1;
		}

		while(labs((long)index_direction - (long)index) < num_of_chunks){
			
			allocator.m_free(allocated[index]);
			
			if(start_index == fromStart)
				index += 2;
			else if(start_index == fromEnd)
				index -= 2;

			alloc_chunks_counter--;
			//Пока мы освобождаем четные блоки, размер списка отдельных свободных блоков увеличивается
			if(offset == 0)
				expected_size_of_list++;
			//Когда начинаем освобождать нечетные блоки, то свободные области начнут соединяться
			//И их кол-во будет уменьшаться, но минимальное кол-во будет равно 1
			else if(offset == 1){
				expected_size_of_list--;
				if(expected_size_of_list < 1) expected_size_of_list = 1;
			}

			assert_param(expected_size_of_list == allocator.get_size_of_free_list());

			//Проверим, что кол-во свободных и выделенных блоков сходится
			assert_param(alloc_chunks_counter == allocator.get_chunks_num_in_use());
			assert_param((allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES - alloc_chunks_counter) == allocator.get_free_chunks_num());
		}
	}    

	//Вся память должна быть освобождена
	assert_param(allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES == allocator.get_free_chunks_num());
	assert_param(allocator.get_chunks_num_in_use() == 0);

	//std::cout << test_name <<" passed" << std::endl;
}

void Test_alloc_and_free_through_one_v2(Allocator& allocator, const char* test_name, IndexDir start_index){
	
	//std::cout << test_name << " start" << std::endl;
	//Allocator allocator = Allocator();
	char* allocated[Allocator::config::NUM_OF_CHUNKS_IN_HEAP] = {};

	size_t alloc_chunks_counter = 0;
	//Выделим столько блоков, сколько сможем и проверим
	Test_max_alloc(allocator, alloc_chunks_counter, allocated);

	size_t num_of_chunks = alloc_chunks_counter;
	size_t index = 0;
	size_t expected_size_of_list = 0;
	//Переменная, чтобы можно было поменять направление изменение индекса
	size_t index_direction = 0; 
	
	//На первом круге будем освобождать блоки через один
	//На втором круге будем выделять блоки и должны в итоге быть выделены опять все
	//Начиная с начала или с конца
	for(size_t cycle = 0; cycle <= 1; cycle++){

		if(start_index == fromStart) {
			index = 0;
			index_direction = 0;
		}
		else if(start_index == fromEnd) {
			index = num_of_chunks - 1;
			index_direction = num_of_chunks - 1;
		}

		while(labs((long)index_direction - (long)index) < num_of_chunks){
			
			if(cycle == 0)
				allocator.m_free(allocated[index]);
			else if(cycle == 1){
				allocator.m_alloc_chunk();
			}
			
			if(start_index == fromStart)
				index += 2;
			else if(start_index == fromEnd)
				index -= 2;
	
			//Пока мы освобождаем блоки через один, размер списка отдельных свободных блоков увеличивается
			if(cycle == 0) {
				expected_size_of_list++;
				alloc_chunks_counter--;
			}
			//Когда начинаем выделять блоки, то кол-во отдельных свободных областей памяти будет уменьшаться
			//И в конце их должно быть 0
			else if(cycle == 1){
				expected_size_of_list--;
				alloc_chunks_counter++;
			}

			assert_param(expected_size_of_list == allocator.get_size_of_free_list());

			//Проверим, что кол-во свободных и выделенных блоков сходится
			assert_param(alloc_chunks_counter == allocator.get_chunks_num_in_use());
			assert_param((allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES - alloc_chunks_counter) == allocator.get_free_chunks_num());
		}
	}

	//Проверим, что если попытаемся выделить еще блок, то получим NULL
	assert_param((char*)allocator.m_alloc_chunk() == NULL);
	//Проверим, что в списке свободных блоков нет
	assert_param(allocator.get_size_of_free_list() == 0);

	//Освободим все блоки
	//Будем освобождать с начала или с конца
	if(start_index == fromStart)    index = 0;
	else if(start_index == fromEnd) index = alloc_chunks_counter - 1;
		
	while(alloc_chunks_counter > 0){
		allocator.m_free(allocated[index]);

		if(start_index == fromStart)    index++;
		else if(start_index == fromEnd) index--;

		alloc_chunks_counter--;

		//Проверим, что кол-во свободных и выделенных блоков сходится
		assert_param(alloc_chunks_counter == allocator.get_chunks_num_in_use());
		assert_param((allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES - alloc_chunks_counter) == allocator.get_free_chunks_num());
		//Проверим, что всего только одна непрерывная свободная область памяти
		assert_param(allocator.get_size_of_free_list() == 1);
	}

	//Вся память должна быть освобождена
	assert_param(allocator.get_total_heap_size() / Allocator::TOTAL_CHUNK_BYTES == allocator.get_free_chunks_num());
	assert_param(allocator.get_chunks_num_in_use() == 0);

	//std::cout << test_name <<" passed" << std::endl;
}
