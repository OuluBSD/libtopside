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


class BinderIfaceVideo : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceVideo);
	
	virtual void Render(Draw& draw) = 0;
	
};


class CpuBuffer;
class CpuShader;

class BinderIfaceCpu : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceCpu);
	
	virtual void Render(const CpuBuffer& buf, CpuShader& shader) = 0;
	
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
