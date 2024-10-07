#ifndef _OrgCtrl_FileListNode_h_
#define _OrgCtrl_FileListNode_h_

BEGIN_TEXTLIB_NAMESPACE


class FileListView : public NodeViewBase {
	
public:
	typedef FileListView CLASSNAME;
	FileListView();
	
	void Data() override;
	
};

class FileListCtrl : public NodeCtrlBase {
	Splitter hsplit;
	ArrayCtrl files;
	WithFileList<Ctrl> form;
	
	enum {
		ADD_FILE,
		REM_FILE,
		SET_FILES,
	};
public:
	typedef FileListCtrl CLASSNAME;
	FileListCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	void ToolMenu(Bar& bar) override;
	
};



END_TEXTLIB_NAMESPACE

#endif
