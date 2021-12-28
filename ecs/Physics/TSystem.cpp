#include "Physics.h"

NAMESPACE_ECS_BEGIN


template <class Fys>
void SystemT<Fys>::NearCallback(void*, NativeGeom& o1, NativeGeom& o2) {
	
	// only collide things with the ground
	/*int g1 = (o1 == ground.geom || o1 == ground_box.geom);
	int g2 = (o2 == ground.geom || o2 == ground_box.geom);
	if (!(g1 ^ g2)) return;*/

	const int N = 10;
	dContact contact[N];
	int n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
			contact[i].surface.mu = dInfinity;
			contact[i].surface.slip1 = 0.1;
			contact[i].surface.slip2 = 0.1;
			contact[i].surface.soft_erp = 0.5;
			contact[i].surface.soft_cfm = 0.3;
			dJointID c = dJointCreateContact(world,contactgroup,&contact[i]);
			dJointAttach(c,
						 dGeomGetBody(contact[i].geom.g1),
						 dGeomGetBody(contact[i].geom.g2));
		}
	}
}

template <class Fys>
void SystemT<Fys>::AddEngineSystem() {
	GetActiveEngine().Add<FysSystem>();
}


FYS_EXCPLICIT_INITIALIZE_CLASS(SystemT)

NAMESPACE_ECS_END
