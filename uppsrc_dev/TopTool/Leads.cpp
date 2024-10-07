#include "TopTool.h"


BEGIN_TEXTLIB_NAMESPACE


LeadsCtrl::LeadsCtrl(TopTool* app) : ToolEditorBase("leads", *app) {
	MetaPtrs::Single().leads = this;
	
	Add(hsplit.SizePos());
	
	hsplit.Horz() << menusplit << base;
	hsplit.SetPos(1000);
	
	menusplit.Vert() << page_group_list << page_list << owners << profiles;
	
}

void LeadsCtrl::InitSimplified() {
	AddItem(t_("Tools"), t_("AI Image Generator"), image_gen);
	AddItem(t_("Tools"), t_("AI Image aspect ratio fixer"), aspect_fixer);
	AddItem(t_("Profile"), t_("Owner Info"), owner_info);
	AddItem(t_("Profile"), t_("Profile Info"), profile_info);
	
}

void LeadsCtrl::Init() {
	ToolEditorBase::Init(); // must be first
	UpdatePageList();
	
}

void LeadsCtrl::Data() {
	DataMeta();
}

void LeadsCtrl::OnDataSnapshot() {
	DataPage();
}

void LeadsCtrl::SetSubMenu(int i) {
	
}


END_TEXTLIB_NAMESPACE

