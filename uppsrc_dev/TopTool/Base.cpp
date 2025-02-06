#include "TopTool.h"


BEGIN_TEXTLIB_NAMESPACE



ToolEditorBase::ToolEditorBase(const char* title, TopTool& app) : title(title), app(app) {
	page_group_list.AddColumn(t_("Page group"));
	page_group_list.WhenCursor = THISBACK(ViewPageGroup);
	
	page_list.AddColumn(t_("Page"));
	page_list.WhenCursor = THISBACK(ViewPage);
	
	owners.AddColumn(t_("Owner"));
	owners.AddIndex("IDX");
	owners.WhenCursor = THISBACK(DataOwner);
	owners.WhenBar << THISBACK(OwnerMenu);
	
	profiles.AddColumn(t_("Profile"));
	profiles.WhenCursor = THISBACK(DataProfile);
	profiles.WhenBar << THISBACK(ProfileMenu);
	profiles.AddIndex("IDX");
	
}

void ToolEditorBase::Serialize(Stream& s) {
	s % page_group % page % save_data;
	
	#if COOKIE_DEBUG
	LOG(IntStr64((size_t)this) + " Loading: " << (int)s.IsLoading());
	DUMP(page_group);
	DUMP(page);
	#endif
}
void ToolEditorBase::Init() {
	INHIBIT_ACTION_(page_group_list, 0);
	INHIBIT_ACTION_(page_list, 1);
	
	#if COOKIE_DEBUG
	LOG(IntStr64((size_t)this) + " Init");
	#endif
	
	page_group_list.SetCursor(page_group);
	int page = this->page.GetAdd(page_group, 0);
	page_list.SetCursor(page);
	SetView(page_group, page);
	
	Data();
	app.SetBar(); // requires Data();
	
	FixMenuBar();
}

void ToolEditorBase::FixMenuBar() {
	int page = this->page.GetAdd(page_group, 0);
	PostCallback(THISBACK2(SetView, page_group, page)); // fix quirky behaviour
}

void ToolEditorBase::AddItem(String g, String i, ToolAppCtrl& c) {
	ListItem& it = items.GetAdd(g).Add();
	it.item = i;
	it.ctrl = &c;
}

void ToolEditorBase::SetView(int i, int j) {
	for (const auto& v : items)
		for (const ListItem& it : v)
			it.ctrl->Hide();
	
	parts.Enable();
	
	WhenStopUpdating();
	
	if (i >= 0 && i < items.GetCount() && j >= 0 && j < items[i].GetCount())
		items[i][j].ctrl->Show();
	
	
	// Save 'cookie' about last viewed page
	page_group = i;
	page.GetAdd(i) = j;
	
	#if COOKIE_DEBUG
	LOG(IntStr64((size_t)this) + " SetView");
	DUMP(page_group);
	DUMP(page);
	#endif
	
	if (page_group == items.Find("Script"))
		SetSubMenu(1);
	else
		SetSubMenu(0);
	
	DataPage();
	
	app.SetBar();
}

void ToolEditorBase::DataPage() {
	int page = this->page.GetAdd(page_group, 0);
	try {
		if (page_group >= 0 && page_group < items.GetCount() && page >= 0 && page < items[page_group].GetCount())
			items[page_group][page].ctrl->Data();
	}
	catch (NoPointerExc e) {
		LOG("error: " << e);
	}
}

void ToolEditorBase::ToolMenu(Bar& bar) {
	int page = this->page.GetAdd(page_group, 0);
	if (page_group >= 0 && page_group < items.GetCount() && page >= 0 && page < items[page_group].GetCount())
		items[page_group][page].ctrl->ToolMenu(bar);
}

void ToolEditorBase::ViewPage() {
	SetView(page_group_list.GetCursor(), page_list.GetCursor());
	//DataPage(); // Duplicate
}

void ToolEditorBase::UpdatePageList() {
	page_group_list.Clear();
	
	for(int i = 0; i < items.GetCount(); i++) {
		String group = items.GetKey(i);
		page_group_list.Add(group);
	}
	
	INHIBIT_ACTION(page_group_list);
	if (page_group >= 0 && page_group < page_group_list.GetCount())
		page_group_list.SetCursor(page_group);
	
	ViewPageGroup();
}

void ToolEditorBase::ViewPageGroup() {
	int page_group = page_group_list.GetCursor();
	int page = this->page.GetAdd(page_group, 0);
	if (page_group < 0)
		return;
	
	const auto& v = items[page_group];
	for(int j = 0; j < v.GetCount(); j++) {
		const ListItem& it = v[j];
		page_list.Set(j, 0, it.item);
		base.Add(it.ctrl->SizePos());
	}
	INHIBIT_ACTION(page_list);
	page_list.SetCount(v.GetCount());
	page_list.SetCursor(page);
	
	if (page >= v.GetCount())
		page = v.GetCount()-1;
	
	SetView(page_group, page);
	DataPage();
}

