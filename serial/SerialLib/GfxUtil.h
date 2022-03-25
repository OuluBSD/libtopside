#ifndef _SerialLib_GfxUtil_h_
#define _SerialLib_GfxUtil_h_


#ifdef flagSCREEN

NAMESPACE_SERIAL_BEGIN


template <class Gfx>
class BufferBaseT :
	public AtomBase
{
	
protected:
	using Buffer = typename Gfx::Buffer;
	Buffer buf;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	
	void Visit(RuntimeVisitor& vis) override {vis % buf;}
	void Update(double dt) override {buf.Update(dt);}
	
	Buffer& GetBuffer() {return buf;}
	
};


NAMESPACE_SERIAL_END


#endif
#endif
