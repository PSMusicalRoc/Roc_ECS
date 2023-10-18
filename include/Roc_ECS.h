#ifndef _ROC_ECS_H_
#define _ROC_ECS_H_

/**
 * @file Roc_ECS.h
 * 
 * @brief Overall include for the Entity-Component System
 * 
 * @note This, and most base ECS classes, were adapted from
 * [Austin Morlan's amazing ECS writeup here.](https://austinmorlan.com/posts/entity_component_system/)
*/

// Core

#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "Coordinator.h"

// Components

#include "Components/Transform.h"
#include "Components/Gravity.h"
#include "Components/Sprite.h"
#include "Components/RectangleCollider.hpp"

// Systems

#include "Systems/RenderSpriteSys.hpp"
#include "Systems/CollisionSystem.hpp"

#endif