#ifndef _PlayEditor_App_h_
#define _PlayEditor_App_h_

using namespace Upp;
#define LAYOUTFILE <PlayEditor/App.lay>
#include <CtrlCore/lay.h>

NAMESPACE_TOPSIDE_BEGIN



class PlayEditor;


class PlayRendererCtrl : public Ctrl {
	PlayRenderer rend;
	
	
public:
	
	
};


class PlayEditor : public TopWindow {
	Splitter part_split;
	ArrayCtrl partlist;
	TabCtrl tabs;
	PlayPart* active_part = 0;
	PlaySection* active_sect = 0;
	
	enum {
		TAB_METASCRIPT,
		TAB_METASECTION,
		TAB_DIALOG,
		TAB_SUBTITLES,
		TAB_RENDER,
	};
	
	// Section meta-script-data
	WithMetaScript<ParentCtrl> scriptconf;
	
	// Section meta-section-data
	WithMetaSection<ParentCtrl> sectconf;
	
	// Dialogue edit
	ArrayCtrl dialog;
	Splitter dialog_split;
	WithLineConf<ParentCtrl> lineconf;
	
	// Subtitles
	Splitter st_split;
	ArrayCtrl st_dialog;
	WithSubtitleEdit<ParentCtrl> st_edit;
	
	// Rendering
	Splitter rend_split;
	ArrayCtrl rend_dialog;
	PlayRendererCtrl rend_ctrl;
	
	
	
	
	PlayScript script;
	
	void OnMessage(const ProcMsg& p);
	void Data();
	void TabData();
	bool ActivateSection(int part_i, int sect_i);
	
public:
	typedef PlayEditor CLASSNAME;
	
	PlayEditor();
	
	bool LoadFile(String path);
	bool Load(String content, String path);
	
	
};


NAMESPACE_TOPSIDE_END

#endif
