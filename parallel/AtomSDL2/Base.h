#ifndef _AtomSDL2_Base_h_
#define _AtomSDL2_Base_h_


NAMESPACE_SERIAL_BEGIN


class SDL2Base :
	public AtomBase
{
	
public:
	RTTI_DECL0(SDL2Base); // skip AtomBase
	void Visit(RuntimeVisitor& vis) override {/* skip AtomBase */}
	
	virtual OOSDL2::Component& GetObj() = 0;
	
};


template <class T>
class SDL2BaseT :
	public SDL2Base
{
	
public:
	using AltBaseT = SDL2BaseT<T>;
	
	RTTI_DECL1(SDL2BaseT<T>, SDL2Base);
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<SDL2Base>(this);}
	
};


NAMESPACE_SERIAL_END

#endif
