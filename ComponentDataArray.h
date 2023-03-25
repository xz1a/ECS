#ifndef _COMPONENT_DATA_ARRAY_H_
#define _COMPONENT_DATA_ARRAY_H_
#include <stdlib.h>
#include <memory>

typedef struct ComponentDataArray {
	void* data;
	size_t type_size;
	size_t data_count;
	size_t capacity;
} ComponentDataArray;

void InitializeComponentDataArray(ComponentDataArray* component_data_array, size_t size, size_t type_size);
void AddToComponentDataArray(ComponentDataArray* component_data_array, void* data);
void InitializeComponentStorage(ComponentDataArray*& component_data_array, size_t component_type_count);
#endif