#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


void Component::Store(Snapshot& snap) {
	snapshot = &snap;
	String dir =
		AppendFileName(
			AppendFileName(
				AppendFileName(
					GetAppModeDatabase().GetEntitiesDir(), snapshot->entity->file_title),
					snapshot->file_title),
				file_title);
	RealizeDirectory(dir);
	String json_path = dir + DIR_SEPS + "db.json";
	StoreAsJsonFileStandard(*this, json_path, true);
}

void Component::LoadTitle(Snapshot& snap, String title) {
	snapshot = &snap;
	file_title = title;
	String dir =
		AppendFileName(
			AppendFileName(
				AppendFileName(
					GetAppModeDatabase().GetEntitiesDir(), snapshot->entity->file_title),
					snapshot->file_title),
				file_title);
	String json_path = dir + DIR_SEPS + "db.json";
	LoadFromJsonFileStandard(*this, json_path);
}

String Component::GetAnyTitle(Entity& a) const {
	int lyr_i = a.FindScript(scripts_file_title);
	if (lyr_i >= 0) {
		const Script& l = a.scripts[lyr_i];
		if (l.native_title.GetCount())
			return l.native_title;
		
	}
	return file_title;
}


END_TEXTLIB_NAMESPACE

