#ifndef _BuggyCar_BuggyCar_h_
#define _BuggyCar_BuggyCar_h_

#include <EcsComplete/EcsComplete.h>
#include <Physics/Physics.h>


#define SOFTGL 0



NAMESPACE_TOPSIDE_BEGIN


#ifdef flagODE
using DefSpace = OdeSpace;
using DefNode = OdeNode;
using DefJoint = OdeJoint;
using DefObject = OdeObject;
using DefSystem = Ecs::OdeSystem;
using DefStaticGroundPlane = Ecs::StaticGroundPlane<OdeFys>;
using DefStaticGroundPlanePrefab = Ecs::StaticGroundPlanePrefab<OdeFys>;
#else
using DefSpace = TosSpace;
using DefNode = TosNode;
using DefJoint = TosJoint;
using DefObject = TosObject;
using DefSystem = Ecs::TosSystem;
using DefStaticGroundPlane = Ecs::StaticGroundPlane<TosFys>;
using DefStaticGroundPlanePrefab = Ecs::StaticGroundPlanePrefab<TosFys>;
#endif


class BuggyCarVertexShader : public SoftShaderBase {
	
public:
	void Process(SdlCpuVertexShaderArgs& args) override;
	
};

class BuggyCarFragmentShader : public SoftShaderBase {
	
public:
	void Process(SdlCpuFragmentShaderArgs& args) override;
	
};




struct BuggyWheel : public DefObject {
	double radius = 0.18;	// wheel radius
	double wmass  = 0.2;	// wheel mass
	
	
	virtual void OnAttach();
	
	
};

struct BuggyChassis : public DefObject {
	float startz = 0.5f;	// starting height of chassis
	float length = 1.7f;	// chassis length
	float width  = 1.2f;	// chassis width
	float height = 0.1f;	// chassis height
	float cmass   = 0.1f;	// chassis mass
	
	
	void OnAttach() override {
		DefObject::OnAttach();
		
		TODO
		#if 0
		dBodySetPosition(body, 0, startz, 0);			// Set position for physics body
		dMassSetBox(&mass, 1, width, height, length);	// Set mass function for physics body as box
		dMassAdjust(&mass, cmass);						// Set mass for the mass function
		geom = dCreateBox(0, width, height, length);	// Set 3D geometry for the object as box
		
		ModelBuilder mb;
		mb	.AddBox(vec3(-width/2, -height/2, -length/2), vec3(width, height, length))
			.SetMaterial(DefaultMaterial());
		loader = mb;
		
		//model_geom = rotate<float>(identity<mat4>(), M_PI_2, vec3(0,0,1));
		
		AttachContent();
		#endif
	}
	
	String ToString() const override {return "BuggyChassis";}
	
};


NAMESPACE_TOPSIDE_END



NAMESPACE_ECS_BEGIN


struct BuggyCar :
	public DefSpace,
	public Component<BuggyCar>
{
	BuggyChassis chassis;
	Array<BuggyWheel> wheels;
	Array<DefJoint> joints;
	
	dReal speed=0, steer=0;	// user commands
	
	using Parent = Entity;
	
public:
	RTTI_DECL2(BuggyCar, DefSpace, Component<BuggyCar>)
	typedef BuggyCar CLASSNAME;
	BuggyCar() {}
	
	void operator = (const BuggyCar& c) {Panic("Not implemented");}
	COMP_DEF_VISIT
	
	template <class T>
	void LoadModel(T& state) {
		chassis.LoadModel(state);
		for (auto& w : wheels) w.LoadModel(state);
	}
	
	/*void Refresh() {
		chassis.Refresh();
		for (auto& w : wheels) w.Refresh();
	}*/
	
	void OnAttach() override {
		DefSpace::OnAttach();
		
		Attach(chassis);
		for(int i = 0; i < 3; i++) {
			Attach(wheels.Add());
			Attach(joints.Add());
		}
		
		wheels[0].SetPosition(0, chassis.startz - chassis.height*0.5, +0.5*chassis.length);
		wheels[1].SetPosition(+chassis.width*0.5, chassis.startz - chassis.height*0.5, -0.5*chassis.length);
		wheels[2].SetPosition(-chassis.width*0.5, chassis.startz - chassis.height*0.5, -0.5*chassis.length);
		
		
		for(int i = 0; i < joints.GetCount(); i++) {
			DefJoint& joint = joints[i];
			DefObject& wheel = wheels[i];
			joint.AttachHinge(chassis, wheel);
			joint.SetHingeSuspension(0.4, 0.8);
			joint.SetHingeLock();
		}
	}
	
	void Step() {
		DefJoint& motor_joint = joints[0];
		
		// motor
		motor_joint.SetVelocity2(-speed);
		motor_joint.SetMaxForce2(0.1);

		// steering
		double v = steer - motor_joint.GetAngle();
		if (v > 0.1) v = 0.1;
		if (v < -0.1) v = -0.1;
		v *= 10.0;
		motor_joint.SetVelocity(v);
		motor_joint.SetMaxForce(0.2);
		motor_joint.SetHingeRange(-0.75, +0.75);
		motor_joint.SetFudgeFactor(1.0);
		
	}
	
	void Refresh() override {
		speed = 1.0;
		steer = 1.0;
		Step();
		chassis.Refresh();
		for (auto& w : wheels) w.Refresh();
	}
	
	/*virtual bool Key(dword key, int count) {
		switch (key) {
			case SDLK_a:
				speed += 0.3;
				return true;
			case SDLK_z:
				speed -= 0.3;
				return true;
			case SDLK_COMMA:
				steer -= 0.05;
				return true;
			case SDLK_PERIOD:
				steer += 0.05;
				return true;
			case SDLK_SPACE:
				speed = 0;
				steer = 0;
				return true;
		}
		return false;
	}*/
	
	Callback GetRefreshCallback() {return THISBACK(Refresh);}
};


struct BuggyCarPrefab : EntityPrefab<Transform, Renderable, BuggyCar>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		components.Get<TransformRef>()->position[1] = 3.0;
		components.Get<RenderableRef>()->cb.Add(components.Get<Ref<BuggyCar>>()->GetRefreshCallback());
		
		Ref<DefSystem> w = e.GetEngine().Get<DefSystem>();
		w->Attach(*components.Get<Ref<BuggyCar>>());
		
        return components;
    }
};


struct BuggyCarApp :
	public Component<BuggyCarApp>,
	public BinderIfaceVideo
{
	RTTI_DECL2(BuggyCarApp, ComponentT, BinderIfaceVideo)
	
	ModelLoader loader;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	Ref<ChaseCam> chaser;
	Ref<ModelComponent> sky;
	Ref<DefStaticGroundPlane> gnd;
	Ref<BuggyCar> car;
	
	BuggyCarApp();
	void operator=(const BuggyCarApp& t) {Panic("Can't copy BuggyCarApp");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	void Render(Draw& draw) override;
	
	void DrawObj(GfxStateDraw& fb, bool use_texture);
	
	template <class T> void BuggyCarStartup(T& state);
	template <class T> void BuggyCarUpdate(T& state);
	
};



NAMESPACE_ECS_END




#endif
