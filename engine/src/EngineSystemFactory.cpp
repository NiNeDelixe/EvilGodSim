#include "enginecore/core/ecs/systems/managment/EngineSystemFactory.h"

std::shared_ptr<ISystem> EngineSystemFactory::createSystem(const SystemCategory &category)
{
    switch (category)
    {
    case SystemCategory::CAMERA_BEHAVIOR:
        return std::make_shared<FreeFlySystem>();
        break;
    
    // case SystemCategory::LOGIC:
    //     return std::make_shared<>();
    //     break;

    case SystemCategory::ROTATION:
        return std::make_shared<RotationSystem>();
        break;

    case SystemCategory::TRANSFORM :
        return std::make_shared<TransformSystem>();
        break;

    default:
        break;
    }

    return std::shared_ptr<ISystem>();
}

SystemsContainer EngineSystemFactory::createSystems()
{
    SystemsContainer systems{}; 
    
    magic_enum::enum_for_each<SystemCategory>(
        [=, &systems](const SystemCategory& category)
        {
            auto system = createSystem(category);
            if (system)
            {
                systems.add(system);
            }
        }
    );

    

    return systems;
}
