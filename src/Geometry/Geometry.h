#ifndef _Geometry_Geometry_h_
#define _Geometry_Geometry_h_

#if (defined flagMSC && !defined flagUWP) || defined flagLINUX
	#define flagASSIMP
#endif

#ifdef flagASSIMP
	#if defined flagBUILTIN_ASSIMP || (defined flagMSC && defined flagWIN32 && !defined flagUWP) || flagLINUX
		#include <ports/assimp/Importer.hpp>
		#include <ports/assimp/scene.h>
		#include <ports/assimp/postprocess.h>
	#else
		#include <ports/assimp/Importer.hpp>
		#include <ports/assimp/scene.h>
		#include <ports/assimp/postprocess.h>
	#endif
#endif

#include <Local/Local.h>

/*#ifdef flagGUI
	#include <LocalCtrl/LocalCtrl.h>
#endif*/

#undef rad2
#undef far
#undef near

#ifdef flagLHS
// Left-handed coordinate system
	#define LHS		0
#elif defined flagRHS_PZ
// Right-handed coordinate system with positive z forward
// CCW angles (RHS) but +z forward.
// Very experiemental: dirty matrix, clean api, unnatural, mathematician's nightmare
	#define RHS_PZ	0
#else
// Right-handed coordinate system
	#define RHS		1
#endif

#if RHS || RHS_PZ
	#define IS_CW_ANGLE 0
#else
	#define IS_CW_ANGLE 1
#endif

#if RHS
	#define IS_NEGATIVE_Z 1
#else
	#define IS_NEGATIVE_Z 0
#endif


#include "Common.h"
#include "Matrix.h"
#include "Util.h"
#include "GeomCommon.h"
#include "Geom2D.h"
#include "GeomTypes.h"
#include "Geom3D.h"
#include "Quadtree.h"
#include "Octree.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "ModelPainter.h"
#include "ModelDraw.h"
#include "Draw.h"
#include "Frustum.h"
#include "Compare.h"
#include "Camera.h"
#include "Pointcloud.h"
#include "MeshTracker.h"
#include "Uncamera.h"
#include "Vr.h"


NAMESPACE_UPP_BEGIN

NTL_MOVEABLE(TS::Circle);
NTL_MOVEABLE(TS::Rectangle);
NTL_MOVEABLE(TS::OrientedRectangle);

NAMESPACE_UPP_END


#endif
