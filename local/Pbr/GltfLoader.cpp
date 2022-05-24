#include "Pbr.h"


NAMESPACE_TOPSIDE_BEGIN


// Create a DirectX texture view from a tinygltf Image.
ComPtr<ID3D11ShaderResourceView> LoadImage(ID3D11Device* device, const tinygltf::Image& image, bool sRGB)
{
    // First convert the image to RGBA if it isn't already.
    Vector<byte> tempBuffer;
    const byte* rgbaBuffer = GltfHelper::ReadImageAsRGBA(image, &tempBuffer);
    if (rgbaBuffer == nullptr)
    {
        return nullptr;
    }

    const DXGI_FORMAT format = sRGB ? DXGI_FORMAT_R8G8B8A8_UNORM_SRGB : DXGI_FORMAT_R8G8B8A8_UNORM;
    return Pbr::Texture::CreateTexture(device, rgbaBuffer, image.width * image.height * 4, image.width, image.height, format);
}

// Create a DirectX sampler state from a tinygltf Sampler.
ComPtr<ID3D11SamplerState> CreateSampler(ID3D11Device* device, const tinygltf::Model& gltf_model, const tinygltf::Sampler& sampler)
{
    D3D11_SAMPLER_DESC samplerDesc{};
    // Not supported: Mipmap filters (NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR)
    samplerDesc.Filter =
        (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_NEAREST && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) ? D3D11_FILTER_MIN_MAG_MIP_POINT :
        (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_NEAREST && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) ? D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR :
        (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_LINEAR  && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) ? D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR :
        (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_LINEAR  && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU =
        sampler.wrapS == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ? D3D11_TEXTURE_ADDRESS_CLAMP :
        sampler.wrapS == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV =
        sampler.wrapT == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ? D3D11_TEXTURE_ADDRESS_CLAMP :
        sampler.wrapT == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    ComPtr<ID3D11SamplerState> samplerState;
    Pbr::Internal::ThrowIfFailed(device->CreateSamplerState(&samplerDesc, &samplerState));
    return samplerState;
}

// Maps a glTF material to a PrimitiveBuilder. This optimization combines all primitives which use
// the same material into a single primitive for reduced draw calls. Each primitive's vertex specifies
// which node it corresponds to any appropriate node transformation be happen in the shader.
using PrimitiveBuilderMap = std::map<int, Pbr::PrimitiveBuilder>;

// Load a glTF node from the tinygltf object model. This will process the node's mesh (if specified) and then recursively load the child nodes too.
void LoadNode(Pbr::NodeIndex_t parent_node_index, const tinygltf::Model& gltf_model, int nodeId, PrimitiveBuilderMap& prim_builder_map, Pbr::Model& model)
{
    const tinygltf::Node& gltfNode = gltf_model.nodes.at(nodeId);

    // Read the local transform for this node and add it into the Pbr Model.
    const mat4 nodeLocalTransform = GltfHelper::ReadNodeLocalTransform(gltfNode);
    const Pbr::NodeIndex_t transform_idx = model.AddNode(nodeLocalTransform, parent_node_index, gltfNode.name).Index;

    if (gltfNode.mesh != -1) // Load the node's optional mesh when specified.
    {
        // A glTF mesh is composed of primitives.
        const tinygltf::Mesh& gltfMesh = gltf_model.meshes.at(gltfNode.mesh);
        for (const tinygltf::Primitive& gltfPrimitive : gltfMesh.primitives)
        {
            // Read the primitive data from the glTF buffers.
            const GltfHelper::Primitive primitive = GltfHelper::ReadPrimitive(gltf_model, gltfPrimitive);

            // Insert or append the primitive into the PBR primitive builder. Primitives which use the same
            // material are appended to reduce the number of draw calls.
            Pbr::PrimitiveBuilder& prim_builder = prim_builder_map[gltfPrimitive.material];

            // Use the starting offset for vertices and indices since multiple glTF primitives can
            // be put into the same primitive builder.
            const uint32 startVertex = (uint32)prim_builder.vertices.size();
            const uint32 startIndex = (uint32)prim_builder.indices.size();

            // Convert the GltfHelper vertices into the PBR vertex format.
            prim_builder.vertices.resize(startVertex + primitive.vertices.size());
            for (size_t i = 0; i < primitive.vertices.size(); i++)
            {
                const GltfHelper::Vertex& vertex = primitive.vertices[i];
                Pbr::Vertex pbrVertex;
                pbrVertex.position = vertex.position;
                pbrVertex.normal = vertex.normal;
                pbrVertex.tangent = vertex.tangent;
                pbrVertex.tex_coord = vertex.tex_coord;
                pbrVertex.mdl_transform_idx = transform_idx;

                prim_builder.vertices[i + startVertex] = pbrVertex;
            }

            // Insert indicies with reverse winding order.
            prim_builder.indices.resize(startIndex + primitive.indices.size());
            for (size_t i = 0; i < primitive.indices.size(); i += 3)
            {
                prim_builder.indices[startIndex + i + 0] = startVertex + primitive.indices[i + 0];
                prim_builder.indices[startIndex + i + 1] = startVertex + primitive.indices[i + 2];
                prim_builder.indices[startIndex + i + 2] = startVertex + primitive.indices[i + 1];
            }
        }
    }

    // Recursively load all children.
    for (const int childNodeId : gltfNode.children)
    {
        LoadNode(transform_idx, gltf_model, childNodeId, prim_builder_map, model);
    }
}
}

