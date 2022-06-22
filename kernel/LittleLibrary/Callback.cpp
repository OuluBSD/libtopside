#include "LittleLibrary.h"



CallbackBase::CallbackBase(void) {
}

CallbackBase::~CallbackBase(void) {
}

void CallbackBase::Execute(void) {
}

CallbackBase* CallbackBase::Clone(void) const {
    return (CallbackBase*) new CallbackBase;
}

callback::callback(void (*pFunction)(void)) {
    pFun = pFunction;
}

callback::~callback(void) {
    pFun = 0;
}

void callback::Execute(void) {
    (*pFun)();
}

CallbackBase* callback::Clone(void) const {
    return (CallbackBase*) new callback(pFun);
}

// ******************* start CbVoid **********************

CbVoidFO::CbVoidFO(void) {
    pCB = new CallbackBase();
}

CbVoidFO::CbVoidFO(const CallbackBase &rCB) {
    pCB = rCB.Clone();
}

CbVoidFO::CbVoidFO(const CbVoidFO &rhs) {
    pCB = (rhs.pCB)->Clone();
}

CbVoidFO::~CbVoidFO(void) {
    delete pCB;
    pCB = 0;
}

void CbVoidFO::operator()(void) const {
    pCB->Execute();
}

void CbVoidFO::Reset(void) {
    delete pCB;
    pCB = new CallbackBase();
}

void CbVoidFO::Assign(const CallbackBase &rCB) {
    delete pCB;
    pCB = rCB.Clone();
}

CallbackBase* CbVoidFO::CloneCurrentCallback(void) const {
    return pCB->Clone();
}