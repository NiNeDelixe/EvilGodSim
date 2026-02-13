#include "enginecore/core/assets/loaders/ModelsLoader.h"

void ModelsLoader::operator()(const std::filesystem::path& file_or_directory, const std::string& name,
	const std::shared_ptr<configs::AssetConfig>& settings)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenUVCoords |
        aiProcess_TransformUVCoords |
        aiProcess_OptimizeMeshes;

    const aiScene* scene = importer.ReadFile(file_or_directory.string(), flags);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG(ERROR) << "failed to import model cause:" << "Scene invalid";
        return;
    }

    auto model = processScene(scene);
    if (!model)
    {
        LOG(ERROR) << "failed to import model cause:" << "Model invalid";
        return;
    }

    model->setPath(file_or_directory);

    m_manager->store(std::move(model), name);
}

std::shared_ptr<Model> ModelsLoader::processScene(const aiScene* scene)
{
    auto model = std::make_shared<Model>();

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* aiMesh = scene->mMeshes[i];
        auto mesh = processMesh(aiMesh);
        if (mesh)
        {
            model->addMesh(std::move(mesh));
        }
    }

    return model;
}

std::shared_ptr<Mesh<DefaultAtributes>> ModelsLoader::processMesh(aiMesh* mesh)
{
    auto vertexData = extractVertexData(mesh);
    auto indexData = extractIndexData(mesh);

    if (vertexData.empty())
    {
        return nullptr;
    }

    return std::make_shared<Mesh<DefaultAtributes>>(
        vertexData.data(),
        mesh->mNumVertices,
        indexData.empty() ? nullptr : indexData.data(),
        indexData.size()
    );
}

std::vector<float> ModelsLoader::extractVertexData(aiMesh* mesh)
{
    std::vector<float> vertexData;
    vertexData.reserve(mesh->mNumVertices * 5); // position(3) + uv(2)

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        // Position
        vertexData.push_back(mesh->mVertices[i].x);
        vertexData.push_back(mesh->mVertices[i].y);
        vertexData.push_back(mesh->mVertices[i].z);

        // UV coordinates
        if (mesh->mTextureCoords[0])
        {
            vertexData.push_back(mesh->mTextureCoords[0][i].x);
            vertexData.push_back(mesh->mTextureCoords[0][i].y);
        }
        else
        {
            vertexData.push_back(0.0f);
            vertexData.push_back(0.0f);
        }
    }

    return vertexData;
}

std::vector<uint32_t> ModelsLoader::extractIndexData(aiMesh* mesh)
{
    std::vector<uint32_t> indices;

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return indices;
}
