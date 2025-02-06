#ifndef _TopTool_Editor_h_
#define _TopTool_Editor_h_


BEGIN_TEXTLIB_NAMESPACE


class ToolEditor : public ToolEditorBase {
	
protected:
	friend class EntityInfoCtrl;
	friend class SnapInfoCtrl;
	friend class CompInfoCtrl;
	friend class ScriptInfoCtrl;
	friend class TopTool;
	
	Splitter			hsplit, menusplit, componentsplit;
	ArrayCtrl			snaps, components;
	ArrayCtrl			scripts;
	bool				fast_exit = false;
	
	ImageGenTool					image_gen;
	ImageAspectFixerTool			aspect_fixer;
	EntityInfoCtrl					entity_info;
	SnapInfoCtrl					snap_info;
	CompInfoCtrl					comp_info;
	ScriptInfoCtrl					script_info;
	
	
public:
	typedef ToolEditor CLASSNAME;
	ToolEditor(TopTool* app);
	
	void Init();
	void ViewPageGroup() override;
	void Data() override;
	void OnDataSnapshot() override;
	void DataSnapshot();
	void DataComponent();
	void DataScript();
	//void DataPart();
	void MovePageGroup(int d);
	void MovePage(int d);
	void MovePart(int d);
	String GetStatusText();
	bool GetSaveSongdata() const {return save_data;}
	bool IsFastExit() const {return fast_exit;}
	void SetSaveSongdata(bool b) {save_data = b;}
	void SetFastExit(bool b) {fast_exit = b;}
	void LoadLast();
	void SetSubMenu(int i) override;
	void DataPage() override;
	
	//void EntityMenu(Bar& bar);
	void SnapshotMenu(Bar& bar);
	void SongMenu(Bar& bar);
	void ScriptMenu(Bar& bar);
	
	//void AddEntity();
	//void RenameEntity();
	//void RemoveEntity();
	void AddSnapshot();
	void RenameSnapshot();
	void RemoveSnapshot();
	void AddSong();
	void RenameSong();
	void RemoveSong();
	void AddScript();
	void RemoveScript();
	
	void InitSimplified();
	//void InitAdvanced();
	
	TextDatabase& GetDatabase();
	EditorPtrs& GetPointers();
	int GetAppMode() const;
	
};


END_TEXTLIB_NAMESPACE


#endif

