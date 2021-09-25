#ifndef _SerialLib_AccelUtil_h_
#define _SerialLib_AccelUtil_h_


NAMESPACE_SERIAL_BEGIN


class OglBufferBase :
	virtual public AtomBase
{
	
protected:
	OglBuffer		buf;
	
	
public:
	
	void Visit(RuntimeVisitor& vis) override {}
	
	
	OglBuffer&		GetBuffer() {return buf;}
	
};


NAMESPACE_SERIAL_END


#endif
