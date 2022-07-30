#ifndef _Edit3D_Edit3D_h_
#define _Edit3D_Edit3D_h_

#include <CtrlLib/CtrlLib.h>
#include <LocalCtrl/LocalCtrl.h>
#include <Geometry/Geometry.h>
#include <ComputerVision/ComputerVision.h>
using namespace Upp;
using namespace TS;


struct GeomProjectFile {
	Index<String> dictionary;
	ArrayMap<int, OctreePointModel> octrees;
	ArrayMap<int, Model> models;
	
	
};

class Edit3D : public TopWindow {
	Splitter metasplit, hsplit, vsplit;
	TreeCtrl content;
	ArrayCtrl props;
	GridCtrl grid;
	TimelineCtrl time;
	MenuBar menu;
	
	GeomProjectFile prj;
	
	
	
public:
	typedef Edit3D CLASSNAME;
	Edit3D();
	
	void Data();
	void Exit();
	
	
	void LoadWmrStereoPointcloud(String directory);
	
};


#endif
