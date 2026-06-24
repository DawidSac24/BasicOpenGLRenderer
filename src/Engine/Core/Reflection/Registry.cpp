#include "Registry.h"

#include <string>

#include "Engine/Core/Log.h"
#include "Engine/Core/Reflection/ClassDescriptor.h"
#include "Registry.h"

namespace Core
{
std::unordered_map<std::string, ClassDescriptor>& Registry::getMap()
{
    static std::unordered_map<std::string, ClassDescriptor> s_descriptors;
    return s_descriptors;
}

ClassDescriptor& Registry::registerClass(const std::string& className)
{
    return getMap()[className];
}

ClassDescriptor* Registry::getClass(const std::string& className)
{
    auto& map = getMap();

    auto it = map.find(className);
    if (it != map.end())
    {
        return &(it->second);
    }

    CORE_INFO("[Registry]: class ", className, " not found");
    return nullptr;
}
}
