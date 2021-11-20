#ifndef _Local_Types_h_
#define _Local_Types_h_

NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;

#undef Bool
typedef unsigned char	Bool;

typedef float			Float;
typedef float			Clamp;
typedef int				Int;
typedef unsigned int	Uint;
typedef unsigned char	Byte;
typedef void			Void;




class BinderIfaceEvents : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceEvents);
	
};


class OglBuffer;
class OglShader;

class BinderIfaceOgl : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceOgl);
	
	virtual void Render(const OglBuffer& buf, OglShader& shader) = 0;
	
};


NAMESPACE_TOPSIDE_END

#endif
