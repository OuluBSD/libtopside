#ifndef _PlayEditor_App_h_
#define _PlayEditor_App_h_

using namespace Upp;
#define LAYOUTFILE <PlayEditor/App.lay>
#include <CtrlCore/lay.h>

NAMESPACE_TOPSIDE_BEGIN


class PlayEditor : public TopWindow {
	Splitter part_split;
	ArrayCtrl partlist;
	TabCtrl tabs;
	PlayPart* active_part = 0;
	PlaySection* active_sect = 0;
	MenuBar menu;
	
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
	bool is_subtitle_recording = false;
	int subtitle_recording_offset = 0;
	int subtitle_recording_cursor = 0;
	TimeCallback st_tc;
	TimeStop st_ts;
	
	// Rendering
	Splitter rend_split;
	ArrayCtrl rend_dialog;
	WithPlayRenderer<ParentCtrl> rend_ctrl;
	bool is_render_play = false;
	int play_begin_time = 0;
	TimeCallback rend_tc;
	TimeStop rend_ts;
	
	// Exporting
	WithVideoExport<ParentCtrl> exporting;
	VideoExporter exporter;
	TimeCallback export_tc;
	
	
	PlayScript script;
	PlayRenderer renderer;
	
	void MainMenu(Bar& bar);
	
	void OnMessage(const ProcMsg& p);
	void Data();
	void TabData();
	void SubtitleData();
	bool ActivateSection(int part_i, int sect_i);
	
	void SubtitleTap();
	void SubtitleStop();
	void SubtitleIteration();
	void SubtitleUpdate();
	
	void OnTimeSlider();
	void ToggleRenderPlay();
	void RenderFrameToPlayer();
	void ReadRendererConfig(PlayRendererConfig& cfg);
	
	void ToggleExporting();
	void OnExportingStop();
	void OnExportingProgressUpdate();
	void PostOnExportingStop() {PostCallback(THISBACK(OnExportingStop));}
	
public:
	typedef PlayEditor CLASSNAME;
	
	PlayEditor();
	
	void SaveFile();
	bool LoadFile(String path);
	bool Load(String content, String path);
	
	
};


NAMESPACE_TOPSIDE_END

#endif
