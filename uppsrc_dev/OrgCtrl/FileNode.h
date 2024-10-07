#ifndef _OrgCtrl_FileNode_h_
#define _OrgCtrl_FileNode_h_


BEGIN_TEXTLIB_NAMESPACE


class FileView : public NodeViewBase {
	
public:
	typedef FileView CLASSNAME;
	FileView();
	
	void Data() override;
	
};

class FileCtrl : public NodeCtrlBase {
	Splitter hsplit;
	WithFile<Ctrl> form;
	CodeEditor edit;
	
	enum {
		GENERATE_CODE,
	};
	
public:
	typedef FileCtrl CLASSNAME;
	FileCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE


#endif
