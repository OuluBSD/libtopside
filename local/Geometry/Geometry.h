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

#include <Local/Local.h>

#ifdef flagGUI
	#include <LocalCtrl/LocalCtrl.h>
#endif

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

NTL_MOVEABLE(TS::Circle);
NTL_MOVEABLE(TS::Rectangle);
NTL_MOVEABLE(TS::OrientedRectangle);

NAMESPACE_UPP_END


#endif
