#ifndef _SerialLib_GfxUtil_h_
#define _SerialLib_GfxUtil_h_


#ifdef flagSCREEN

NAMESPACE_SERIAL_BEGIN


class OglBufferBase :
	virtual public AtomBase
{
	
protected:
	SdlOglBuffer		buf;
	
	
public:
	
	void Visit(RuntimeVisitor& vis) override {vis % buf;}
	void			Update(double dt) override {buf.Update(dt);}
	
	SdlOglBuffer&		GetBuffer() {return buf;}
	
};


class CpuBufferBase :
	virtual public AtomBase
{
	
protected:
	SdlCpuBuffer		buf;
	
	
public:
	
	void Visit(RuntimeVisitor& vis) override {vis % buf;}
	void			Update(double dt) override {buf.Update(dt);}
	
	SdlCpuBuffer&		GetBuffer() {return buf;}
	
};


NAMESPACE_SERIAL_END


#endif
#endif
