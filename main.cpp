#include <iostream>
#include "ECS.h"
#include <string>

struct Position {
	float x;
	float y; 
	float z;
};

struct Velocity {
	float x;
	float y;
	float z;
	float angle;
};

int main()
{
	EntityManager entity_manager = EntityManager();
	entity_manager.RegisterArchetype<Position, Velocity>();
	//test.
	EntityId id = entity_manager.CreateEntity(Position{1.0, 1.0, 1.0}, Velocity{ 0.0, 0.0, 0.0, 0.0});
	EntityId id2 = entity_manager.CreateEntity(Position{ 2.0, 2.0, 2.0 }, Velocity{ 0.0, 1.0, 0.0, 90.0 });
	Position& p = entity_manager.GetComponent<Position>(id);
	std::cout << p.x << ", " << p.y << ", " << p.z << std::endl;
	Velocity& v = entity_manager.GetComponent<Velocity>(id);
	std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.angle << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	Position& p2 = entity_manager.GetComponent<Position>(id2);
	std::cout << p2.x << ", " << p2.y << ", " << p2.z << std::endl;
	Velocity& v2 = entity_manager.GetComponent<Velocity>(id2);
	std::cout << v2.x << ", " << v2.y << ", " << v2.z << ", " << v2.angle << std::endl;
	Archetype* archetype = entity_manager.GetArchetype<Position, Velocity>();
}