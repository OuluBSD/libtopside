#pragma once

#ifdef flagVR

NAMESPACE_TOPSIDE_BEGIN


class PaintStrokeComponent :
	public Component<PaintStrokeComponent> {
	VIS_COMP_0_0
	
public:
	COPY_PANIC(PaintStrokeComponent)
	void Visit(RuntimeVisitor& vis) override {}
	
	Vector<Square> squares;
	bool stroke_changed = true;
	
	void AddPoint(const mat4& trans_mtx, float width);
	Pbr::PrimitiveBuilder GetPrimitiveData();
	
};


class PaintStrokeSystem :
	public System<PaintStrokeSystem> {
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	SYS_CTOR(PaintStrokeSystem);
	~PaintStrokeSystem() = default;
	
	void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}
	
protected:
	void Update(double) override;
	
private:
	Shared<Pbr::Resources> pbr_res;
};


NAMESPACE_TOPSIDE_END

#endif
