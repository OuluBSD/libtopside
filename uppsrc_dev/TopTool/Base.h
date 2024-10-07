#ifndef _TopTool_Base_h_
#define _TopTool_Base_h_


BEGIN_TEXTLIB_NAMESPACE



class TopTool;

class ToolEditorBase : public Ctrl {
	const char* title = 0;
	
protected:
	struct ListItem : Moveable<ListItem> {
		String item;
		ToolAppCtrl* ctrl = 0;
	};
	VectorMap<String, Vector<ListItem>> items;
	
	
	ArrayCtrl			parts, page_group_list, page_list;
	ArrayCtrl			owners;
	ArrayCtrl			profiles;
	int					page_group = 0;
	VectorMap<int,int>	page;
	bool				save_data = false;
	
	void AddItem(String g, String i, ToolAppCtrl& c);
	
public:
	TopTool&			app;
	Ctrl				base;
	Ctrl				subsplit;
	bool				filter_profile_language = false;
	
public:
	typedef ToolEditorBase CLASSNAME;
	ToolEditorBase(const char* title, TopTool& app);
	void UpdatePageList();
	void ViewPage();
	void Init();
	void SetView(int i, int j);
	void ToolMenu(Bar& bar);
	void OwnerMenu(Bar& bar);
	void ProfileMenu(Bar& bar);
	void SnapshotMenu(Bar& bar);
	void DataMeta();
	void DataOwner();
	void DataProfile();
	void AddOwner();
	void RemoveOwner();
	void AddProfile();
	void RemoveProfile();
	void FixMenuBar();
	virtual void Data() {}
	virtual void ViewPageGroup();
	virtual void DataPage();
	virtual void OnDataSnapshot() {}
	virtual void SetSubMenu(int i) = 0;
	void Serialize(Stream& s) override;
	
	Callback WhenStartUpdating, WhenStopUpdating;
	
};



END_TEXTLIB_NAMESPACE


#endif
