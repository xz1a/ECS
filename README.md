
# ECS

An Archetype Entity Component System Framework for use in my own projects.




## Usage

- Basic Usage example
```
//First Define Entity Manager
EntityManager entity_manager = EntityManager();


//Define Components
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

//Register Archetype
entity_manager.RegisterArchetype<Position, Velocity>();

//Create Entity Example
EntityId id = entity_manager.CreateEntity(Position{1.0, 1.0, 1.0}, Velocity{ 0.0, 0.0, 0.0, 0.0});

//Get Component Example
Velocity& v = entity_manager.GetComponent<Velocity>(id);

//Retrieving Archetype Example
Archetype* archetype = entity_manager.GetArchetype<Position, Velocity>();
```
- Defining Systems
```

//Use Inheritance and Override Update Function.

class System {
public:
	virtual void Update(float p_delta_time) = 0;
}
```
## TODO

- Archetype graph for fast archetype querying.