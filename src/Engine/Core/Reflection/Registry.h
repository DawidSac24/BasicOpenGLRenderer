#pragma once

#include <string>
#include <unordered_map>

#include "ClassDescriptor.h"

#define REFLECT_CLASS(Type)                                \
    static bool s_##Type##_registered = []() {             \
        auto& desc = Core::Registry::registerClass(#Type); \
        Type::registerReflection(desc);                    \
        return true;                                       \
    }();

namespace Core
{
class Registry
{
public:
    static ClassDescriptor& registerClass(const std::string& className);
    static ClassDescriptor* getClass(const std::string& className);

private:
    static std::unordered_map<std::string, ClassDescriptor>& getMap();
};
}
