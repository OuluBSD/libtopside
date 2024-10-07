#ifndef _ToolBase_ChecklistComposition_h_
#define _ToolBase_ChecklistComposition_h_

#if 0


BEGIN_TEXTLIB_NAMESPACE


class ChecklistBase : public ToolAppCtrl {
	ArrayCtrl list;
	Vector<Option*> opts;
	Vector<EditString*> edits;
	
	void Init();
	
protected:
	Vector<String> descs;
	Vector<String> keys;
	
public:
	typedef ChecklistBase CLASSNAME;
	ChecklistBase();
	
	void Data();
	void OnOptionChange(int i);
	void OnValueChange(int i);
	virtual void InitKeys() = 0;
	
};


END_TEXTLIB_NAMESPACE


#endif
#endif
