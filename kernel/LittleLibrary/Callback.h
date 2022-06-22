#ifndef _LittleLibrary_Callback_h_
#define _LittleLibrary_Callback_h_

// Based on public domain library libCb by John Culp.



//function object plugin
class CallbackBase {
public:
    CallbackBase(void);
    virtual ~CallbackBase(void);

    virtual void Execute(void);

    virtual CallbackBase* Clone(void) const;
};

template <class T>
class CALLBACK : public CallbackBase {
public:
    CALLBACK(T* pObject, void (T::*pFunction)(void) ) :
        CallbackBase(), pObj(pObject), pFun(pFunction) {};
    virtual ~CALLBACK(void) {};

    virtual void Execute(void) {
        (pObj->*pFun)();
    }

    virtual CallbackBase* Clone(void) const {
        return (CallbackBase*) new CALLBACK<T>(pObj, pFun);
    }

private:
    T* pObj;
    void (T::*pFun)(void);
};

template <class T, class OBJ>
class CALLBACK1 : public CallbackBase {
public:
    CALLBACK1(T* pObject, void (T::*pFunction)(OBJ), OBJ tcbObj) :
        CallbackBase(), pObj(pObject), pFun(pFunction), cbObj(tcbObj) {};
    virtual ~CALLBACK1(void) {};

    virtual void Execute(void) {
        (pObj->*pFun)(cbObj);
    }

    virtual CallbackBase* Clone(void) const {
        return (CallbackBase*) new CALLBACK1<T,OBJ>(pObj, pFun, cbObj);
    }

private:
    T* pObj;
    void (T::*pFun)(OBJ);
    OBJ cbObj;
};

template <class OBJ>
class callback1 : public CallbackBase {
public:
    callback1(void (*pFunction)(OBJ), OBJ tcbObj) :
        CallbackBase(), pFun(pFunction), cbObj(tcbObj) {};
    virtual ~callback1(void) {};

    virtual void Execute(void) {
        (*pFun)(cbObj);
    };

    virtual CallbackBase* Clone(void) const {
        return (CallbackBase*) new callback1<OBJ>(pFun, cbObj);
    };

private:
    void (*pFun)(OBJ);
    OBJ cbObj;
};

class callback : public CallbackBase {
public:
    callback(void (*pFunction)(void));
    virtual ~callback(void);

    virtual void Execute(void);

    virtual CallbackBase* Clone(void) const;

private:
    void (*pFun)(void);
};

template <class ARG>
class Callback1Base {
public:
    //Callback1Base(void) {};
    virtual ~Callback1Base(void) {};

    //virtual void Execute(ARG) {};

	virtual Callback1Base<ARG>* Clone(void) {return 0;};
    /*virtual Callback1Base<ARG>* Clone(void) const {
        return (Callback1Base<ARG>*) new Callback1Base<ARG>;
    };*/
};

template <class ARG>
class Callback1Ptr {
	Callback1Base<ARG> *base;
public:
	Callback1Ptr() {base = 0;}
	bool IsNull() {return base == 0;}
	Callback1Base<ARG>& operator = (Callback1Base<ARG>& cb) {base = &cb; return cb;}
	void Execute(ARG arg) {base->Execute(arg);};
};

template <class ARG, class T>
class CallbackClass1 : public Callback1Base<ARG> {
public:
    CallbackClass1(T*pObject, void (T::*pFunction)(ARG) ) :
        Callback1Base<ARG>(), pObj(pObject), pFun(pFunction) {};
    virtual ~CallbackClass1(void) {};

    virtual void Execute(ARG arg) {
        (pObj->*pFun)(arg);
    };

    virtual Callback1Base<ARG>* Clone(void) const {
        return (Callback1Base<ARG>*) new CallbackClass1<ARG,T>(pObj, pFun);
    };

private:
    T* pObj;
    void (T::*pFun)(ARG);
};

template <class ARG, class T, class OBJ>
class CbOneMemberObj : public Callback1Base<ARG> {
public:
    CbOneMemberObj(T*pObject, void (T::*pFunction)(ARG, OBJ), OBJ tcbObj ) :
        Callback1Base<ARG>(), pObj(pObject), pFun(pFunction), cbObj(tcbObj) {};
    virtual ~CbOneMemberObj(void) {};

    virtual void Execute(ARG arg) {
        (pObj->*pFun)(arg, cbObj);
    };

    virtual Callback1Base<ARG>* Clone(void) const {
        return (Callback1Base<ARG>*) new CbOneMemberObj<ARG,T,OBJ>(pObj, pFun, cbObj);
    };

private:
    T* pObj;
    void (T::*pFun)(ARG, OBJ);
    OBJ cbObj;
};

