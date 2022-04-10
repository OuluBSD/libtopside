// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IWebcam_BaseClasses_h_
#define _IWebcam_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct CamWebcam : public Atom {
	RTTI_DECL1(CamWebcam, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~CamWebcam() {}

};

NAMESPACE_PARALLEL_END



#endif

