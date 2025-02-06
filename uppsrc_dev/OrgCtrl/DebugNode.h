#ifndef _OrgCtrl_DebugNode_h_
#define _OrgCtrl_DebugNode_h_

BEGIN_TEXTLIB_NAMESPACE


class DebugView : public NodeViewBase {
	
public:
	typedef DebugView CLASSNAME;
	DebugView();
	
	void Data() override;
	
};

class DebugCtrl : public NodeCtrlBase {
	ArrayCtrl types, items, subitems0, subitems1, subitems2, subitems3;
	Splitter hsplit;
	
	VectorMap<String, Event<>> type_cbs;
	Vector<Event<int&>> count_cbs;
	Vector<Event<>> item_cbs;
	Vector<Event<>> subitem0_cbs;
	Vector<Event<>> subitem1_cbs;
	Vector<Event<>> subitem2_cbs;
	Vector<Event<>> subitem3_cbs;
	
public:
	typedef DebugCtrl CLASSNAME;
	DebugCtrl();
	
	void Data() override;
	void RegisterTypes();
	void DataType();
	void DataItem();
	void DataSubItem0();
	void DataSubItem1();
	void DataSubItem2();
	void DataSubItem3();
	void OnValueChange();
	void ToolMenu(Bar& bar) override;
	void Do(int fn);
	
	template <class T> void SubItem0_Lang(T& o);
	template <class T> void SubItem0(T& o);
	template <> void SubItem0(HardPlatform& o);
	template <class T> void SubItem1(T& o);
	template <> void SubItem1(HardPlatform::Lang& o);
	template <class T> void SubItem2(T& o);
	template <> void SubItem2(HardPlatform& o);
	template <class T> void RegisterType(Array<T>& array, String name);
	
};



END_TEXTLIB_NAMESPACE

#endif
