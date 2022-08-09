#ifndef _Edit3D_VideoImportCtrl_h_
#define _Edit3D_VideoImportCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


struct VideoImportCtrl;

struct VideoImportImageCtrl : Ctrl {
	VideoImportCtrl* owner = 0;
	
	
	VideoImportImageCtrl();
	void Paint(Draw& w) override;
	Rect DrawStereoImages(Draw& d);
	
};

struct KeypointImageCtrl : VideoImportImageCtrl {
	Color clr;
	
	KeypointImageCtrl();
	void Paint(Draw& w) override;
	
};

struct TriangleImageCtrl : VideoImportImageCtrl {
	Color clr;
	
	
	TriangleImageCtrl();
	void Paint(Draw& w) override;
	
};

struct VideoImportCtrl : ParentCtrl {
	enum {
		VIEW_KEYPOINTS,
		VIEW_TRIANGLES,
		VIEW_WORLD,
	};
	
	Edit3D* owner;
	Splitter hsplit;
	ArrayCtrl list;
	TabCtrl tabs;
	
	// keypoint view
	struct KpView : ParentCtrl {
		Splitter hsplit, vsplit;
		KeypointImageCtrl st;
		EditRenderer rends[2];
		
	};
	struct TriView : ParentCtrl {
		Splitter hsplit, vsplit;
		TriangleImageCtrl st;
		EditRenderer rends[2];
		
	};
	struct WorldView : ParentCtrl {
		GridCtrl grid;
		EditRenderer rends[4];
		
	};
	KpView kp;
	TriView tri;
	WorldView w;
	
	typedef VideoImportCtrl CLASSNAME;
	VideoImportCtrl(Edit3D* e);
	
	void Update(double dt);
	void Data();
	void DataList();
	void OnTab();
	void RefreshRenderers();
	
};


NAMESPACE_TOPSIDE_END

#endif
