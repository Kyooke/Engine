#include "OBJLoader.h"
#include "MTLLoader.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <Windows.h>
struct Normal
{
    float x;
    float y;
    float z;
};

struct TexCoord
{
    float u;
    float v;
};


bool OBJLoader::Load(
    const char* filename,
    std::vector<Vertex>& vertices,
    std::vector<unsigned int>& indices,
    std::string& materialFile)
{
    std::string path =
        std::filesystem::current_path().string();

    MessageBoxA(
        nullptr,
        path.c_str(),
        "Current Directory",
        MB_OK
    );
    MessageBoxA(
        nullptr,
        filename,
        "roodOBJ",
        MB_OK
    );
    std::ifstream file(filename);

    if (!file.is_open())
    {
        MessageBoxA(
            nullptr,
            "OBJ OPEN ERROR",
            "Debug",
            MB_OK
        );

        return false;
    }
    else
    {
        MessageBoxA(
            nullptr,
            "OBJ OPEN OK",
            "Debug",
            MB_OK
        );
    }


    std::vector<Normal> normals;
    std::vector<TexCoord> texcoords;


    std::string line;


    while (std::getline(file, line))
    {
        OutputDebugStringA(line.c_str());
        OutputDebugStringA("\n");

        std::stringstream ss(line);

        std::string type;

        ss >> type;

        if (type == "mtllib")
        {
            std::string mtlFile;
            ss >> mtlFile;

            std::filesystem::path objPath(filename);
            std::filesystem::path mtlPath =
                objPath.parent_path() / mtlFile;

            MTLLoader::Load(
                mtlPath.string().c_str(),
                materialFile);

            continue;
        }

        // 頂点
        if (type == "v")
        {
            MessageBoxA(
                nullptr,
                "v found",
                "Debug",
                MB_OK
            );
            Vertex vertex;

            ss >> vertex.x;
            ss >> vertex.y;
            ss >> vertex.z;

            vertex.nx = 0;
            vertex.ny = 0;
            vertex.nz = 0;

            vertices.push_back(vertex);
        }

        // 法線
        else if (type == "vn")
        {
            Normal normal;

            ss >> normal.x;
            ss >> normal.y;
            ss >> normal.z;

            normals.push_back(normal);
        }

        // テクスチャ座標
        else if (type == "vt")
        {
            TexCoord tex;

            ss >> tex.u;
            ss >> tex.v;

            tex.v = 1.0f - tex.v;

            texcoords.push_back(tex);
        }


        else if (type == "f")
        {
            std::string s0;
            std::string s1;
            std::string s2;


            ss >> s0;
            ss >> s1;
            ss >> s2;


            unsigned int v0, vt0, vn0;
            unsigned int v1, vt1, vn1;
            unsigned int v2, vt2, vn2;


            sscanf_s(
                s0.c_str(),
                "%u/%u/%u",
                &v0,
                &vt0,
                &vn0
            );


            sscanf_s(
                s1.c_str(),
                "%u/%u/%u",
                &v1,
                &vt1,
                &vn1
            );


            sscanf_s(
                s2.c_str(),
                "%u/%u/%u",
                &v2,
                &vt2,
                &vn2
            );


            vertices[v0 - 1].nx = normals[vn0 - 1].x;
            vertices[v0 - 1].ny = normals[vn0 - 1].y;
            vertices[v0 - 1].nz = normals[vn0 - 1].z;


            vertices[v1 - 1].nx = normals[vn1 - 1].x;
            vertices[v1 - 1].ny = normals[vn1 - 1].y;
            vertices[v1 - 1].nz = normals[vn1 - 1].z;


            vertices[v2 - 1].nx = normals[vn2 - 1].x;
            vertices[v2 - 1].ny = normals[vn2 - 1].y;
            vertices[v2 - 1].nz = normals[vn2 - 1].z;

            vertices[v0 - 1].u = texcoords[vt0 - 1].u;
            vertices[v0 - 1].v = texcoords[vt0 - 1].v;

            vertices[v1 - 1].u = texcoords[vt1 - 1].u;
            vertices[v1 - 1].v = texcoords[vt1 - 1].v;

            vertices[v2 - 1].u = texcoords[vt2 - 1].u;
            vertices[v2 - 1].v = texcoords[vt2 - 1].v;


            indices.push_back(v0 - 1);
            indices.push_back(v1 - 1);
            indices.push_back(v2 - 1);
        }
    }
    std::stringstream debug;

    debug << "vertices : " << vertices.size()
        << "\nindices : " << indices.size();

   
    return true;
}