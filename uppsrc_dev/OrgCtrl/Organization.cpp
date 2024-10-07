#include "OrgCtrl.h"
#include <TopTool/TopTool.h>

BEGIN_TEXTLIB_NAMESPACE


OrganizationCtrl::OrganizationCtrl() {
	Add(hsplit.SizePos());
	
	hsplit.Horz() << vsplit << main;
	hsplit.SetPos(1500);
	
	vsplit.Vert() << pkgs << nodes;
	vsplit.SetPos(500, 0);
	vsplit.SetPos(3333, 1);
	
	pkgs.AddColumn("Package");
	pkgs.AddIndex("IDX");
	pkgs.WhenCursor << THISBACK(DataPackage);
	pkgs.WhenBar << [this](Bar& bar) {
		bar.Add(t_("Add package"), THISBACK1(Do, ADD_PKG));
		bar.Add(t_("Remove package"), THISBACK1(Do, REM_PKG));
		
	};
	
	nodes.WhenBar << [this](Bar& bar) {
		const auto& f = NodeFactory::GetFactories();
		for(int i = 0; i < f.GetCount(); i++) {
			bar.Sub(t_("Add ") + GetNodeName(f.GetKey(i)),
				GetNodeImage((NodeType)f.GetKey(i)),
				[this,i,&f](Bar& b) {
				const auto& ff = f[i];
				for(int j = 0; j < ff.GetCount(); j++) {
					b.Add(ff[j].name, THISBACK2(AddNode, i, j));
				}
			});
		}
		bar.Separator();
		bar.Add(t_("Remove node"), THISBACK1(Do, REM_NODE));
	};
	nodes.WhenCursor << THISBACK(DataNode);
	
	
}

void OrganizationCtrl::Init() {
	
	
}

void OrganizationCtrl::ViewNodeCtrl() {
	/*if (page_group >= page_group_list.GetCount())
		page_group = page_group_list.GetCount()-1;
	if (page_group < 0)
		return;
	
	ToolEditorBase::ViewPageGroup();
	*/
}

void OrganizationCtrl::Data() {
	MetaDatabase& mdb = MetaDatabase::Single();
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	for(int i = 0; i < db.pkgs.GetCount(); i++) {
		Package& pkg = db.pkgs[i];
		pkgs.Set(i, "IDX", i);
		pkgs.Set(i, 0, pkg.name);
	}
	INHIBIT_ACTION(pkgs);
	INHIBIT_CURSOR(pkgs);
	pkgs.SetCount(db.pkgs.GetCount());
	int cursor = p.pkg_cursor;
	if (cursor >= 0 && cursor < pkgs.GetCount())
		pkgs.SetCursor(cursor);
	
	DataPackage();
}

void OrganizationCtrl::DataPackage() {
	TextDatabase& db = GetDatabase();
	EditorPtrs& p = GetPointers();
	
	nodes.Clear();
	
	if (!pkgs.IsCursor())
		return;
	int pkg_i = pkgs.Get("IDX");
	p.pkg_cursor = pkg_i;
	
	auto& pkg = db.pkgs[pkg_i];
	Node& root = pkg.root;
	root.name = pkg.name;
	nodes.SetRoot(OrgLibImgs::root, pkg.name);
	
	AddNodeSubToList(0, root);
	
	//nodes.OpenDeep(0);
	nodes.Open(0);
	
	INHIBIT_ACTION(nodes);
	INHIBIT_CURSOR(nodes);
	if (p.node_cursor >= 0 && p.node_cursor < nodes.GetLineCount())
		nodes.SetCursor(p.node_cursor);
	
	DataNode();
}

void OrganizationCtrl::AddNodeToList(int cur, Node& n) {
	String name;
	if (0) {
		name = GetNodeName(n.type);
		if (!n.name.IsEmpty())
			name += ": " + n.name;
	}
	else {
		name = n.name;
	}
	int ncur = nodes.Add(cur, GetNodeImage(n.type), name);
	AddNodeSubToList(ncur, n);
}

void OrganizationCtrl::AddNodeSubToList(int cur, Node& n) {
	node_ptrs.GetAdd(cur) = &n;
	for(int i = 0; i < n.sub.GetCount(); i++) {
		AddNodeToList(cur, n.sub[i]);
	}
}

