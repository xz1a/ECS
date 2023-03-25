#ifndef _ARCHETYPE_H_
#define _ARCHETYPE_H_
#include "ComponentDataArray.h"
#include <unordered_map>
#include <typeindex>

using ArchetypeId = unsigned int;
typedef struct Archetype {
	ArchetypeId id;
	ComponentDataArray* components;
	std::unordered_map<std::type_index, unsigned int> component_type_row_index;
	int entity_count = 0;
} Archetype;
#endif