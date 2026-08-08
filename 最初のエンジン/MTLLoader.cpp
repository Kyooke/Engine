#include "MTLLoader.h"

#include <fstream>
#include <sstream>
#include <filesystem>

bool MTLLoader::Load(
    const char* fileName,
    std::string& textureFileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string type;
        ss >> type;

        if (type == "map_Kd")
        {
            std::string textureName;
            ss >> textureName;

            if (textureName.empty())
            {
                return false;
            }

            std::filesystem::path mtlPath(fileName);

            std::filesystem::path texturePath =
                mtlPath.parent_path() / textureName;

            textureFileName =
                texturePath.string();

            return true;
        }
    }

    return false;
}