void OrganizationCtrl::RemoveCtrl() {
	if (ctrl) {
		main.RemoveChild(&*ctrl);
		ctrl.Clear();
		view.Clear();
	}
	cur_view = NODE_INVALID;
	cur_ff = -1;
}

void OrganizationCtrl::DataNode() {
	EditorPtrs& p = GetPointers();
	
	if (!nodes.IsCursor()) {
		RemoveCtrl();
		return;
	}
	
	int cur = nodes.GetCursor();
	p.node_cursor = cur;
	if (p.editor) p.editor->app.PostStoreLast();
	
	int i = node_ptrs.Find(cur);
	if (i < 0) {
		RemoveCtrl();
		return;
	}
	Node& n = *node_ptrs[i];
	if (n.ff_i < 0) {
		n.ff_i = 0;
	}
	if (cur_view == n.type && cur_ff == n.ff_i) {
		DataView();
		return;
	}
	
	RemoveCtrl();
	
	
	const auto& f = NodeFactory::GetFactories();
	i = f.Find(n.type);
	if (i < 0)
		return;
	const auto& v = f[i];
	if (n.ff_i >= v.GetCount()) {
		RemoveCtrl();
		return;
	}
	const auto& ff = v[n.ff_i];
	ctrl = ff.ctrl();
	view = ff.view();
	ctrl->org = this;
	view->org = this;
	ctrl->view = &*view;
	main.Add(ctrl->SizePos());
	
	cur_view = n.type;
	cur_ff = n.ff_i;
	
	DataView();
}

void OrganizationCtrl::DataView() {
	if (view) {
		int cur = nodes.GetCursor();
		int i = node_ptrs.Find(cur);
		view->SetNode(i >= 0 ? node_ptrs[i] : 0);
		view->Data();
	}
	if (ctrl) {
		ctrl->Data();
		WhenToolMenuUpdate();
	}
}

void OrganizationCtrl::ToolMenu(Bar& bar) {
	if (ctrl)
		ctrl->ToolMenu(bar);
}

TextDatabase& OrganizationCtrl::GetDatabase() {
	return MetaDatabase::Single().db;
}

EditorPtrs& OrganizationCtrl::GetPointers() {
	return MetaPtrs::Single().db;
}

void OrganizationCtrl::AddNode(int i, int j) {
	const auto& f = NodeFactory::GetFactories();
	const auto& ff = f[i][j];
	if (!nodes.IsCursor())
		return;
	int cur = nodes.GetCursor();
	int k = node_ptrs.Find(cur);
	if (k < 0)
		return;
	Node& n = *node_ptrs[k];
	Node& sub = n.sub.Add();
	sub.type = (NodeType)f.GetKey(i);
	sub.name = ff.name;
	sub.ff_i = j;
	
	PostCallback(THISBACK(DataPackage));
}

void OrganizationCtrl::Do(int fn) {
	MetaDatabase& mdb = MetaDatabase::Single();
	TextDatabase& db = GetDatabase();
	
	if (fn == ADD_PKG) {
		String name;
		bool b = EditTextNotNull(
			name,
			t_("Add Package"),
			t_("Package's name"),
			0
		);
		if (!b) return;
		
		int pkg_i = -1;
		for(int i = 0; i < db.pkgs.GetCount(); i++) {
			Package& a = db.pkgs[i];
			if (a.name == name) {
				pkg_i = i;
				break;
			}
		}
		if (pkg_i >= 0) {
			PromptOK(DeQtf(t_("Profile exist already")));
			return;
		}
		
		Package& pkg = db.pkgs.Add();
		pkg.name = name;
		pkg.json_path = AppendFileName(db.GetPackageDir(), name + DIR_SEPS + "pkg.json");
		pkg.StoreToFile();
		
		PostCallback(THISBACK(Data));
	}
	if (fn == REM_PKG) {
		if (!pkgs.IsCursor())
			return;
		int idx = pkgs.Get("IDX");
		if (idx >= 0 && idx < db.pkgs.GetCount())
			db.pkgs.Remove(idx);
		
		PostCallback(THISBACK(Data));
	}
	if (fn == REM_NODE) {
		if (!nodes.IsCursor())
			return;
		int i = node_ptrs.Find(nodes.GetCursor());
		if (i < 0)
			return;
		Node& n = *node_ptrs[i];
		if (n.owner)
			n.owner->Remove(n);
		
		PostCallback(THISBACK(DataPackage));
	}
}


END_TEXTLIB_NAMESPACE
