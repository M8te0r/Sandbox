#pragma once
#include <vector>
#include <string>
namespace Elysian
{
    class Texture
    {
    public:
        // 程序ID
        unsigned int ID;

    public:
        Texture(const char *path);
        Texture(std::vector<std::string> faces);
    };

} // namespace Elysian
