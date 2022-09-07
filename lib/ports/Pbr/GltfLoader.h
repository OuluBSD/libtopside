// Functions to load glTF 2.0 content into a renderable Pbr::Model.

#pragma once


interface ID3D11Device;
interface ID3D11DeviceContext3;

namespace tinygltf { class Model; }

namespace Gltf {

// Creates a Pbr Model from tinygltf model with the specified root transform.
std::shared_ptr<Pbr::Model> FromGltfObject(
    const Pbr::Resources& pbr_res,
    const tinygltf::Model& gltfModel,
    DirectX::CXMMATRIX rootTransform);

// Creates a Pbr Model from tinygltf model.
inline std::shared_ptr<Pbr::Model> FromGltfObject(
    const Pbr::Resources& pbr_res,
    const tinygltf::Model& gltfModel)
{
    return FromGltfObject(pbr_res, gltfModel, DirectX::XMMatrixIdentity());
}

// Creates a Pbr Model from glTF 2.0 GLB file content with the specified root transform.
std::shared_ptr<Pbr::Model> FromGltfBinary(
    const Pbr::Resources& pbr_res,
    _In_reads_bytes_(bufferBytes) const byte* buffer,
    uint32_t bufferBytes,
    DirectX::CXMMATRIX rootTransform);

// Creates a Pbr Model from glTF 2.0 GLB file content.
inline std::shared_ptr<Pbr::Model> FromGltfBinary(
    const Pbr::Resources& pbr_res,
    _In_reads_bytes_(bufferBytes) const byte* buffer,
    uint32_t bufferBytes)
{
    return FromGltfBinary(pbr_res, buffer, bufferBytes, DirectX::XMMatrixIdentity());
}

}
