#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


void Snapshot::Store(Entity& e) {
	entity = &e;
	String dir =
		AppendFileName(
			AppendFileName(
				GetAppModeDatabase().GetEntitiesDir(), entity->file_title),
				file_title);
	RealizeDirectory(dir);
	String json_path = dir + DIR_SEPS + "db.json";
	StoreAsJsonFileStandard(*this, json_path, true);
}

void Snapshot::LoadTitle(Entity& e, String title) {
	entity = &e;
	file_title = title;
	String dir =
		AppendFileName(
			AppendFileName(
				GetAppModeDatabase().GetEntitiesDir(), entity->file_title),
				file_title);
	String json_path = dir + DIR_SEPS + "db.json";
	LoadFromJsonFileStandard(*this, json_path);
}

Component& Snapshot::GetAddComponent(String name) {
	String file_title = MakeTitle(name);
	for(Component& comp : components) {
		if (comp.file_title == file_title)
			return comp;
	}
	Component& comp = components.Add();
	comp.file_title = file_title;
	return comp;
}

/*Component& Snapshot::RealizeReversed(Component& s) {
	for (Component& r : reversed_components)
		if (r.linked_uniq == s.uniq)
			return r;
	Component& r = reversed_components.Add();
	r.file_title = s.file_title;
	r.linked_uniq = s.uniq;
	r.artist = s.artist;
	r.title = s.title;
	r.prj_name = s.prj_name;
	r.structure_str = s.structure_str;
	r.data <<= s.data;
	r.content = s.content;
	r.owner = this;
	r.SetReversed();
	r.SetId(reversed_components.GetCount()-1);
	r.FixPtrs();
	return r;
}*/


END_TEXTLIB_NAMESPACE

