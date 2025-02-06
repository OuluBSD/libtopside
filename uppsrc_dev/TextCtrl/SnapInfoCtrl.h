#ifndef _TextCtrl_SnapInfoCtrl_h_
#define _TextCtrl_SnapInfoCtrl_h_


BEGIN_TEXTLIB_NAMESPACE


class ToolEditor;

class SnapInfoCtrl : public WithSnapshotInfo<ToolAppCtrl> {
	
	
public:
	typedef SnapInfoCtrl CLASSNAME;
	SnapInfoCtrl();
	
	void Data();
	void Clear();
	void OnValueChange();
	
};


END_TEXTLIB_NAMESPACE


#endif
