#ifndef _Geometry_Geometry_h_
#define _Geometry_Geometry_h_


#define flagASSIMP

#ifdef flagASSIMP
	#ifdef flagBUILTIN_ASSIMP
		#include <plugin/assimp/Importer.hpp>
		#include <plugin/assimp/scene.h>
		#include <plugin/assimp/postprocess.h>
	#else
		#include <assimp/Importer.hpp>
		#include <assimp/scene.h>
		#include <assimp/postprocess.h>
	#endif
#endif

#include <Oulu/Oulu.h>

#undef rad2

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
