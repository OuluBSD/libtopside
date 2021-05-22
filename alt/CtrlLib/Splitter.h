#ifndef _CtrlLibAlt_Splitter_h_
#define _CtrlLibAlt_Splitter_h_

NAMESPACE_UPP


class Splitter : public Ctrl {
	
	
public:
	RTTI_DECL1(Splitter, Ctrl)
	Splitter();
	
	
	Splitter& Add(Ctrl& c);
	Splitter& Vert();
	Splitter& Horz();
	Splitter& SetPos(int i);
	
	void Clear();
	
	Splitter& operator << (Ctrl& c) {return Add(c);}
	
};


END_UPP_NAMESPACE

#endif
