// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IAvFile_BaseClasses_h_
#define _IAvFile_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct AVAVFile : public Atom {
	RTTI_DECL1(AVAVFile, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~AVAVFile() {}

};

NAMESPACE_PARALLEL_END



#endif

