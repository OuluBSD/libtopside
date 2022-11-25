#ifndef _SharedCore_Ctrl_h_
#define _SharedCore_Ctrl_h_


NAMESPACE_UPP


class Ctrl;
class AbsoluteWindowProxy;

class AbsoluteWindowInterface : RTTIBase {
	
protected:
	friend class AbsoluteWindowProxy;
	AbsoluteWindowProxy* proxy = 0;
	
	
public:
	RTTI_DECL0(AbsoluteWindowInterface)
	typedef AbsoluteWindowInterface CLASSNAME;
	AbsoluteWindowInterface();
	virtual ~AbsoluteWindowInterface() {}
	
	virtual void							Title(const String& title) = 0;
	virtual AbsoluteWindowInterface&		Sizeable(bool b=true) = 0;
	virtual AbsoluteWindowInterface&		MaximizeBox(bool b=true) = 0;
	virtual AbsoluteWindowInterface&		MinimizeBox(bool b=true) = 0;
	virtual int								Run(bool appmodal=false) = 0;
	
	virtual Ctrl*							GetWindowCtrl();
	
	virtual String			GetTitle();
	
	virtual void			Start() {}
	virtual void			CloseWindow() {}
	virtual void			RefreshData() {};
	virtual void			FocusEvent() {}
	
};


class AbsoluteWindowProxy : public AbsoluteWindowInterface {
	AbsoluteWindowInterface* o = 0;
	
public:
	RTTI_DECL1(AbsoluteWindowProxy, AbsoluteWindowInterface)
	typedef AbsoluteWindowProxy CLASSNAME;
	AbsoluteWindowProxy();
	
	void SetTarget(AbsoluteWindowInterface&);
	
	virtual void							Title(const String& title) override {o->Title(title);}
	virtual AbsoluteWindowInterface&		Sizeable(bool b=true) override {o->Sizeable(b); return *this;}
	virtual AbsoluteWindowInterface&		MaximizeBox(bool b=true) override {o->MaximizeBox(b); return *this;}
	virtual AbsoluteWindowInterface&		MinimizeBox(bool b=true) override {o->MinimizeBox(b); return *this;}
	virtual int								Run(bool appmodal=false) override {return o->Run(appmodal);}
	
	virtual String			GetTitle() override {return o->GetTitle();}
	
	virtual void			Start() override {o->Start();}
	virtual void			CloseWindow() override {o->CloseWindow();}
	virtual void			RefreshData() override {o->RefreshData();};
	virtual void			FocusEvent() override {o->FocusEvent();}
	
	
};


END_UPP_NAMESPACE


#endif
