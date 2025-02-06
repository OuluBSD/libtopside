#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE




Script::~Script() {
	
}

void Script::Store(Entity& a) {
	String dir = a.GetScriptDir();
	RealizeDirectory(dir);
	String json_path = dir + file_title + ".json";
	StoreAsJsonFileStandard(*this, json_path, true);
}

void Script::LoadTitle(Entity& a, String title) {
	String dir = a.GetScriptDir();
	file_title = title;
	String json_path = dir + file_title + ".json";
	LoadFromJsonFileStandard(*this, json_path);
}

String Script::GetAnyTitle() const {
	if (native_title.GetCount())
		return native_title;
	
	return file_title;
}

String Script::GetText() const {
	TODO return String();
}



END_TEXTLIB_NAMESPACE

