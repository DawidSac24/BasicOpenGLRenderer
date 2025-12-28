#pragma once

#include <filesystem>
#include <string>

namespace Core
{

class FileSystem
{
public:
    static std::string getPath(const std::string& path)
    {
// 1. Get the compiled definition (Development Mode)
#ifdef PROJECT_ROOT
        // std::filesystem handles slash/backslash conversion automatically
        std::filesystem::path root(PROJECT_ROOT);
        std::filesystem::path relative(path);
        return (root / relative).string();
#else
        // 2. Production Mode (Release)
        // Expects 'assets' folder to be next to the .exe
        return path;
#endif
    }
};

}
