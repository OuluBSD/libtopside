#ifndef _BuggyCar_BuggyCar_h_
#define _BuggyCar_BuggyCar_h_

#include <Complete/Complete.h>
#include <Physics/Physics.h>


NAMESPACE_OULU_BEGIN



struct BuggyWheel : public OdeObject {
	double radius = 0.18;	// wheel radius
	double wmass  = 0.2;	// wheel mass
	
	
	virtual void OnAttach();
	
	
};

struct BuggyChassis : public OdeObject {
	float startz = 0.5f;	// starting height of chassis
	float length = 1.7f;	// chassis length
	float width  = 1.2f;	// chassis width
	float height = 0.1f;	// chassis height
	float cmass   = 0.1f;	// chassis mass
	
	
	virtual void OnAttach() {
		OdeObject::OnAttach();
		
		dBodySetPosition(body, 0, startz, 0);			// Set position for physics body
		dMassSetBox(&mass, 1, width, height, length);	// Set mass function for physics body as box
		dMassAdjust(&mass, cmass);						// Set mass for the mass function
		geom = dCreateBox(0, width, height, length);	// Set 3D geometry for the object as box
		
		ModelBuilder mb;
		mb	.AddBox(vec3(-width/2, -height/2, -length/2), vec3(width, height, length))
			.SetMaterial(DefaultMaterial());
		model = mb;
		
		//model_geom = rotate<float>(identity<mat4>(), M_PI_2, vec3(0,0,1));
		
		AttachContent();
	}
	
	
};

struct BuggyCar : public OdeSpace, public Component<BuggyCar> {
	BuggyChassis chassis;
	Array<BuggyWheel> wheels;
	Array<OdeJoint> joints;
	
	dReal speed=0, steer=0;	// user commands
	
	
	typedef BuggyCar CLASSNAME;
	BuggyCar() {}
	
	void operator = (const BuggyCar& c) {Panic("Not implemented");}
	
	virtual void OnAttach() {
		OdeSpace::OnAttach();
		
		Attach(chassis);
		for(int i = 0; i < 3; i++) {
			Attach(wheels.Add());
			Attach(joints.Add());
		}
		
		wheels[0].SetPosition(0, chassis.startz - chassis.height*0.5, +0.5*chassis.length);
		wheels[1].SetPosition(+chassis.width*0.5, chassis.startz - chassis.height*0.5, -0.5*chassis.length);
		wheels[2].SetPosition(-chassis.width*0.5, chassis.startz - chassis.height*0.5, -0.5*chassis.length);
		
		
		for(int i = 0; i < joints.GetCount(); i++) {
			OdeJoint& joint = joints[i];
			OdeObject& wheel = wheels[i];
			joint.AttachHinge(chassis, wheel);
			joint.SetHingeSuspension(0.4, 0.8);
			joint.SetHingeLock();
		}
	}
	
	void Step() {
		OdeJoint& motor_joint = joints[0];
		
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
	
	void Paint(Shader& d) {
		speed = 1.0;
		steer = 1.0;
		Step();
		chassis.Paint(d);
		for (auto& w : wheels) w.Paint(d);
	}
	
	virtual bool Key(dword key, int count) {
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
	}
	
	Callback1<Shader&> GetPaintCallback() {return THISBACK(Paint);}
};


struct BuggyCarPrefab : EntityPrefab<Transform, Renderable, BuggyCar>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		
		components.Get<Transform>().position[1] = 3.0;
		
		components.Get<Renderable>()->cb << components.Get<BuggyCar>()->GetPaintCallback();
		
		Shared<PhysicsSystem> w = store.GetMachine().Get<PhysicsSystem>();
		PhysicsSystem& ow = dynamic_cast<PhysicsSystem&>(*w);
		ow.Attach(*components.Get<BuggyCar>());
		
        return components;
    }
};


NAMESPACE_OULU_END

#endif
