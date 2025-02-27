#pragma once


NAMESPACE_ECS_BEGIN


namespace Pbr {
struct Model;
}


#if 0
// These are a few commonly used components
struct Transform : Component<Transform>
{
	COPY_PANIC(Transform)
	
    winrt::Windows::Foundation::Numerics::float3 position = winrt::Windows::Foundation::Numerics::float3::zero();
    winrt::Windows::Foundation::Numerics::float3 scale = winrt::Windows::Foundation::Numerics::float3::one();
    winrt::Windows::Foundation::Numerics::quaternion orientation = winrt::Windows::Foundation::Numerics::quaternion::identity();

    void SetFromMatrix(const winrt::Windows::Foundation::Numerics::float4x4& matrix)
    {
        fail_fast_if(!decompose(matrix, &scale, &orientation, &position));
    }

    winrt::Windows::Foundation::Numerics::float4x4 GetMatrix() const
    {
        using namespace winrt::Windows::Foundation::Numerics;

        return make_float4x4_scale(scale) * make_float4x4_from_quaternion(orientation) * make_float4x4_translation(position);
    }
};

struct RigidBody : Component<RigidBody>
{
	COPY_PANIC(RigidBody)
	
    winrt::Windows::Foundation::Numerics::float3 velocity = winrt::Windows::Foundation::Numerics::float3::zero();
    winrt::Windows::Foundation::Numerics::float3 acceleration = winrt::Windows::Foundation::Numerics::float3::zero();
    winrt::Windows::Foundation::Numerics::float3 angularVelocity = winrt::Windows::Foundation::Numerics::float3::zero();
    winrt::Windows::Foundation::Numerics::float3 angularAcceleration = winrt::Windows::Foundation::Numerics::float3::zero();

    float dampingFactor = 0.999f;
};
#endif

struct PbrRenderable : Component<PbrRenderable>
{
	COPY_PANIC(PbrRenderable)
	
    void ResetModel(std::string name, std::optional<winrt::Windows::Foundation::Numerics::float4x4> offset = std::nullopt)
    {
        ModelName = std::move(name);
        Offset = std::move(offset);
        Model = nullptr;
    }

    std::string ModelName;
    std::shared_ptr<Pbr::Model> Model = nullptr;
    std::optional<DirectX::XMVECTORF32> Color;
    std::optional<winrt::Windows::Foundation::Numerics::float4x4> Offset;
    std::optional<float> AlphaMultiplier;
};

typedef Ref<PbrRenderable> PbrRenderableRef;


/*struct TextRenderable : Component<TextRenderable>
{
	COPY_PANIC(TextRenderable)
	
    std::wstring Text = L"";
    float FontSize = 60.0f;
};*/



NAMESPACE_ECS_END

