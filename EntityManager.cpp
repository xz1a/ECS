#include "EntityManager.h"

EntityManager::EntityManager() {
	next_id = 0;
	entity_archetype_map = std::unordered_map<EntityId, Record>();
	composition_archetype_map = std::unordered_map<std::type_index, Archetype>();
}

EntityId EntityManager::CreateEntity() {
	return next_id++;
}