void ToolEditorBase::DataMeta() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	
	for(int i = 0; i < mdb.owners.GetCount(); i++) {
		owners.Set(i, 0, mdb.owners[i].name);
		owners.Set(i, "IDX", i);
	}
	INHIBIT_CURSOR(owners);
	owners.SetCount(mdb.owners.GetCount());
	int owner_i = p.GetOwnerIndex();
	if (owner_i >= 0 && owner_i < owners.GetCount())
		owners.SetCursor(owner_i);
	else if (!owners.IsCursor() && owners.GetCount())
		owners.SetCursor(0);
	
	
	DataOwner();
}

void ToolEditorBase::DataOwner() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	if (!owners.IsCursor())
		return;
	
	int owner_i = owners.GetCursor();
	Owner& owner = mdb.owners[owner_i];
	p.owner = owners.IsCursor() ? &mdb.owners[owners.GetCursor()] : 0;
	
	int row = 0;
	for(int i = 0; i < owner.profiles.GetCount(); i++) {
		Profile& p = owner.profiles[i];
		profiles.Set(row, 0, owner.profiles[i].name);
		profiles.Set(row, "IDX", i);
		row++;
	}
	INHIBIT_CURSOR(profiles);
	profiles.SetCount(row);
	int profile_i = FindArrayIndex(profiles, p.GetProfileIndex());
	if (profile_i >= 0 && profile_i < profiles.GetCount())
		profiles.SetCursor(profile_i);
	else if (!profiles.IsCursor() && profiles.GetCount())
		profiles.SetCursor(0);
	
	DataProfile();
}

void ToolEditorBase::DataProfile() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	if (!owners.IsCursor() || !profiles.IsCursor())
		return;
	
	int owner_i = owners.Get("IDX");
	Owner& owner = mdb.owners[owner_i];
	int prof_i = profiles.Get("IDX");
	p.profile = &owner.profiles[prof_i];
	
}

void ToolEditorBase::OwnerMenu(Bar& bar) {
	bar.Add(t_("Add Owner"), THISBACK(AddOwner));
	
	if (owners.IsCursor()) {
		bar.Add(t_("Delete Owner"), THISBACK(RemoveOwner));
	}
}

void ToolEditorBase::ProfileMenu(Bar& bar) {
	bar.Add(t_("Add Profile"), THISBACK(AddProfile));
	
	if (profiles.IsCursor()) {
		bar.Add(t_("Delete Profile"), THISBACK(RemoveProfile));
	}
}

void ToolEditorBase::AddOwner() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	
	String name;
	bool b = EditTextNotNull(
		name,
		t_("Add Owner"),
		t_("Owner's name"),
		0
	);
	if (!b) return;
	
	String t = MakeTitle(name);
	int artist_i = -1;
	for(int i = 0; i < mdb.owners.GetCount(); i++) {
		Owner& a = mdb.owners[i];
		if (a.name == t) {
			artist_i = i;
			break;
		}
	}
	if (artist_i >= 0) {
		/*if (!PromptYesNo(DeQtf(Format(t_("Do you want to replace file for artist '%s'"), name)))
			return;*/
		PromptOK(DeQtf(t_("Owner exist already")));
		return;
	}
	
	Owner& a = mdb.owners.Add();
	a.name = name;
	p.owner = &a;
	
	Data();
}

void ToolEditorBase::AddProfile() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	if (!owners.IsCursor())
		return;
	
	int owner_i = owners.GetCursor();
	Owner& owner = mdb.owners[owner_i];
	
	String name;
	bool b = EditTextNotNull(
		name,
		t_("Add Profile"),
		t_("Profile's name"),
		0
	);
	if (!b) return;
	
	int artist_i = -1;
	for(int i = 0; i < owner.profiles.GetCount(); i++) {
		Profile& a = owner.profiles[i];
		if (a.name == name) {
			artist_i = i;
			break;
		}
	}
	if (artist_i >= 0) {
		/*if (!PromptYesNo(DeQtf(Format(t_("Do you want to replace file for artist '%s'"), name)))
			return;*/
		PromptOK(DeQtf(t_("Profile exist already")));
		return;
	}
	
	Profile& a = owner.profiles.Add();
	a.owner = &owner;
	a.name = name;
	p.profile = &a;
	
	DataOwner();
}

void ToolEditorBase::RemoveOwner() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	if (owners.IsCursor()) {
		mdb.owners.Remove(owners.GetCursor());
	}
	Data();
}

void ToolEditorBase::RemoveProfile() {
	if (!owners.IsCursor())
		return;
	
	MetaDatabase& mdb = MetaDatabase::Single();
	int owner_i = owners.GetCursor();
	Owner& owner = mdb.owners[owner_i];
	
	MetaPtrs& p = MetaPtrs::Single();
	if (profiles.IsCursor()) {
		owner.profiles.Remove(profiles.GetCursor());
	}
	DataOwner();
}

END_TEXTLIB_NAMESPACE

