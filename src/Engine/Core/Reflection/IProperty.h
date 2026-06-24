#pragma once

#include "Engine/Core/Reflection/PropertyType.h"
namespace Core
{
class IProperty
{
public:
    virtual ~IProperty() = default;

    virtual const char* getName() const = 0;
    virtual void* getVarPtr(void* instance) const = 0;
    virtual PropertyType getType() const = 0;
};
}
