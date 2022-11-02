#ifndef _SoftPhys_SoftPhys_h_
#define _SoftPhys_SoftPhys_h_

#include <Geometry/Geometry.h>

#define NAMESPACE_SOFTPHYS_BEGIN NAMESPACE_TOPSIDE_BEGIN namespace SoftPhys {
#define NAMESPACE_SOFTPHYS_END NAMESPACE_TOPSIDE_END }
#define SOFTPHYS SoftPhys
	
#if 1 // flagDEBUGSOFTPHYS
#define SOFTPHYS_RENDER 0

#define SOFTPHYS_RENDER_COMMON \
	void Refresh(Parallel::GfxDataState& s);

#else
#define SOFTPHYS_RENDER_COMMON
#endif

#define PHYS_EPSILON FLT_EPSILON
	
#if 1
// fast
#define EULER_INTEGRATION
#else
// more accurate
#define ACCURATE_EULER_INTEGRATION
#endif

//#define DYNAMIC_FRICTION
//#define LINEAR_ONLY

#define RIGIDBODY_TYPE_BASE		0
#define RIGIDBODY_TYPE_PARTICLE	1
#define RIGIDBODY_TYPE_SPHERE	2
#define RIGIDBODY_TYPE_BOX		3

#define GRAVITY_CONST vec3(0.0f, -9.82f, 0.0f)



#include "Common.h"
#include "Feedback.h"
#include "Joint.h"
#include "Mass.h"
#include "Body.h"
#include "JointGroup.h"
#include "Geometry.h"
#include "Contact.h"



#include "Geometry2D.h"
#include "Geometry3D.h"
#include "Rigidbody.h"
#include "Particle.h"
#include "Spring.h"
#include "Cloth.h"
#include "DistanceJoint.h"
#include "PhysicsSystem.h"
#include "RigidbodyVolume.h"
#include "QuadTree.h"
#include "Rigidbody.h"
#include "RigidbodyVolume.h"
#include "Scene.h"
#include "Spring.h"


#include "Threading.h"
#include "ThreadPool.h"
#include "World.h"
#include "Space.h"






NAMESPACE_TOPSIDE_BEGIN



NAMESPACE_TOPSIDE_END

#endif
