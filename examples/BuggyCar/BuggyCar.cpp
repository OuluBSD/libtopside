#include "BuggyCar.h"

NAMESPACE_TOPSIDE_BEGIN


void BuggyWheel::OnAttach() {
	OdeObject::OnAttach();
	
	dQFromAxisAndAngle(orient, 1, 0, 0, M_PI*0.5);	// Set orientation from axis (1i+0j+0k) and it's (angle 90 degrees)
	dMassSetSphere(&mass, 1, radius);				// Set mass function for physics body as sphere
	dMassAdjust(&mass, wmass);						// Set mass for the mass function
	geom = dCreateSphere(0, radius);				// Set 3D geometry for the object as sphere
	
	ModelBuilder mb;
	mb	.AddCylinder(vec3(0, 0, 0), radius, 0.02)
		.SetMaterial(DefaultMaterial());
	model = mb;
	
	model_geom = rotate(identity<mat4>(), M_PI_2, vec3(0,0,1));
	
	AttachContent();
}


void BuggyCarStartup() {
	Machine& mach = GetMachine();
	mach.Add<PhysicsSystem>();
	
	EntityStore& ents = *mach.Get<EntityStore>();
	ents.Create<StaticGroundPlanePrefab>();
	ents.Create<BuggyCarPrefab>();
}


NAMESPACE_TOPSIDE_END


RENDER_APP_(Topside::DefaultRenderApp)
APP_STARTUP_(Topside::BuggyCarStartup);

NAMESPACE_UPP
INITBLOCK(AppFlags) {
	using namespace Topside;
	AppFlags& f = GetAppFlags();
	if (1)
		f.gfx = AppFlags::GFX_OPENGL;
	else
		f.gfx = AppFlags::GFX_SW;
}
END_UPP_NAMESPACE