#ifndef _TopTool_App_h_
#define _TopTool_App_h_


BEGIN_TEXTLIB_NAMESPACE


class TopTool : public TopWindow {
	MenuBar				menu;
	ToolBar				toolbar;
	StatusBar			statusbar;
	
	LeadsCtrl			lead;
	OrganizationCtrl	org;
	ServicesCtrl		svc;
	ToolEditor			ed;
	Tasks				ai;
	ManagerCtrl			mc;
	
	TimeCallback		tc;
	bool				skip_data = false;
	ToolEditorBase*		active = 0;
	bool				posted_store_last = false;
	
	int page = 0;
	Rect last_window;
	bool is_maximized = false;
	bool started = false;
	
	void Load() {LoadFromFile(*this, ConfigFile("cookie.bin"));}
	void Store() {StoreToFile(*this, ConfigFile("cookie.bin"));}
	
protected:
	friend class ToolEditor;
	
	String last_script, last_part;
	String last_entity, last_snapshot, last_component;
	String last_owner, last_profile;
	int last_pkg = 0, last_node = 0;
	
public:
	typedef TopTool CLASSNAME;
	TopTool();
	~TopTool();
	
	void MainMenu(Bar& b);
	void SetOpenAIToken();
	void Init();
	void PostInit() {PostCallback(THISBACK(Init));}
	void Data();
	void SetView(int i);
	void Serialize(Stream& s) override {s % page % last_window % is_maximized % last_entity % last_snapshot % last_component % last_script % last_part % last_owner % last_profile % last_pkg % last_node;}
	void Layout() override {SaveWindowPos();}
	void ShowOrphanedFiles();
	void SaveWindowPos();
	void LoadWindowPos();
	void StartUpdating();
	void MovePageGroup(int d);
	void MovePage(int d);
	void MovePart(int d);
	void SetBar();
	void MainBar(Bar& bar);
	void FastExit();
	void SaveDatabase();
	void StoreLast();
	void PostStoreLast();
	void SetSaveSongdata(bool b) {ed.SetSaveSongdata(b);}
	
	ToolEditor& GetEditor() {return ed;}
	OrganizationCtrl& GetOrganization() {return org;}
	LeadsCtrl& GetLeads() {return lead;}
	
};


END_TEXTLIB_NAMESPACE


#endif
