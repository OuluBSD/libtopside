#ifndef _SerialLib_OglUtil_h_
#define _SerialLib_OglUtil_h_


#ifdef flagGUI

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
#endif
