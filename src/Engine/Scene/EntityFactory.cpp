#include "EntityFactory.h"

namespace Engine
{
EntityFactory::EntityFactory() { }

Entity* EntityFactory::createEntity(EntityType type, std::string* name) { }

Entity* EntityFactory::createEmptyEntity(std::string* name) { }
Entity* EntityFactory::createCubeEntity(std::string* name) { }
Entity* EntityFactory::createSphereEntity(std::string* name) { }

}
