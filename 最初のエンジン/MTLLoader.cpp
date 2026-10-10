#include "MTLLoader.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <Windows.h>

bool MTLLoader::Load(
    const char* fileName,
    std::string& textureFileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        MessageBoxA(
            nullptr,
            fileName,
            "MTL OPEN ERROR",
            MB_OK);

        return false;
    }

    MessageBoxA(
        nullptr,
        "MTL OPEN OK",
        "MTL",
        MB_OK);

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
                MessageBoxA(
                    nullptr,
                    "map_Kd enpty",
                    "MTL ERROR",
                    MB_OK);

                return false;
            }

            MessageBoxA(
                nullptr,
                textureName.c_str(),
                "TEXTURE NAME",
                MB_OK);

            std::filesystem::path mtlPath(fileName);

            std::filesystem::path texturePath =
                mtlPath.parent_path() / textureName;

            textureFileName =
                texturePath.string();

            MessageBoxA(
                nullptr,
                textureFileName.c_str(),
                "TEXTURE PATH",
                MB_OK);

            return true;
        }
    }

    MessageBoxA(
        nullptr,
        "map_Kd が見つかりません",
        "MTL ERROR",
        MB_OK);

    return false;
}