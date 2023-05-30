#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


GeomProjectCtrl::GeomProjectCtrl(Edit3D* e) {
	this->e = e;
	
	time.WhenCursor << THISBACK(OnCursor);
	tree.WhenAction << THISBACK(TreeSelect);
	
	hsplit.Horz().SetPos(2000) << metasplit << vsplit,
	metasplit.Vert() << tree << props;
	vsplit.Vert().SetPos(7500) << grid << time;
	
	grid.SetGridSize(2,2);
	for(int i = 0; i < 4; i++) {
		rends[i].owner = e;
		grid.Add(rends[i]);
	}
	rends[0].SetViewMode(VIEWMODE_YZ);
	rends[1].SetViewMode(VIEWMODE_XZ);
	rends[2].SetViewMode(VIEWMODE_XY);
	rends[3].SetViewMode(VIEWMODE_PERSPECTIVE);
	rends[0].SetCameraSource(CAMSRC_FOCUS);
	rends[1].SetCameraSource(CAMSRC_FOCUS);
	rends[2].SetCameraSource(CAMSRC_FOCUS);
	rends[3].SetCameraSource(CAMSRC_PROGRAM);
	
	
}

void GeomProjectCtrl::Update(double dt) {
	GeomAnim& anim = e->anim;
	GeomVideo& video = e->video;
	bool was_playing = anim.is_playing || video.is_importing;
	
	if (video.is_importing) {
		video.Update(dt);
		TimelineData();
	}
	else {
		anim.Update(dt);
	}
	
	time.SetSelectedColumn(anim.position);
	time.Refresh();
	
	if (anim.is_playing || was_playing) {
		for(int i = 0; i < 4; i++) {
			rends[i].Refresh();
		}
	}
}

void GeomProjectCtrl::Data() {
	GeomProject& prj = e->prj;
	
	tree.SetRoot(ImagesImg::Root(), "Project");
	
	if (tree_scenes < 0)
		tree_scenes = tree.Add(0, ImagesImg::Scenes(), "Scenes");
	
	for(int i = 0; i < prj.scenes.GetCount(); i++) {
		GeomScene& scene = prj.scenes[i];
		String name = scene.name.IsEmpty() ? "Scene #" + IntStr(i) : scene.name;
		int j = tree.Add(tree_scenes, ImagesImg::Scene(), i, name);
		
		TreeDirectory(j, scene);
		
		if (i == 0 && !tree.HasFocus())
			tree.SetCursor(j);
	}
	
	/*for(int i = 0; i < prj.octrees.GetCount(); i++) {
		OctreePointModel& o = prj.octrees[i];
		String name = prj.dictionary[o.id];
		tree.Add(tree_octrees, ImagesImg::Octree(), o.id, name);
	}*/
	
	tree.Open(0);
	
	TreeSelect();
}

void GeomProjectCtrl::TreeSelect() {
	if (!tree.HasFocus())
		return;
	
	int cursor = tree.GetCursor();
	int parent = tree.GetParent(cursor);
	if (parent == tree_scenes) {
		int i = tree.Get(cursor);
		GeomScene& s = e->prj.scenes[i];
		
	}

}

void GeomProjectCtrl::OnCursor(int i) {
	e->anim.position = i;
}

void GeomProjectCtrl::TreeDirectory(int id, GeomDirectory& dir) {
	for(int i = 0; i < dir.subdir.GetCount(); i++) {
		GeomDirectory& subdir = dir.subdir[i];
		String name = dir.subdir.GetKey(i);
		int j = tree.Add(id, ImagesImg::Directory(), i, name);
		TreeDirectory(j, subdir);
	}
	for(int i = 0; i < dir.objs.GetCount(); i++) {
		GeomObject& o = dir.objs[i];
		Image img;
		switch (o.type) {
			case GeomObject::O_CAMERA: img = ImagesImg::Camera(); break;
			case GeomObject::O_MODEL:  img = ImagesImg::Model(); break;
			case GeomObject::O_OCTREE: img = ImagesImg::Octree(); break;
			default: img = ImagesImg::Object();
		}
		int j = tree.Add(id, img, i, o.name);
	}
}

void GeomProjectCtrl::TimelineData() {
	GeomProject& prj = e->prj;
	GeomScene& scene = e->state.GetActiveScene();
	
	time.SetCount(scene.objs.GetCount());
	time.SetKeypointRate(prj.kps);
	time.SetLength(scene.length);
	time.SetKeypointColumnWidth(13);
	
	for(int i = 0; i < scene.objs.GetCount(); i++) {
		GeomObject& o = scene.objs[i];
		/*int j = prj.list[i];
		int id = j / GeomProject::O_COUNT;
		int type = j % GeomProject::O_COUNT;*/
		
		String name = o.name.IsEmpty() ? IntStr(i) : o.name;
		
		TimelineRowCtrl& row = time.GetRowIndex(i);
		row.SetTitle(name);
		
		row.SetKeypoints(o.timeline.keypoints.GetKeys());
		
		row.Refresh();
	}
	
	time.Refresh();
}

NAMESPACE_TOPSIDE_END
