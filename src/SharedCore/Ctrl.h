#ifndef _SharedCore_Ctrl_h_
#define _SharedCore_Ctrl_h_


NAMESPACE_UPP


class Ctrl;
class Gubo;
class Absolute2DProxy;
class Absolute3DProxy;


class AbsoluteInterface : RTTIBase {
	
public:
	RTTI_DECL0(AbsoluteInterface)
	
	virtual void					Title(const String& title) = 0;
	virtual AbsoluteInterface&		Sizeable(bool b=true) = 0;
	virtual AbsoluteInterface&		MaximizeBox(bool b=true) = 0;
	virtual AbsoluteInterface&		MinimizeBox(bool b=true) = 0;
	virtual int						Run(bool appmodal=false) = 0;
	virtual void					SetPendingPartialRedraw() = 0;
	virtual String					GetTitle() const = 0;
	
	virtual void					Start() {}
	virtual void					Close() {}
	virtual void					RefreshData() {}
	virtual void					FocusEvent() {}
	
	
};

class Absolute2DInterface : public AbsoluteInterface {
	
protected:
	friend class Absolute2DProxy;
	Absolute2DProxy* proxy = 0;
	
	
public:
	RTTI_DECL1(Absolute2DInterface, AbsoluteInterface)
	typedef Absolute2DInterface CLASSNAME;
	Absolute2DInterface() {}
	virtual ~Absolute2DInterface() {}
	
	virtual Ctrl*					GetCtrl();
	
	Absolute2DProxy*				GetLinkedProxy() const {return proxy;}
	
};


class Absolute3DInterface : public AbsoluteInterface {
	
protected:
	friend class Absolute3DProxy;
	Absolute3DProxy* proxy = 0;
	
	
public:
	RTTI_DECL1(Absolute3DInterface, AbsoluteInterface)
	typedef Absolute3DInterface CLASSNAME;
	Absolute3DInterface() {}
	virtual ~Absolute3DInterface() {}
	
	virtual Gubo*					GetGubo();
	
	Absolute3DProxy*				GetLinkedProxy() const {return proxy;}
	
};

class Absolute2DProxy : public Absolute2DInterface {
	Absolute2DInterface* o = 0;
	
public:
	RTTI_DECL1(Absolute2DProxy, Absolute2DInterface)
	typedef Absolute2DProxy CLASSNAME;
	Absolute2DProxy() {}
	
	void SetTarget(Absolute2DInterface&);
	Absolute2DInterface* GetTarget() const {return o;}
	
	void						Title(const String& title) override {ASSERT(o); o->Title(title);}
	Absolute2DInterface&		Sizeable(bool b=true) override {ASSERT(o); o->Sizeable(b); return *this;}
	Absolute2DInterface&		MaximizeBox(bool b=true) override {ASSERT(o); o->MaximizeBox(b); return *this;}
	Absolute2DInterface&		MinimizeBox(bool b=true) override {ASSERT(o); o->MinimizeBox(b); return *this;}
	int							Run(bool appmodal=false) override {ASSERT(o); return o->Run(appmodal);}
	void						SetPendingPartialRedraw() override {ASSERT(o); o->SetPendingPartialRedraw();}
	
	String			GetTitle() const override {ASSERT(o); return o->GetTitle();}
	
	void			Start() override {ASSERT(o); o->Start();}
	void			Close() override {ASSERT(o); o->Close();}
	void			RefreshData() override {ASSERT(o); o->RefreshData();};
	void			FocusEvent() override {ASSERT(o); o->FocusEvent();}
	
	
};

class Absolute3DProxy : public Absolute3DInterface {
	Absolute3DInterface* o = 0;
	
public:
	RTTI_DECL1(Absolute3DProxy, Absolute3DInterface)
	typedef Absolute3DProxy CLASSNAME;
	Absolute3DProxy() {}
	
	void SetTarget(Absolute3DInterface&);
	Absolute3DInterface* GetTarget() const {return o;}
	
	void						Title(const String& title) override {ASSERT(o); o->Title(title);}
	Absolute3DInterface&		Sizeable(bool b=true) override {ASSERT(o); o->Sizeable(b); return *this;}
	Absolute3DInterface&		MaximizeBox(bool b=true) override {ASSERT(o); o->MaximizeBox(b); return *this;}
	Absolute3DInterface&		MinimizeBox(bool b=true) override {ASSERT(o); o->MinimizeBox(b); return *this;}
	int							Run(bool appmodal=false) override {ASSERT(o); return o->Run(appmodal);}
	void						SetPendingPartialRedraw() override {ASSERT(o); o->SetPendingPartialRedraw();}
	
	String			GetTitle() const override {ASSERT(o); return o->GetTitle();}
	
	void			Start() override {ASSERT(o); o->Start();}
	void			Close() override {ASSERT(o); o->Close();}
	void			RefreshData() override {ASSERT(o); o->RefreshData();};
	void			FocusEvent() override {ASSERT(o); o->FocusEvent();}
	
	
};


END_UPP_NAMESPACE


#endif
