#include "Navigator.h"
#include "ProjectManager.h"
#include "MainEditor.h"

PackageFileList::PackageFileList() {
	
}

void PackageFileList::LocalMenu(Bar& bar) {
	bar.Add("Insert package directory file(s)", Proxy(WhenAddFiles));
	bar.Separator();
	bar.Add("Rename", Proxy(WhenRename));
	
}

void PackageFileList::RightDown(Point, dword) {
	MenuBar::Execute(THISBACK(LocalMenu));
}






NavigatorCtrl::NavigatorCtrl(IDE* ide) : ide(ide) {
	ide = 0;
	
	Add(split.VSizePos().HSizePos());
	
	split << blocks << files << references;
	split.Vert();
	
	blocks.WhenAction = THISBACK(SelectBlock);
	files.WhenAction = THISBACK(SelectFile);
	files.WhenAddFiles  = THISBACK(AddFiles);
	files.WhenRename = THISBACK(RenameFile);
	
	blocks	.Columns(2);
	files	.Columns(2);
	
	references.AddColumn("Key");
	references.AddColumn("Line");
}

void NavigatorCtrl::ClearBlocks() {
	blocks.Clear();
}

void NavigatorCtrl::AddBlock(String name) {
	blocks.Add(name);
}

void NavigatorCtrl::SetBlock(String name) {
	
}

void NavigatorCtrl::SelectBlock() {
	if (blocks.GetCount() == 0) return;
	LoadBlock(blocks.GetCursor());
}

void NavigatorCtrl::LoadBlock(int id) {
	//TODO: position may change when trying to load new package but canceling... so this is not final solution
	files.Clear();
	if (id == -1) return;
	String name = blocks.Get(id);
	int assembly = ide->GetProject().GetOpenPackage().assembly;
	Package& p = GetProjectManager().GetPackage(assembly, name);
	
	for(int i = 0; i < p.files.GetCount(); i++) {
		PackageFile& pf = p.files[i];
		String rel_path = GetRelativePath(pf.path, GetFileDirectory(p.path));
		files.Add(rel_path);
	}
}

void NavigatorCtrl::RenameFile() {
	int id = files.GetCursor();
	
	int bid = blocks.GetCursor();
	String name = blocks.Get(bid);
	int assembly = ide->GetProject().GetOpenPackage().assembly;
	Package& p = GetProjectManager().GetPackage(assembly, name);
	
	ASSERT(id >= 0 && id < p.files.GetCount());
	
	PackageFile& pf = p.files[id];
	
	String n = pf.name;
	EditText(n, "New filename", "Name");
	
	if (n != pf.name) {
		String new_path = AppendFileName( GetFileDirectory(pf.path), n);
		if (FileExists(new_path)) {
			PromptOK("File exists: " + new_path);
			return;
		}
		FileOut out(new_path);
		if (!out.IsOpen()) return;
		
		FileIn in(pf.path);
		if (!in.IsOpen()) return;
		
		out << in.Get(in.GetSize());
		out.Close();
		in.Close();
		
		DeleteFile(pf.path);
		pf.path = new_path;
		pf.name = n;
		
		p.Store();
		RefreshFiles();
	}
}

void NavigatorCtrl::SelectFile() {
	if (files.GetCount() == 0) return;
	LoadFile(files.GetCursor());
}

void NavigatorCtrl::LoadFile(int id) {
	if (id < 0) return;
	
	NodeCache& cache = ide->GetProject().GetCache();
	
	int bid = blocks.GetCursor();
	String name = blocks.Get(bid);
	int assembly = ide->GetProject().GetOpenPackage().assembly;
	Package& p = GetProjectManager().GetPackage(assembly, name);
	
	ASSERT(id >= 0 && id < p.files.GetCount());
	PackageFile& pf = p.files[id];
	
	const String& path = p.files[id].path;
	LOG("Open " << path);
	
	WhenSelectFile(path);
	
	String ext = GetFileExt(path);
	if (ext==".cpp" || ext==".c" || ext==".h") {
		ClangNode& pkg = cache.GetPackage(p.name);
		ClangNode& file = NodeGetFile(pkg, GetFileName(path));
		cache.LoadFileNode(path, file);
		cache.StoreThis();
		/*
		Project& prj = ide->GetProject();
		Translation::Project& proj = prj.GetTranslator();
		if (proj.FindUnit(path) == -1)
			proj.AddUnit(path, prj.GetTopFolders());
		Translation::Unit& unit = proj.GetUnit(path);
		*/
		SetFile(path);
	}
	
	
}

static inline bool StringsEqual_i(const String& lhs, const String& rhs)
{
    return lhs == rhs;
}

int FindFirstOf(const String& src, const char* match, int startpos=0) {
    if (startpos < 0) return -1;
    int match_len = strlen(match);
    for(int i = startpos; i < src.GetCount(); i++) {
        int c = src[i];
        for(int j = 0; j < match_len; j++) {
            if (c == match[j]) {
                return i;
            }
        }
    }
    return -1;
}

