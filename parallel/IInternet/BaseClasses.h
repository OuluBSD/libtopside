// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.6 0:00:44

#ifndef _IInternet_BaseClasses_h_
#define _IInternet_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct NetSocket : public Atom {
	RTTI_DECL1(NetSocket, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~NetSocket() {}

};

NAMESPACE_PARALLEL_END



#endif

