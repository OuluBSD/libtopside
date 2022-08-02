#ifndef _Edit3D_Editor_h_
#define _Edit3D_Editor_h_

#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_header.h>


NAMESPACE_TOPSIDE_BEGIN


struct EditConfiguration {
	Color background_clr;
	
	
	EditConfiguration();
	
};

struct Edit3D : public TopWindow {
	Splitter metasplit, hsplit, vsplit;
	TreeCtrl tree;
	ArrayCtrl props;
	GridCtrl grid;
	TimelineCtrl time;
	MenuBar menu;
	ToolBar tool;
	EditRenderer rends[4];
	EditConfiguration conf;
	
	int tree_cameras = -1;
	int tree_octrees = -1;
	int tree_pointclouds = -1;
	
	GeomProjectFile prj;
	GeomWorldState state;
	
public:
	typedef Edit3D CLASSNAME;
	Edit3D();
	
	void Data();
	void TreeSelect();
	void Exit();
	void RefreshData();
	void Stop();
	void Pause();
	void Play();
	void RefrehRenderers();
	void Toolbar(Bar& bar);
	
	void LoadTestProject(int test_i);
	void LoadWmrStereoPointcloud(String directory);
	
};


NAMESPACE_TOPSIDE_END

#endif