static void SplitPath(const String& in_path, Vector<String>& split_path)
{
    int start = 0;
    int dirsep;
    do
    {
        dirsep = FindFirstOf(in_path, "/", start);
        if (dirsep == -1)
            split_path.Add(in_path.Mid(start));
        else
            split_path.Add(in_path.Mid(start, dirsep - start));
        start = dirsep + 1;
    } while (dirsep != -1);
}


String GetRelativePath(const String& to, const String& from)
{
    Vector<String> to_dirs;
    Vector<String> from_dirs;

    SplitPath(to, to_dirs);
    SplitPath(from, from_dirs);
    if (from_dirs.GetCount() && from_dirs[from_dirs.GetCount()-1] == "")
        from_dirs.Remove(from_dirs.GetCount()-1);

    String output;
    output.Reserve(to.GetCount());

    Vector<String>::Iterator to_it = to_dirs.Begin(),
                                             to_end = to_dirs.End(),
                                             from_it = from_dirs.Begin(),
                                             from_end = from_dirs.End();

    while ((to_it != to_end) && (from_it != from_end) && StringsEqual_i(*to_it, *from_it))
    {
         ++to_it;
         ++from_it;
    }

    while (from_it != from_end)
    {
        output += "../";
        ++from_it;
    }

    while (to_it != to_end)
    {
        output += *to_it;
        ++to_it;

        if (to_it != to_end)
            output += "/";
    }

    return output;
}


void NavigatorCtrl::AddFiles() {
	FileSel fs; 
	
	ProjectManager& pman = GetProjectManager();
	Project& prj = ide->GetProject();
	Package& pkg = prj.GetOpenPackage();
	NodeCache& cache = ide->GetProject().GetCache();
	
	fs.Set(GetFileDirectory(pkg.path));
	fs.Type("Any file(s)", "*.*");
	//fs.Type("Image file(s)", "*.jpg *.gif *.png *.bmp");
	//fs.Preview(img);
	
	bool b = fs.ExecuteOpen();
	
	if (b) {
		String path = fs.Get();
		LOG("Add file: " << path);
		if (!FileExists(path)) {
			FileOut out(path);
		}
		Vector<String>& files = pkg.info.Get("file");
		String rel_path = GetRelativePath(path, GetFileDirectory(pkg.path));
		files.Add(rel_path);
		int id = pkg.files.GetCount();
		PackageFile& pf = pkg.files.Add();
		pf.path = path;
		pf.name = GetFileName(path);
		pkg.Store();
		String ext = GetFileExt(path);
		
		ClangNode& pkg_node = cache.GetPackage(pkg.name);
		ClangNode& file = NodeGetFile(pkg_node, GetFileName(path));
		cache.LoadFileNode(path, file);
		cache.StoreThis();
		/*
		if (ext==".c" || ext==".cpp" || ext==".h")
			prj.GetTranslator().AddUnit(path, prj.GetTopFolders());
		*/
		RefreshFiles();
		this->files.SetCursor(id);
	}
}



void NavigatorCtrl::RefreshFiles() {
	ProjectManager& pman = GetProjectManager();
	
	Project& prj = ide->GetProject();
	Assembly& a = prj.GetOpenAssembly();
	Package&  p = prj.GetOpenPackage();
	
	LOG(a.name);
	LOG(p.name);
	
	ClearBlocks();
	
	Vector<String> use_list = prj.GetUseList();
	
	for(int i = 0; i < use_list.GetCount(); i++) {
		AddBlock(use_list[i]);
	}
	
}


String NavigatorCtrl::GetCurrentPackageName() {
	int cur = blocks.GetCursor();
	if (cur < 0 || cur >= blocks.GetCount())
		return "";
	
	return blocks.Get(cur);
}



void NavigatorCtrl::SetLine(int line) {
	this->line = line;
	int c1 = references.GetCount();
	for(int i = 0; i < c1; i++) {
		if ((int)references.Get(i, 1) <= line) {
			references.SetCursor(i);
			break;
		}
	}
}

void NavigatorCtrl::SetFile(const String& path) {
	Project& prj = ide->GetProject();
	Array<Translation::Cursor> cursors = prj.GetTranslator().GetRootCursors(path);
	references.Clear();
	int c1 = cursors.GetCount();
	references.Add("cursor-count", c1);
	for(int i = 0; i < c1; i++) {
		Translation::Cursor& a = cursors[i];
		Translation::Type at = a.GetType();
		String arg = "cursor-" + IntStr(i);
		references.Add(arg + "-type-kind", at.GetKind());
		references.Add(arg + "-type-name", at.GetName());
		references.Add(arg + "-name", a.GetName());
		references.Add(arg + "-display-name", a.GetDisplayName());
	}
}
