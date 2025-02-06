#ifndef _OrgCtrl_FeaturesNode_h_
#define _OrgCtrl_FeaturesNode_h_


BEGIN_TEXTLIB_NAMESPACE


class FeaturesView : public NodeViewBase {
	
public:
	typedef FeaturesView CLASSNAME;
	FeaturesView();
	
	void Data() override;
	
};

class FeaturesCtrl : public NodeCtrlBase {
	Splitter hsplit;
	ArrayCtrl features;
	WithFeatures<Ctrl> form;
	
	enum {
		ADD_FEATURE,
		REM_FEATURE
	};
		
public:
	typedef FeaturesCtrl CLASSNAME;
	FeaturesCtrl();
	
	void Data() override;
	void OnValueChange();
	void Do(int fn);
	
};



END_TEXTLIB_NAMESPACE

#endif
