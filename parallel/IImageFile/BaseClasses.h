// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IImageFile_BaseClasses_h_
#define _IImageFile_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct ImgImage : public Atom {
	RTTI_DECL1(ImgImage, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~ImgImage() {}

};

NAMESPACE_PARALLEL_END



#endif

