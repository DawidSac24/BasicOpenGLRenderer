#pragma once

#include <memory>
#include <vector>

#include "Engine/Core/Reflection/IProperty.h"
#include "Engine/Core/Reflection/Property.h"

namespace Core
{
class ClassDescriptor
{
public:
    std::vector<std::unique_ptr<IProperty>> properties;

    template <typename ClassType, typename VarType>
    void addProperty(const char* name, VarType ClassType::* ptr)
    {
        properties.push_back(std::make_unique<Property<ClassType, VarType>>(name, ptr));
    }
};
}
