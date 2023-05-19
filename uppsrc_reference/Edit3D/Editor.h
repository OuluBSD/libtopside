#ifndef _Edit3D_Editor_h_
#define _Edit3D_Editor_h_

#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_header.h>


NAMESPACE_TOPSIDE_BEGIN


struct Edit3D;
class EditClientService;


struct EditConfiguration {
	Color background_clr;
	float mouse_move_sensitivity = 0.01;
	
	EditConfiguration();
	
};

struct GeomProjectCtrl : Ctrl {
	Edit3D* e;
	
	Splitter metasplit, hsplit, vsplit;
	TreeCtrl tree;
	ArrayCtrl props;
	GridCtrl grid;
	TimelineCtrl time;
	EditRenderer rends[4];
	
	int tree_scenes = -1;
	
	
	typedef GeomProjectCtrl CLASSNAME;
	GeomProjectCtrl(Edit3D* e);
	void Update(double dt);
	void Data();
	void TimelineData();
	void TreeSelect();
	void OnCursor(int kp_i);
	void TreeDirectory(int id, GeomDirectory& dir);
	
};

struct Edit3D : TopWindow {
	typedef enum {
		VIEW_NONE,
		VIEW_GEOMPROJECT,
		VIEW_VIDEOIMPORT,
	} ViewType;
	
	ViewType view = VIEW_NONE;
	
	GeomProjectCtrl v0;
	VideoImportCtrl v1;
	MenuBar menu;
	ToolBar tool;
	
	EditConfiguration conf;
	
	
	GeomProject prj;
	GeomWorldState state;
	GeomAnim anim;
	//GeomVideo video;
	GeomStagedVideo video;
	TimeCallback tc;
	TimeStop ts;
	
	EditClientService* svc = 0;
	
public:
	typedef Edit3D CLASSNAME;
	Edit3D();
	
	void LoadRemote(EditClientService* svc);
	void SetView(ViewType view);
	void Update();
	void Data();
	void Exit();
	void RefreshData();
	void Stop();
	void Pause();
	void Play();
	void RefrehRenderers();
	void RefrehToolbar();
	void OnSceneEnd();
	void Toolbar(Bar& bar);
	
	void LoadTestProject(int test_i);
	void LoadWmrStereoPointcloud(String directory);
	
	GeomScene& GetActiveScene();
	
};


NAMESPACE_TOPSIDE_END

#endif
