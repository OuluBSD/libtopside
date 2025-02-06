#ifndef _OrgCtrl_UppExporter_h_
#define _OrgCtrl_UppExporter_h_


BEGIN_TEXTLIB_NAMESPACE


class UppExporterView : public NodeViewBase {
	
public:
	typedef UppExporterView CLASSNAME;
	UppExporterView();
	
	void Data() override;
	
	void Clear();
	void ReadFiles();
	void MakeFiles();
	
	
	UppAssembly assembly;
	UppAssemblyData data;
	UppAssemblyCache cache;
	UppProject* main_prj = 0;
	
	Event<> WhenTree;
	
};

class UppExporterCtrl : public NodeCtrlBase {
	Splitter hsplit, vsplit;
	WithUppExporter<Ctrl> form;
	ArrayCtrl pkgs, files;
	CodeEditor edit;
	Index<String> pkg_list;
	
	enum {
		MAKE_FILES,
		UPDATE_FILES,
		EXPORT_CODE,
		REM_FILE,
	};
	
public:
	typedef UppExporterCtrl CLASSNAME;
	UppExporterCtrl();
	
	void Data() override;
	void DataPkg();
	void DataFile();
	void ToolMenu(Bar& bar) override;
	void OnValueChange();
	void Do(int fn);
	void OnTreeChange();
	
	
};



END_TEXTLIB_NAMESPACE


#endif
