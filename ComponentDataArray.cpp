#include "ComponentDataArray.h"

void InitializeComponentDataArray(ComponentDataArray* component_data_array, size_t size, size_t type_size) {
	if (size <= 0) {
		component_data_array->type_size = type_size;
		component_data_array->data = malloc(type_size);
		component_data_array->capacity = 1;
		component_data_array->data_count = 0;
	}
	else {
		component_data_array->type_size = type_size;
		component_data_array->data = malloc(size * type_size);
		component_data_array->capacity = size;
		component_data_array->data_count = 0;
	}
}

void AddToComponentDataArray(ComponentDataArray* component_data_array, void* data) {
	if (component_data_array->data_count == component_data_array->capacity) {
		component_data_array->capacity *= 2;
		component_data_array->data = realloc(component_data_array->data, component_data_array->capacity * component_data_array->type_size);
	}
	char* dest = (char*)component_data_array->data;
	memcpy(dest + (component_data_array->data_count * component_data_array->type_size), data, component_data_array->type_size);
	component_data_array->data_count++;
}


void InitializeComponentStorage(ComponentDataArray*& component_data_array_ptr, size_t component_type_count) {
	component_data_array_ptr = (ComponentDataArray*)malloc(sizeof(ComponentDataArray) * component_type_count);
	for (int i = 0; i < component_type_count; ++i) {
		component_data_array_ptr[i] = ComponentDataArray{};
	}
}