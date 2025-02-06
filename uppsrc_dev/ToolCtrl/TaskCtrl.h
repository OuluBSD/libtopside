#ifndef _ToolCtrl_TaskCtrl_h_
#define _ToolCtrl_TaskCtrl_h_


BEGIN_TEXTLIB_NAMESPACE


class Tasks : public Ctrl {
	Splitter hsplit, vsplit;
	ArrayCtrl list;
	DocEdit input, output;
	#if 0
	ProgressIndicator prog;
	Label lbl;
	#endif
	int data_cursor = -1;
	
public:
	typedef Tasks CLASSNAME;
	Tasks();
	
	void Data();
	void DataTask();
	void ToolMenu(Bar& bar) {}
	void ValueChange();
	void ProcessItem();
	void ReturnFail();
	void RetryItem(bool skip_prompt, bool skip_cache);
	void OutputMenu(Bar& bar);
	
};


END_TEXTLIB_NAMESPACE


#endif