template <class ARG>
class Callback1 : public Callback1Base<ARG> {
public:
	Callback1() {pFun = 0;}
    Callback1( void (*pFunction)(ARG arg) ) :
        Callback1Base<ARG>(), pFun(pFunction) {};
    virtual ~Callback1(void) {};

    //virtual void Execute(ARG arg) {
    void Execute(ARG arg) {
        if (!IsNull()) (*pFun)(arg);
    };

    virtual Callback1Base<ARG>* Clone(void) const {
        return (Callback1Base<ARG>*) new Callback1<ARG>(pFun);
    };
	
	Callback1<ARG>& operator = (Callback1<ARG>& src) {
		pFun = src.pFun; return *this;
	}

	Callback1<ARG>& Copy(Callback1<ARG>& src) {
		pFun = src.pFun; return *this;
	}
	
	bool IsNull() {return pFun == 0;}
	void Reset() {pFun = 0;}
	
//private:
    void (*pFun)(ARG);
};

class CbVoidFO { //funcion object callback object
public:
    CbVoidFO(void);
    CbVoidFO(const CallbackBase &rCB);
    CbVoidFO(const CbVoidFO &rhs);
    ~CbVoidFO(void);

    void operator()(void) const;
    void Reset(void); //add to others.
    void Assign(const CallbackBase &rCB);
    CallbackBase* CloneCurrentCallback(void) const; //add to others

private:
    CallbackBase *pCB;
};

template <class ARG>
class CbOneFO { //callback object
public:
    CbOneFO(void) {
        pCB = new Callback1Base<ARG>;
    };
    CbOneFO(const Callback1Base<ARG> &rCB) {
        pCB = rCB.Clone();
    };
    CbOneFO(const CbOneFO<ARG> &rhs) {
        pCB = rhs.pCB->Clone();
    };
    ~CbOneFO(void) {
        delete pCB;
        pCB = 0;
    };

    void operator()(ARG arg1) const {
        pCB->Execute(arg1);
    };

    void Assign(const Callback1Base<ARG> &rCB) {
        delete pCB;
        pCB = rCB.Clone();
    };

private:
    Callback1Base<ARG>* pCB;
};

template <class ARG1, class ARG2>
class CbTwoBase {
public:
    CbTwoBase(void) {};
    virtual ~CbTwoBase(void) {};

    virtual CbTwoBase* Clone(void) const {
        return new CbTwoBase;
    };

    virtual void Execute(ARG1, ARG2) {};
};

template <class ARG1, class ARG2>
class CbTwoPlain : public CbTwoBase<ARG1, ARG2> {
public:
    CbTwoPlain( void(*ptFun)(ARG1 arg1, ARG2 arg2) ) :
        CbTwoBase<ARG1,ARG2>(), pFun(ptFun) {
    };
    virtual ~CbTwoPlain(void) {};

    virtual CbTwoBase<ARG1,ARG2>* Clone(void) const {
        return (CbTwoBase<ARG1,ARG2>*) new CbTwoPlain<ARG1,ARG2>(pFun);
    };

    virtual void Execute(ARG1 arg1, ARG2 arg2) {
        *pFun(arg1,arg2);
    };
private:
    void (*pFun)(void);
};

template <class ARG1, class ARG2, class T>
class CbTwoMember : public CbTwoBase<ARG1, ARG2> {
public:
    CbTwoMember(T* pObject, void (T::*ptFun)(ARG1, ARG2) ) :
        CbTwoBase<ARG1,ARG2>(), pObj(pObject), pFun(ptFun) {
    };
    virtual ~CbTwoMember(void) {};

    virtual CbTwoBase<ARG1,ARG2>* Clone(void) const {
        return (CbTwoBase<ARG1,ARG2>*) new CbTwoMember<ARG1,ARG2,T>(pObj, pFun);
    };

    virtual void Execute(ARG1 arg1, ARG2 arg2) {
        (pObj->*pFun)(arg1, arg2);
    };

private:
    T *pObj;
    void(T::*pFun)(ARG1, ARG2);
};

template <class ARG1, class ARG2>
class CbTwoFO { //a callback
public:
    CbTwoFO(void) {
        pCB = new CbTwoBase<ARG1, ARG2>;
    };
    CbTwoFO(const CbTwoBase<ARG1,ARG2> &rCB) {
        pCB = rCB.Clone();
    };
    ~CbTwoFO(void) {
        delete pCB;
        pCB = 0;
    };

    void operator()(ARG1 arg1, ARG2 arg2) const {
        pCB->Execute(arg1, arg2);
    };
    void Assign(const CbTwoBase<ARG1,ARG2> &newCB) {
        delete pCB;
        pCB = newCB.Clone();
    };

private:
    CbTwoBase<ARG1,ARG2> *pCB;
};



#endif
