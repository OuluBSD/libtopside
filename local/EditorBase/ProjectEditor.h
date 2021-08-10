#ifndef _EditorBase_ProjectEditorExt_h_
#define _EditorBase_ProjectEditorExt_h_

NAMESPACE_TOPSIDE_BEGIN


class ProjectEditorExt : public EditorExtension {
	Splitter vsplit;
	FileList projects;
	FileList files;
	CodeEditor left, right;
	
	int editortabsize, indent_spaces, indent_amount, show_tabs, no_parenthesis_indent, hilite_scope, hilite_bracket;
	int hilite_ifdef, barline, hilite_if_endif, thousands_separator, hline, line_numbers, auto_enclose;
	int mark_lines, bordercolumn, bordercolor, persistent_find_replace, find_replace_restore_pos;
	int font_height;
	Image prj_icon;
	
	// Debugging GUI
	DocEdit left_object_tree;
	DocEdit left_node_tree;
	Splitter left_tree_split;
	String left_path, right_path;
	
	
	
	
public:
	typedef ProjectEditorExt CLASSNAME;
	ProjectEditorExt();
	~ProjectEditorExt();
	
	void Activate() override;
	void Deactivate() override;
	void Save() override {SaveFile();}
	bool HotKey(dword key) override;
	
	
	void Init();
	void InitEditor(CodeEditor& edit);
	void Data();
	void DataProjectFiles();
	void OpenSelectedFile();
	void Compile();
	void NewFile();
	void SaveFile();
	void OpenLog();
	void SetTabFile(int i, String path, int line, int col);
	
	String JoinFiles();
	
	void GoToError(const ErrorInfo& f) override;
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
