#ifndef _ROC_COMPONENT_MANAGER_H_
#define _ROC_COMPONENT_MANAGER_H_

#include <memory>
#include <functional>
#include <string>

#include "RocLogger/RocLogger.hpp"
#include "IComponentArray.h"

class ComponentManager
{
public:
	template<typename T>
	bool AddComponent(Entity entity)
	{
		// Add a component to the array for an entity
        std::shared_ptr<ComponentArray<T>> ptr = GetComponentArray<T>();
        if (ptr == nullptr) {LogWarn("Couldn't get a ComponentArray for " + T::name()); return false;}
		return ptr->InsertData(entity, T());
	}

	template<typename T>
	bool AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
        std::shared_ptr<ComponentArray<T>> ptr = GetComponentArray<T>();
        if (ptr == nullptr) return false;
		return ptr->InsertData(entity, component);
	}

	template<typename T>
	bool RegisterComponent()
	{
		std::string typeName = T::name();

		if (mComponentTypes.find(typeName) != mComponentTypes.end())
        {
            LogError("Attempting to register ComponentType twice.");
            return false;
        }

		// Add this component type to the component type map
		mComponentTypes.insert({typeName, mNextComponentType});

		// Create a ComponentArray pointer and add it to the component arrays map
		mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

		mCreateCompFuncs[typeName] = [=](Entity e){ return this->AddComponent<T>(e); };

		// Increment the value so that the next component registered will be different
		++mNextComponentType;
        return true;
	}

	bool AddComponentToEntityFromText(Entity e, const std::string& typeName)
	{
		if (mCreateCompFuncs.find(typeName) == mCreateCompFuncs.end())
		{
			throw std::runtime_error(std::string("Could not find component ") + typeName);
		}

		return mCreateCompFuncs[typeName](e);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		std::string typeName = T::name();

		if (mComponentTypes.find(typeName) == mComponentTypes.end())
        {
            LogError("Attempted to access ComponentType before registering.");
            return MAX_COMPONENTS;
        }

		// Return this component's type - used for creating signatures
		return mComponentTypes[typeName];
	}

	ComponentType GetComponentType(const std::string& typeName)
	{
		if (mComponentTypes.find(typeName) == mComponentTypes.end())
        {
            LogError("Attempted to access ComponentType before registering.");
            return MAX_COMPONENTS;
        }

		// Return this component's type - used for creating signatures
		return mComponentTypes[typeName];
	}

	template<typename T>
	bool RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity
        std::shared_ptr<ComponentArray<T>> ptr = GetComponentArray<T>();
        if (ptr == nullptr) return false;
		return ptr->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
        std::shared_ptr<ComponentArray<T>> ptr = GetComponentArray<T>();
        /** @todo AGAIN PLEASE FIX, I HATE ASSERTS IN REAL CODE */
        if (ptr == nullptr) LogAssert(false && "GAH");
		return ptr->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : mComponentArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	// Map from type string pointer to a component type
	std::unordered_map<std::string, ComponentType> mComponentTypes{};

	// Map from type string pointer to a component array
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays{};

	std::unordered_map<std::string, std::function<bool(Entity)>> mCreateCompFuncs{};

	// The component type to be assigned to the next registered component - starting at 0
	ComponentType mNextComponentType{};

	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		std::string typeName = T::name();

		if (mComponentTypes.find(typeName) == mComponentTypes.end())
        {
            LogError("Attempted to access nonexistent ComponentArray.");
            return nullptr;
        }

		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};

#endif
