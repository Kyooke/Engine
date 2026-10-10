#include "Model.h"
#include "Graphics.h"
#include "Vertex.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Image.h"

#include <vector>

struct ModelData
{
    Transform transform;

    std::vector<Mesh> meshes;

    int textureHandle = -1;

};

static std::vector<ModelData> models;

int Model::Load(const char* fileName)
{

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string textureFileName;


    OBJLoader::Load(
        fileName,
        vertices,
        indices,
        textureFileName);


    std::string text =
        "vertices : " + std::to_string(vertices.size()) +
        "\nindices : " + std::to_string(indices.size());

    MessageBoxA(
        nullptr,
        text.c_str(),
        "Model Data",
        MB_OK
    );


    ModelData data;

if (!textureFileName.empty())
{
    MessageBoxA(
        nullptr,
        textureFileName.c_str(),
        "Texture",
        MB_OK
    );

    data.textureHandle =
        Image::Load(textureFileName.c_str());
}


    Mesh mesh;

    mesh.Initialize(
        graphics_,
        vertices,
        indices);

    data.meshes.push_back(mesh);

    models.push_back(data);

    return (int)models.size() - 1;
}

void Model::SetTransform(
    int handle,
    const Transform& transform)
{
    if (handle < 0 ||
        handle >= models.size())
    {
        return;
    }

    models[handle].transform = transform;
}

void Model::SetTexture(
    int handle,
    int textureHandle)
{
    if (handle < 0 ||
        handle >= (int)models.size())
    {
        return;
    }

    models[handle].textureHandle = textureHandle;
}
void Model::Draw(int handle)
{
    if (handle < 0 ||handle >= (int)models.size())
    {
        return;
    }

    if (models[handle].textureHandle != -1)
    {
        Image::Set(models[handle].textureHandle);
    }

    for (auto& mesh : models[handle].meshes)
    {
        mesh.Draw(models[handle].transform);
    }
}

Graphics* Model::graphics_ = nullptr;

void Model::Initialize(Graphics* graphics)
{
    graphics_ = graphics;
}