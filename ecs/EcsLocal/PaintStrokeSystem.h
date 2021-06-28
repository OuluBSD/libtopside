#pragma once

#ifdef flagVR

NAMESPACE_ECS_BEGIN


class PaintStrokeComponent :
	public Component<PaintStrokeComponent> {
	
public:
	RTTI_COMP0(PaintStrokeComponent)
	COPY_PANIC(PaintStrokeComponent)
	COMP_DEF_VISIT
	COMP_DEF_MAKE_ACTION
	
	Vector<Square> squares;
	bool stroke_changed = true;
	
	void AddPoint(const mat4& trans_mtx, float width);
	Pbr::PrimitiveBuilder GetPrimitiveData();
	
};


class PaintStrokeSystem :
	public System<PaintStrokeSystem> {
public:
	SYS_RTTI(PaintStrokeSystem)
	SYS_CTOR(PaintStrokeSystem);
	SYS_DEF_VISIT
	~PaintStrokeSystem() = default;
	
	void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}
	
protected:
	void Update(double) override;
	
private:
	Shared<Pbr::Resources> pbr_res;
};


NAMESPACE_ECS_END

#endif
