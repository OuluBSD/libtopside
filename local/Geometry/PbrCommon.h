#if 0
//
// Shared data types and functions used throughout the Pbr rendering library.
//

#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr
{
namespace Internal
{
    void ThrowIfFailed(dword hr);
}

namespace ShaderSlots {

enum VSResourceViews
{
    Transforms = 0,
};

enum PSMaterial // For both samplers and textures.
{
    BaseColor = 0,
    MetallicRoughness,
    Normal,
    Occlusion,
    Emissive,
    
    LastMaterialSlot = Emissive
};

enum Pbr // For both samplers and textures.
{
    Brdf = LastMaterialSlot + 1
};

enum EnvironmentMap // For both samplers and textures.
{
    SpecularTexture = Brdf + 1,
    DiffuseTexture = SpecularTexture + 1,
    env_map_sampler = Brdf + 1
};

enum ConstantBuffers
{
    Scene,          // Used by VS and PS
    Material,       // PS only
};

}


struct ShaderResources {};
struct Texture {
	
	void Set(RGBA clr, int w, int h, int d, int channels) {}
	void Set(const byte* img, int w, int h, int d, int channels) {}
	void SetSolidColorTexture(const vec4& color);
	
};
struct SamplerState {
	
};
struct BlendState {};
struct DataBuffer {
	void Clear() {}
};
struct GfxContext {};
struct SpatialSourceState {};
struct InputLayout {};
struct VertexShader {};
struct GeometryShader {};
struct PixelShader {};


struct Mesh;
struct Resources;
struct Model;


using NodeIndex = uint16; // This type must align with the type used in the Pbr shaders.

constexpr Pbr::NodeIndex root_node_idx = 0;

// Vertex structure used by the PBR shaders.
struct Vertex : Moveable<Vertex>
{
    vec3			position;
    vec3			normal;
    vec4			tangent;
    vec2			tex_coord;
    NodeIndex		mdl_transform_idx; // Index into the node transforms

    //static const D3D11_INPUT_ELEMENT_DESC vtx_desc[5];
};

struct MeshBuilder
{
    static void CreateSphere(Mesh& prim, float diameter, uint32 tessellation, Pbr::NodeIndex transform_idx = Pbr::root_node_idx);
    static void CreateCube(Mesh& prim, float side_length, Pbr::NodeIndex transform_idx = Pbr::root_node_idx);
};

/*namespace Texture
{
    ShaderResources& LoadImage(NativeDeviceRef device, const byte* file_data, uint32 file_size);
    ShaderResources& CreateFlatCubeTexture(NativeDeviceRef device, const vec4& color, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
    ShaderResources& CreateTexture(NativeDeviceRef device, const byte* rgba, uint32 size, int width, int height, DXGI_FORMAT format);
    SamplerState& CreateSampler(NativeDeviceRef device, D3D11_TEXTURE_ADDRESS_MODE addressMode = D3D11_TEXTURE_ADDRESS_CLAMP);
}*/

// Catch changes to a value of type T for lazy sync with DirectX.
template <typename T>
class TrackChanges
{
public:
    TrackChanges() { change_count = 0; }
    TrackChanges(TrackChanges<T>&& o) : value(std::move(o.value)) { change_count = 0;  }
    TrackChanges(const TrackChanges<T>& o) : value(o.Get()) { change_count = 0;  }

    TrackChanges<T>& operator=(TrackChanges<T>&& o)
    {
        ++change_count;
        value = std::move(o.value);
        return *this;
    }

    TrackChanges<T>& operator=(const TrackChanges<T>& o)
    {
        ++change_count;
        value = o.value;
        return *this;
    }

    template <typename Func>
    void Set(Func func)
    {
        ++change_count;
        func(value);
    }

    bool UpdateChangeCountBookmark(uint32* change_count_bookmark) const
    {
        uint32 new_value = *change_count_bookmark;
        uint32 prev = change_count.exchange(new_value);
        return prev != new_value;
    }

    const T& Get() const { return value; }

private:
    T value;
    mutable AtomicInt change_count;
};

}

NAMESPACE_TOPSIDE_END

#endif
