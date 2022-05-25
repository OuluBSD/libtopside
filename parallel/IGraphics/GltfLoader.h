// Functions to load glTF 2.0 content into a renderable Pbr::Model.

#pragma once


namespace tinygltf { class Model; }


NAMESPACE_PARALLEL_BEGIN


//interface ID3D11Device;
//interface ID3D11DeviceContext3;

namespace Gltf {

// Creates a Pbr Model from tinygltf model with the specified root transform.
template <class Gfx>
Shared<Pbr::ModelT<Gfx>>
FromGltfObject(
    const Pbr::ResourcesT<Gfx>& pbr_res,
    const tinygltf::Model& gltf_model,
    const mat4& root_transform);

// Creates a Pbr Model from tinygltf model.
template <class Gfx>
inline Shared<Pbr::ModelT<Gfx>>
FromGltfObject(
    const Pbr::ResourcesT<Gfx>& pbr_res,
    const tinygltf::Model& gltf_model)
{
    return FromGltfObject(pbr_res, gltf_model, identity<mat4>());
}

// Creates a Pbr Model from glTF 2.0 GLB file content with the specified root transform.
template <class Gfx>
Shared<Pbr::ModelT<Gfx>>
FromGltfBinary(
    const Pbr::ResourcesT<Gfx>& pbr_res,
    const byte* buffer,
    uint32 buffer_bytes,
    const mat4& root_transform);

// Creates a Pbr Model from glTF 2.0 GLB file content.
template <class Gfx>
inline Shared<Pbr::ModelT<Gfx>>
FromGltfBinary(
    const Pbr::ResourcesT<Gfx>& pbr_res,
    const byte* buffer,
    uint32 buffer_bytes)
{
    return FromGltfBinary(pbr_res, buffer, buffer_bytes, identity<mat4>());
}

}


NAMESPACE_PARALLEL_END

