#include "TextDataCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE



TextDatabase& ToolAppCtrl::GetDatabase() const {
	return GetAnyEditor().GetDatabase();
}

bool ToolAppCtrl::HasPointers() const {
	return HasAnyEditor();
}

EditorPtrs& ToolAppCtrl::GetPointers() const {
	return GetAnyEditor().GetPointers();
}

/*const Index<String>& ToolAppCtrl::GetTypeclasses() const {
	static Index<String> v;
	TODO
	return v;
}

const Vector<ContentType>& ToolAppCtrl::GetContents() const {
	static Vector<ContentType> v;
	TODO
	return v;
}

const Vector<String>& ToolAppCtrl::GetContentParts() const {
	static Vector<String> v;
	TODO
	return v;
}*/



END_TEXTLIB_NAMESPACE
