#include "enginecore/core/ecs/systems/managment/EngineSystemFactory.h"

SystemsContainer EngineSystemFactory::createSystems()
{
    SystemsContainer systems{}; 
    
    systems.add(std::make_shared<FreeFlySystem>());
    systems.add(std::make_shared<RotationSystem>());
    systems.add(std::make_shared<TransformSystem>());
    

    return systems;
}
