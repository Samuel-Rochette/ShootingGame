#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;


// Generate a unique ID for Component Type
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// Fetch Component Type ID
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

// Maximum number of Components that can be stored in an Entity
constexpr std::size_t maxComponents = 32;

// Maximum number of groups that an Entity can belong to
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

// Component class - Belongs to an entity - Contains data/methods
class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

// Entity Class - Container for Components
class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> entityComponents;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	// Iterate through all the components that belong the
	// Entity instance and invoke its update method
	void update()
	{
		for (auto& c : entityComponents) c->update();
	}

	// Iterate through all the components that belong the
	// Entity instance and invoke its draw method
	void draw()
	{
		for (auto& c : entityComponents) c->draw();
	}

	// Returns whether or not the Entity is active
	bool isActive() { return active; }

	// Sets the Entity's active flag to false which is checked 
	// by the manager's refresh function every frame in order to
	// dismiss the Entity
	void destroy() { active = false; }

	// Returns true if the Entity belongs to the member group
	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	// Assigns the Entity to the member group
	void addGroup(Group mGroup);

	// Removes the Entity from the member group
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	// Returns true if a Component of a matching type belongs to the Entity
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	// Assigns a new Component to the Entity
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		entityComponents.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	// Calls a Component that belongs to the Entity,
	// properties and methods can be accessed from here
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

// Manager class - creates, destroys and updates Entities
class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:

	// Iterate through every Entity and invoke its update method
	void update()
	{
		for (auto& e : entities) e->update();
	}

	// Iterate through every Entity and invoke its draw method
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	// Iterate through every Entity and dismiss it if
	// it is inactive or it does not belong to a group
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	// Add the member Entity to the member Group
	void addToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	// Returns a vector of all the Entities that belong to the member group
	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	// Creates a new Entity
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};