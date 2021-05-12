#pragma once


NAMESPACE_OULU_BEGIN


struct PaintStrokeComponent :
	public Component<PaintStrokeComponent>
{
    Vector<Rect> squares;
    bool stroke_changed = true;

    void AddPoint(const mat4& trans_mtx, float width);
    Pbr::PrimitiveBuilder GetPrimitiveData();
    
};


class PaintStrokeSystem :
	public System<PaintStrokeSystem>
{
public:
    PaintStrokeSystem(Machine& core, Shared<Pbr::Resources> pbr_res);
    ~PaintStrokeSystem() = default;

protected:
    void Update(double) override;

private:
    Shared<Pbr::Resources> pbr_res;
};


NAMESPACE_OULU_END
