#pragma once


NAMESPACE_WIN_BEGIN
using namespace TS;

	
struct PaintStrokeComponent : Component<PaintStrokeComponent>
{
    struct Square
    {
        winrt::Windows::Foundation::Numerics::float3 TopLeft, TopRight, BottomLeft, BottomRight;
    };

    std::vector<Square> squares;
    bool strokeChanged{ true };

    void AddPoint(const winrt::Windows::Foundation::Numerics::float4x4& transformationMatrix, float width);
    Pbr::PrimitiveBuilder GetPrimitiveData();
    
    COPY_PANIC(PaintStrokeComponent)
    
};


// PaintStrokeSystem
// This System manages the PaintStrokeComponents and automatically generates the 3D mesh for each stroke
class PaintStrokeSystem : public System<PaintStrokeSystem>
{
public:
    PaintStrokeSystem(Engine& core, std::shared_ptr<Pbr::Resources> pbrResources);
    ~PaintStrokeSystem() = default;

protected:
    void Update(double) override;

private:
    std::shared_ptr<Pbr::Resources> m_pbrResources{ nullptr };
};


NAMESPACE_WIN_END