namespace Gltf
{

Shared<Pbr::Model> FromGltfObject(
    const Pbr::Resources& pbr_res,
    const tinygltf::Model& gltf_model,
    const mat4& rootGltfTransform)
{
    // Start off with an empty Pbr Model.
    auto model = std::make_shared<Pbr::Model>();

    // Read and transform mesh/node data. Primitives with the same material are merged to reduce draw calls.
    PrimitiveBuilderMap prim_builder_map;
    {
        const int defaultSceneId = (gltf_model.defaultScene == -1) ? 0 : gltf_model.defaultScene;
        const tinygltf::Scene& defaultScene = gltf_model.scenes.at(defaultSceneId);

        // The Pbr::Model will already have a root node, which is often used to dynamically move the object. This node
        // is the root of the glTF model and can be used to create a persistent transform. This is useful if the model
        // is not positioned or scaled correctly.
        const Pbr::NodeIndex_t gltfRootNodeIndex = model->AddNode(rootGltfTransform, Pbr::RootNodeIndex, "gltf_root").Index;

        // Process the root scene nodes. The children will be processed recursively.
        for (const int rootNodeId : defaultScene.nodes)
        {
            LoadNode(gltfRootNodeIndex, gltf_model, rootNodeId, prim_builder_map, *model);
        }
    }

    // Load the materials referenced by the primitives
    std::map<int, Shared<Pbr::Material>> materialMap;
    {
        // Create D3D cache for reuse of texture views and samplers when possible.
        using ImageKey = std::tuple<const tinygltf::Image*, bool>; // Item1 is a pointer to the image, Item2 is sRGB.
        std::map<ImageKey, ComPtr<ID3D11ShaderResourceView>> imageMap;
        std::map<const tinygltf::Sampler*, ComPtr<ID3D11SamplerState>> samplerMap;

        // prim_builder_map is grouped by material. Loop through the referenced materials and load their resources. This will only
        // load materials which are used by the active scene.
        for (const auto& prim_builderPair : prim_builder_map)
        {
            Shared<Pbr::Material> pbrMaterial;

            const int materialIndex = prim_builderPair.first;
            if (materialIndex == -1) // No material was referenced. Make up a material for it.
            {
                // Default material is a grey material, 50% roughness, non-metallic.
                pbrMaterial = Pbr::Material::CreateFlat(pbr_res, Colors::Gray, 0.5f);
            }
            else
            {
                const tinygltf::Material& gltfMaterial = gltf_model.materials.at(materialIndex);

                const GltfHelper::Material material = GltfHelper::ReadMaterial(gltf_model, gltfMaterial);
                pbrMaterial = std::make_shared<Pbr::Material>(pbr_res);

                // Read a tinygltf texture and sampler into the Pbr Material.
                auto loadTexture = [&](Pbr::ShaderSlots::PSMaterial slot, const GltfHelper::Material::Texture& texture, bool sRGB, Cvec4 defaultRGBA)
                {
                    // Find or load the image referenced by the texture.
                    const ImageKey imageKey = std::make_tuple(texture.Image, sRGB);
                    ComPtr<ID3D11ShaderResourceView> tex_view = imageMap[imageKey];
                    if (!tex_view) // If not cached, load the image and store it in the texture cache.
                    {
                        // TODO: Generate mipmaps if sampler's minification filter (minFilter) uses mipmapping.
                        // TODO: If texture is not power-of-two and (sampler has wrapping=repeat/mirrored_repeat OR minFilter uses mipmapping), resize to power-of-two.
                        tex_view = texture.Image != nullptr ?
                            LoadImage(pbr_res.GetDevice().Get(), *texture.Image, sRGB) :
                            pbr_res.CreateSolidColorTexture(defaultRGBA);
                        imageMap[imageKey] = tex_view;
                    }

                    // Find or create the sampler referenced by the texture.
                    ComPtr<ID3D11SamplerState> samplerState = samplerMap[texture.Sampler];
                    if (!samplerState) // If not cached, create the sampler and store it in the sampler cache.
                    {
                        samplerState = texture.Sampler != nullptr ?
                            CreateSampler(pbr_res.GetDevice().Get(), gltf_model, *texture.Sampler) :
                            Pbr::Texture::CreateSampler(pbr_res.GetDevice().Get(), D3D11_TEXTURE_ADDRESS_WRAP);
                        samplerMap[texture.Sampler] = samplerState;
                    }

                    pbrMaterial->SetTexture(slot, tex_view.Get(), samplerState.Get());
                };

                pbrMaterial->Name = gltfMaterial.name;

                pbrMaterial->parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
                    data.base_clr_factor = material.base_clr_factor;
                    data.metallic_factor = material.metallic_factor;
                    data.roughness_factor = material.roughness_factor;
                    data.emissive_factor = material.emissive_factor;
                    data.occlusion_strength = material.occlusion_strength;
                    data.normal_scale = material.normal_scale;
                });

                loadTexture(Pbr::ShaderSlots::BaseColor, material.BaseColorTexture, false /* sRGB */, vec4loader{ 1, 1, 1, 1 });
                loadTexture(Pbr::ShaderSlots::MetallicRoughness, material.MetallicRoughnessTexture, false /* sRGB */, vec4loader{ 1, 1, 1, 1 });
                loadTexture(Pbr::ShaderSlots::Emissive, material.EmissiveTexture, true /* sRGB */, vec4loader{ 1, 1, 1, 1 });
                loadTexture(Pbr::ShaderSlots::normal, material.normalTexture, false /* sRGB */, vec4loader{ 0.5f, 0.5f, 1, 1 });
                loadTexture(Pbr::ShaderSlots::Occlusion, material.OcclusionTexture, false /* sRGB */, vec4loader{ 1, 1, 1, 1 });

                // Not supported: alphaMode ("OPAQUE", "MASK", "BLEND")
                // Not supported: alphaCutoff (default: 0.5)
                // Not supported: doubleSided
            }

            materialMap.insert(std::make_pair(materialIndex, std::move(pbrMaterial)));
        }
    }

    // Convert the primitive builders into primitives with their respective material and add it into the Pbr Model.
    for (const auto& prim_builderPair : prim_builder_map)
    {
        const Pbr::PrimitiveBuilder& prim_builder = prim_builderPair.second;
        const Shared<Pbr::Material>& material = materialMap.find(prim_builderPair.first)->second;
        model->AddPrimitive(Pbr::Primitive(pbr_res, prim_builder, material));
    }

    return model;
}

Shared<Pbr::Model> FromGltfBinary(
    const Pbr::Resources& pbr_res,
    const byte* buffer,
    uint32 buffer_bytes,
    const mat4& root_transform)
{
    // Parse the GLB buffer data into a tinygltf model object.
    tinygltf::Model gltf_model;
    String errorMsg, warnMsg;
    tinygltf::TinyGLTF loader;
    if (!loader.LoadBinaryFromMemory(&gltf_model, &errorMsg, &warnMsg, buffer, buffer_bytes, "."))
    {
        const auto msg = String("\r\nFailed to load gltf model (") + std::to_string(buffer_bytes) + " bytes). Error: " + errorMsg;
        throw std::exception(msg.c_str());
    }

    return FromGltfObject(pbr_res, gltf_model, root_transform);
}

}

NAMESPACE_TOPSIDE_END

