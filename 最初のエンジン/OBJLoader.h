#pragma once

#include <vector>
#include <string>

#include "Vertex.h"


class OBJLoader
{
public:

    static bool Load(
        const char* filename,
        std::vector<Vertex>& vertices,
        std::vector<unsigned int>& indices,
        std::string& materialFile
    );

};