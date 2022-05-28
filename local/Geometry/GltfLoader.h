// Functions to load glTF 2.0 content into a renderable Pbr::Model.

#pragma once


namespace tinygltf { class Model; }


NAMESPACE_TOPSIDE_BEGIN


//interface ID3D11Device;
//interface ID3D11DeviceContext3;

namespace Gltf {

// Creates a Pbr Model from tinygltf model with the specified root transform.
bool FromGltfObject(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const tinygltf::Model& gltf_model,
    const mat4& root_transform);

// Creates a Pbr Model from tinygltf model.
inline bool FromGltfObject(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const tinygltf::Model& gltf_model)
{
    return FromGltfObject(model, pbr_res, gltf_model, identity<mat4>());
}

// Creates a Pbr Model from glTF 2.0 GLB file content with the specified root transform.
bool FromGltfBinary(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const char* buffer,
    uint32 buffer_bytes,
    const mat4& root_transform);

// Creates a Pbr Model from glTF 2.0 GLB file content.
inline bool FromGltfBinary(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const char* buffer,
    uint32 buffer_bytes)
{
    return FromGltfBinary(model, pbr_res, buffer, buffer_bytes, identity<mat4>());
}

}


NAMESPACE_TOPSIDE_END

