#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_
#include "TemplateParser.h"
#include "ComponentDataArray.h"
#include "Archetype.h"
#include <unordered_map>
#include <unordered_set>

using EntityId = unsigned int;
using ArchetypeSet = std::unordered_set<ArchetypeId>;

struct Archetype;

template<typename... ComponentTypes> struct ComponentComposition {
	using Tuple = std::tuple<ComponentTypes...>;
	static constexpr size_t size = sizeof...(ComponentTypes);
	template <std::size_t N> using ComponentTypeAt = typename std::tuple_element<N, Tuple>::type;
};



typedef struct GraphEdge {
	Archetype& add;
	Archetype& remove;
} GraphEdge;

template<typename... T> struct ArchetypeKey {};

typedef struct EntityRecord {
	Archetype archetype;
	size_t column_index;
} Record;

class EntityManager {
public:
	EntityManager();
	EntityId CreateEntity();

	template<typename... ComponentTypes>EntityId CreateEntity(ComponentTypes... components) {
		RegisterArchetype<ComponentTypes...>();
		Archetype& archetype = composition_archetype_map.at(typeid(ArchetypeKey<ComponentTypes...>));
		EntityRecord record = {};
		record.archetype = archetype;
		record.column_index = archetype.entity_count++;
		entity_archetype_map.insert(std::pair<EntityId, EntityRecord>(next_id, record));
		TemplateParseParameter::AddEntityToArchetype(archetype.components, components...);
		return next_id++;
	}

	template <typename ComponentType> ComponentType& GetComponent(EntityId entity_id) {
		EntityRecord& entity_record = entity_archetype_map[entity_id];
		Archetype& entity_archetype = entity_record.archetype;
		int row = entity_archetype.component_type_row_index[typeid(ComponentType)];
		int column = entity_record.column_index;
		char* tp = (char*)entity_archetype.components[row].data;
		ComponentType* temp = (ComponentType*)(tp+ column*sizeof(ComponentType));
		return *temp;
	}

	template<typename... ComponentTypes> Archetype* GetArchetype() {
		if (composition_archetype_map.find(typeid(ArchetypeKey<ComponentTypes...>)) == composition_archetype_map.end()) {
			return NULL;
		}
		return &composition_archetype_map.at(typeid(ArchetypeKey<ComponentTypes...>));
	}

	template<typename... ComponentTypes> void RegisterArchetype() {
		if (composition_archetype_map.find(typeid(ArchetypeKey<ComponentTypes...>)) == composition_archetype_map.end()) {
			Archetype archetype;
			InitializeComponentStorage(archetype.components, sizeof...(ComponentTypes));
			TemplateParseType<ComponentTypes...>::InitializeComponentTypeRowIndexMap(archetype.component_type_row_index);
			TemplateParseType<ComponentTypes...>::InitializeComponentDataArrays(archetype.components);
			composition_archetype_map.insert(std::pair<std::type_index, Archetype>(typeid(ArchetypeKey<ComponentTypes...>), archetype));
		}
	}
protected:
private:
	std::unordered_map<std::type_index, Archetype> composition_archetype_map;
	std::unordered_map<EntityId, EntityRecord> entity_archetype_map;
	EntityId next_id;
};
#endif