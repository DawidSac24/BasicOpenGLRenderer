#pragma once

#include "Engine/Core/Reflection/PropertyType.h"
#include "Engine/Core/UUID.h"
#include <glm/ext/vector_float3.hpp>
namespace Core
{
template <typename T>
struct getPropertyType
{
    static constexpr PropertyType value = PropertyType::CustomClass;
};

template <>
struct getPropertyType<int>
{
    static constexpr PropertyType value = PropertyType::Int;
};
template <>
struct getPropertyType<float>
{
    static constexpr PropertyType value = PropertyType::Float;
};
template <>
struct getPropertyType<glm::vec3>
{
    static constexpr PropertyType value = PropertyType::Vector3;
};
template <>
struct getPropertyType<UUID>
{
    static constexpr PropertyType value = PropertyType::AssetHandle;
};
}
