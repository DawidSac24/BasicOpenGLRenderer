#pragma once

#include "./IProperty.h"
#include "Engine/Core/Reflection/TypeTraits.h"

namespace Core
{
template <typename ClassType, typename VarType>
class Property : public IProperty
{
public:
    Property(const char* name, VarType ClassType::* ptr)
        : m_name(name)
        , m_memberPtr(ptr)
    {
    }

    const char* getName() const override { return m_name; }
    void* getVarPtr(void* instance) const override
    {
        ClassType* typedInstance = static_cast<ClassType*>(instance);

        return &(typedInstance->*m_memberPtr);
    }

    PropertyType getType() const override
    {
        return getPropertyType<VarType>::value;
    }

private:
    const char* m_name;
    VarType ClassType::* m_memberPtr;
};
}
