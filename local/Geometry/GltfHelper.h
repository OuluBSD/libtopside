#if 0
// GltfHelper provides additional glTF parsing functionality, built on top of tinygltf.
// This library has no rendering dependencies and can be used for any purpose, such as
// format transcoding or by a rendering engine.

#pragma once


namespace tinygltf {
class Node;
class Model;
struct Primitive;
struct Material;
struct Image;
struct Sampler;
}


NAMESPACE_TOPSIDE_BEGIN


namespace GltfHelper {

// Vertex data.
struct Vertex : Moveable<Vertex>
{
    vec3 position;
    vec3 normal;
    vec4 tangent;
    vec2 tex_coord;
    // Note: This implementation does not currently support glTF 2's Color0 and TexCoord1 attributes.
};

// A primitive is a collection of vertices and indices.
struct Primitive
{
    Vector<Vertex> vertices;
    Vector<uint32> indices;
};

// Metallic-roughness material definition.
struct Material
{
    struct Texture
    {
        const tinygltf::Image* image;
        const tinygltf::Sampler* sampler;
    };

    Texture base_color_texture;
    Texture metallic_roughness_texture;
    Texture emissive_texture;
    Texture normal_texture;
    Texture occlusion_texture;

    vec4 base_color_factor;
    float metallic_factor;
    float roughness_factor;
    vec3 emissive_factor;

    float normal_scale;
    float occlusion_strength;
};

// Reads the "transform" or "TRS" data for a Node as an XMMATRIX.
mat4 ReadNodeLocalTransform(const tinygltf::Node& gltf_node);

// Parses the primitive attributes and indices from the glTF accessors/bufferviews/buffers into a common simplified data structure, the Primitive.
Primitive ReadPrimitive(const tinygltf::Model& gltf_model, const tinygltf::Primitive& gltf_primitive);

// Parses the material values into a simplified data structure, the Material.
Material ReadMaterial(const tinygltf::Model& gltf_model, const tinygltf::Material& gltf_material);

// Converts the image to RGBA if necessary. Requires a temporary buffer only if it needs to be converted.
const byte* ReadImageAsRGBA(const tinygltf::Image& image, Vector<byte>* temp_buffer);

}


NAMESPACE_TOPSIDE_END

#endif
