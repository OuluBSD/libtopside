// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

#ifndef _IMidiFile_BaseClasses_h_
#define _IMidiFile_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct MifMidiFile : public Atom {
	RTTI_DECL1(MifMidiFile, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~MifMidiFile() {}

};

NAMESPACE_PARALLEL_END



#endif

