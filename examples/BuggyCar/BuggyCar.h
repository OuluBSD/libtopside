#ifndef _BuggyCar_BuggyCar_h_
#define _BuggyCar_BuggyCar_h_

#include <EcsMinimal/EcsMinimal.h>


#define SOFTGL 0



NAMESPACE_TOPSIDE_BEGIN
using namespace Parallel;


#ifdef flagODE
using DefFys = OdeFys;
using DefSpace = SpaceT<OdeFys>;
using DefNode = NodeT<OdeFys>;
using DefJoint = JointT<OdeFys>;
using DefObject = ObjectT<OdeFys>;
using DefSystem = SystemT<OdeFys>;
using DefStaticGroundPlane = Ecs::StaticGroundPlane<OdeFys>;
using DefStaticGroundPlanePrefab = Ecs::StaticGroundPlanePrefab<OdeFys>;
#else
using DefFys = TosFys;
using DefSpace = SpaceT<TosFys>;
using DefNode = NodeT<TosFys>;
using DefJoint = JointT<TosFys>;
using DefObject = ObjectT<TosFys>;
using DefSystem = SystemT<TosFys>;
using DefStaticGroundPlane = Ecs::StaticGroundPlane<TosFys>;
using DefStaticGroundPlanePrefab = Ecs::StaticGroundPlanePrefab<TosFys>;
#endif


class BuggyCarVertexShader : public SoftShaderBaseT<SdlSwGfx> {
	
public:
	void Process(VertexShaderArgsT<SdlSwGfx>& args) override;
	
};

class BuggyCarFragmentShader : public SoftShaderBaseT<SdlSwGfx> {
	
public:
	void Process(FragmentShaderArgsT<SdlSwGfx>& args) override;
	
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
		
		// Set position for physics body
		DefFys::SetBodyPosition(body, 0, startz, 0);
		
		// Set mass function for physics body as box
		DefFys::SetMassFunctionBox(mass, width, height, length);
		
		// Set mass for the mass function
		DefFys::SetMass(mass, cmass);
		
		// Set 3D geometry for the object as box
		DefFys::SetGeomModelBox(geom, width, height, length);
		
		ModelBuilder mb;
		mb	.AddBox(vec3(-width/2, -height/2, -length/2), vec3(width, height, length))
			.SetMaterial(DefaultMaterial());
		loader = mb;
		
		//model_geom = rotate<float>(identity<mat4>(), M_PI_2, vec3(0,0,1));
		
		AttachContent();
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
	
	float speed=0, steer=0;	// user commands
	
	using Parent = Entity;
	
public:
	RTTI_DECL2(BuggyCar, DefSpace, Component<BuggyCar>)
	typedef BuggyCar CLASSNAME;
	BuggyCar() {}
	
	void operator = (const BuggyCar& c) {Panic("Not implemented");}
	COMP_DEF_VISIT_(vis % chassis; vis | wheels | joints;)
	
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
		
		//Ref<DefSystem> w = e.GetEngine().Get<DefSystem>();
		//w->Attach(*components.Get<Ref<BuggyCar>>());
		
		Ref<DefSystem> w = Parallel::GetActiveMachine().Get<DefSystem>();
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
	
	COMP_DEF_VISIT_(vis % loader; vis & chaser & sky & gnd & car;)
	
	void operator=(const BuggyCarApp& t) {Panic("Can't copy BuggyCarApp");}
	void Initialize() override;
	bool Render(Draw& draw) override;
	
	void DrawObj(GfxStateDraw& fb, bool use_texture);
	
	template <class T> void BuggyCarStartup(T& state);
	template <class T> void BuggyCarUpdate(T& state);
	
};



NAMESPACE_ECS_END




#endif
