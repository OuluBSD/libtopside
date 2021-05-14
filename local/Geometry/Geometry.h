#ifndef _Geometry_Geometry_h_
#define _Geometry_Geometry_h_


#define flagASSIMP

#ifdef flagASSIMP
	#if defined flagBUILTIN_ASSIMP || (defined flagMSC && defined flagWIN32)
		#include <ports/assimp/Importer.hpp>
		#include <ports/assimp/scene.h>
		#include <ports/assimp/postprocess.h>
	#else
		#include <ports/assimp/Importer.hpp>
		#include <ports/assimp/scene.h>
		#include <ports/assimp/postprocess.h>
	#endif
#endif

#include <Oulu/Oulu.h>

#undef rad2
#undef far
#undef near

#include "Common.h"
#include "Matrix.h"
#include "Util.h"
#include "GeomCommon.h"
#include "Geom2D.h"
//#include "Transform.h"
#include "Quadtree.h"
#include "Octree.h"
#include "GeomTypes.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "Draw.h"


NAMESPACE_UPP_BEGIN

NTL_MOVEABLE(Oulu::Circle);
NTL_MOVEABLE(Oulu::Rectangle);
NTL_MOVEABLE(Oulu::OrientedRectangle);

NAMESPACE_UPP_END


#endif
