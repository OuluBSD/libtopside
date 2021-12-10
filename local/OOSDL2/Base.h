#ifndef _OOSDL2_Base_h_
#define _OOSDL2_Base_h_

NAMESPACE_SDL2_BEGIN


class Context;


class Stateful :
	RTTIBase
{
	RTTI_DECL0(Stateful)
	
protected:
	bool is_open = false;
	
	virtual bool Open0() = 0;
	virtual void Close0() = 0;
	
public:
	Stateful() = default;
	virtual ~Stateful() {/*deleted inheritance crash: Close();*/ ASSERT(!is_open); }
	
	bool Open() {if (!is_open && Open0()) is_open = true; return is_open;}
	void Close() {if (is_open) Close0(); is_open = false;}
	bool IsOpen() const {return is_open;}
	
};

class Component :
	public Stateful
{
	RTTI_DECL1(Component, Stateful)
	
protected:
	friend class Context;
	Context* ctx = 0;
	AtomBase* ab = 0;
	
	virtual uint32 GetInitFlag() const = 0;
	
public:
	Component(Context* ctx, AtomBase* ab) : ctx(ctx), ab(ab) {}
	
	Context*		GetContext() const {return ctx;}
	AtomBase*		GetAtomBase() const {return ab;}
	PacketBuffer&	GetSinkBuffer();
	
};


NAMESPACE_SDL2_END

#endif
