#pragma once

#if 1

NAMESPACE_ECS_BEGIN


class PaintStrokeComponent :
	public Component<PaintStrokeComponent> {
	
public:
	RTTI_COMP0(PaintStrokeComponent)
	COPY_PANIC(PaintStrokeComponent)
	COMP_DEF_VISIT
	
	
	Vector<Square> squares;
	bool stroke_changed = true;
	
	
	void Initialize() override;
	void Uninitialize() override;
	void AddPoint(const mat4& trans_mtx, float width);
	//Pbr::PrimitiveBuilder GetPrimitiveData();
	
};


class PaintStrokeSystemBase :
	public System<PaintStrokeSystemBase>
{
public:
	SYS_RTTI(PaintStrokeSystemBase)
	ECS_SYS_CTOR(PaintStrokeSystemBase);
	SYS_DEF_VISIT
	
	~PaintStrokeSystemBase() = default;
	
	//void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}
	
	void Attach(PaintStrokeComponent* comp);
	void Detach(PaintStrokeComponent* comp);
	
protected:
	void Update(double) override;
	bool Initialize() override;
    // void Uninitialize() override;
	
private:
	Vector<PaintStrokeComponent*> comps;
	
    //Pbr::Resources* pbr_res = 0;
	
};


NAMESPACE_ECS_END

#endif
