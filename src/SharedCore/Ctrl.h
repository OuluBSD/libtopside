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
	AbsoluteWindowInterface() {}
	virtual ~AbsoluteWindowInterface() {}
	
	virtual void							Title(const String& title) = 0;
	virtual AbsoluteWindowInterface&		Sizeable(bool b=true) = 0;
	virtual AbsoluteWindowInterface&		MaximizeBox(bool b=true) = 0;
	virtual AbsoluteWindowInterface&		MinimizeBox(bool b=true) = 0;
	virtual int								Run(bool appmodal=false) = 0;
	virtual void							SetPendingPartialRedraw() = 0;
	virtual String							GetTitle() const = 0;
	
	virtual Ctrl*							GetWindowCtrl();
	
	
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
	AbsoluteWindowProxy() {}
	
	void SetTarget(AbsoluteWindowInterface&);
	
	void							Title(const String& title) override {ASSERT(o); o->Title(title);}
	AbsoluteWindowInterface&		Sizeable(bool b=true) override {ASSERT(o); o->Sizeable(b); return *this;}
	AbsoluteWindowInterface&		MaximizeBox(bool b=true) override {ASSERT(o); o->MaximizeBox(b); return *this;}
	AbsoluteWindowInterface&		MinimizeBox(bool b=true) override {ASSERT(o); o->MinimizeBox(b); return *this;}
	int								Run(bool appmodal=false) override {ASSERT(o); return o->Run(appmodal);}
	void							SetPendingPartialRedraw() override {ASSERT(o); o->SetPendingPartialRedraw();}
	
	String			GetTitle() const override {ASSERT(o); return o->GetTitle();}
	
	void			Start() override {ASSERT(o); o->Start();}
	void			CloseWindow() override {ASSERT(o); o->CloseWindow();}
	void			RefreshData() override {ASSERT(o); o->RefreshData();};
	void			FocusEvent() override {ASSERT(o); o->FocusEvent();}
	
	
};


END_UPP_NAMESPACE


#endif
