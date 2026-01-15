#pragma once

#include <random>
#include <string>

namespace Core
{

class UUID
{
public:
    UUID()
        : m_UUID(s_UniformDistribution(s_Engine))
    {
    }
    UUID(uint64_t uuid)
        : m_UUID(uuid)
    {
    }

    UUID(const std::string& id)
        : m_UUID(std::stoull(id))
    {
    }

    operator uint64_t() const { return m_UUID; }

private:
    uint64_t m_UUID;

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine;
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;
};

}

namespace std
{
template <>
struct hash<Core::UUID>
{
    std::size_t operator()(const Core::UUID& uuid) const { return hash<uint64_t>()((uint64_t)uuid); }
};
}
