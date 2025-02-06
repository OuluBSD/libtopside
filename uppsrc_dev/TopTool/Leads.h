#ifndef _TopTool_Leads_h_
#define _TopTool_Leads_h_


BEGIN_TEXTLIB_NAMESPACE


class TopTool;

class LeadsCtrl : public ToolEditorBase {
	
protected:
	friend class OwnerInfoCtrl;
	friend class ProfileInfoCtrl;
	Splitter					hsplit, menusplit;
	ArrayCtrl					componentlist;
	
	ImageGenTool				image_gen;
	ImageAspectFixerTool		aspect_fixer;
	
	OwnerInfoCtrl				owner_info;
	ProfileInfoCtrl				profile_info;
	
public:
	typedef LeadsCtrl CLASSNAME;
	LeadsCtrl(TopTool* app);
	
	void Init();
	void Data() override;
	void DataComponent();
	void InitSimplified();
	void SetSubMenu(int i) override;
	void OnDataSnapshot() override;
	
};



END_TEXTLIB_NAMESPACE


#endif
