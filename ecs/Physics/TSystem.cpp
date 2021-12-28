#include "Physics.h"

NAMESPACE_ECS_BEGIN


template <class Fys>
void SystemT<Fys>::NearCallback(void*, NativeGeom& o1, NativeGeom& o2) {
	
	// only collide things with the ground
	/*int g1 = (o1 == ground.geom || o1 == ground_box.geom);
	int g2 = (o2 == ground.geom || o2 == ground_box.geom);
	if (!(g1 ^ g2)) return;*/

	const int N = 10;
	NativeContact contact[N];
	int n = Fys::Collide(o1, o2, N, &contact[0], sizeof(NativeContact));
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			Fys::AttachContact(
				world,
				contactgroup,
				contact[i],
				0.1f, 0.1f,
				0.5f, 0.3f);
		}
	}
}

template <class Fys>
void SystemT<Fys>::AddEngineSystem() {
	GetActiveEngine().Add<FysSystem>();
}


FYS_EXCPLICIT_INITIALIZE_CLASS(SystemT)

NAMESPACE_ECS_END
