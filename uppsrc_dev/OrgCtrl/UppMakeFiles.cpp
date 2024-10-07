#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


void UppExporterView::MakeFiles() {
	String ass_dir = node->data.GetAdd("assembly");
	String name = node->data.GetAdd("main-package");
	
	if (ass_dir.IsEmpty() || name.IsEmpty())
		return;
	
	Node& prj_file = *node->owner;
	RealizeDirectory(ass_dir);
	
	Init(prj_file, org);
	Data();
	
	String main_pkg = name;
	UppProject& main_prj = data.RealizeProject(main_pkg);
	main_prj.ClearContent();
	main_prj.GetAddConfig("");
	main_prj.FindAddFile(main_pkg + ".h");
	main_prj.FindAddFile(main_pkg + ".cpp");
	main_prj.Store(); // required at this point already
	
	Vector<Node*> packages;
	prj_file.FindChildDeep(packages, NODE_PACKAGE);
	
	CppFileWriter writer;
	
	VectorMap<String,int> use_counts;
	
	for (Node* pkg_ptr : packages) {
		Node& pkg = *pkg_ptr;
		String pkg_name = pkg.name;
		String h_name = pkg_name + ".h";
		String cpp_name = pkg_name + ".cpp";
		ASSERT(pkg_name.GetCount());
		
		String pkg_dir = pkg.GetPathFrom(prj_file);
		String full_pkg_name = pkg_dir + pkg_name;
		
		ValueArray& includes = ValueToArray(pkg.data.GetAdd("includes"));
		Vector<String> inc_strs;
		for(int i = 0; i < includes.GetCount(); i++)
			inc_strs.Add(includes[i]);
		
		ValueArray& pkg_deps = ValueToArray(pkg.data.GetAdd("deps"));
		
		UppProject& upp_prj = data.RealizeProject(full_pkg_name);
		
		if (&upp_prj != &main_prj) {
			upp_prj.ClearContent();
			upp_prj.AddFile(h_name);
			upp_prj.AddFile(cpp_name);
			use_counts.GetAdd(full_pkg_name,0);
			for(int i = 0; i < pkg_deps.GetCount(); i++) {
				String dep = pkg_deps[i];
				upp_prj.AddUse(dep);
				use_counts.GetAdd(dep,0)++;
			}
		}
		
		String dir = upp_prj.GetDirectory();
		RealizeDirectory(dir);
		String h_path = AppendFileName(dir, h_name);
		String cpp_path = AppendFileName(dir, cpp_name);
		writer.WriteHeader(pkg, h_path, inc_strs);
		writer.WriteImplementation(pkg, cpp_path, h_name);
		
		String prj_dir = AppendFileName(ass_dir, full_pkg_name);
		
		Vector<Node*> classes;
		pkg.FindChildDeep(classes, NODE_CLASS);
		
		for(int i = 0; i < classes.GetCount(); i++) {
			Node& cls = *classes[i];
			
			// TODO find class path
			
			String cls_name = cls.name;
			ASSERT(!cls_name.IsEmpty());
			if (cls_name == pkg_name)
				cls_name += "_";
			
			String h_file = cls_name + ".h";
			String cpp_file = cls_name + ".cpp";
			upp_prj.FindAddFile(h_file);
			upp_prj.FindAddFile(cpp_file);
			
			String h_path = AppendFileName(prj_dir, h_file);
			String cpp_path = AppendFileName(prj_dir, cpp_file);
			
			writer.WriteHeader(cls, h_path, Vector<String>());
			writer.WriteImplementation(cls, cpp_path, h_name);
		}
		
		upp_prj.Store();
	}
	
	for(int i = 0; i < use_counts.GetCount(); i++) {
		if (use_counts[i] > 0) continue;
		String pkg_name = use_counts.GetKey(i);
		main_prj.AddUse(pkg_name);
	}
	main_prj.Store();
	//WhenTree();
}

void UppExporterCtrl::OnTreeChange() {
	if (org)
		PostCallback(callback(org, &OrganizationCtrl::Data));
}


END_TEXTLIB_NAMESPACE
