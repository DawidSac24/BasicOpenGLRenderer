// UUID.h
#include <random>

namespace Core
{

class UUID
{
public:
    UUID()
        : m_UUID(s_UniformDistribution(s_Engine))
    {
    }

    // Allow copying/conversion to uint64_t
    operator uint64_t() const { return m_UUID; }

private:
    uint64_t m_UUID;

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine;
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;
};

// (Implementation of statics goes in .cpp file)
}

// Enable hashing so it works in unordered_map
namespace std
{
template <> struct hash<Core::UUID>
{
    std::size_t operator()(const Core::UUID& uuid) const { return hash<uint64_t>()((uint64_t)uuid); }
};
}
