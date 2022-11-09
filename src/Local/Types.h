#ifndef _Local_Types_h_
#define _Local_Types_h_

NAMESPACE_UPP

class Draw;

END_UPP_NAMESPACE



NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;

#undef Bool
typedef unsigned char	Bool;

typedef float			Float;
//typedef float			Clamp;
typedef int				Int;
typedef unsigned int	Uint;
typedef unsigned char	Byte;
typedef void			Void;

typedef float			TimeSpan;

class RuntimeVisitor;
class EnvState;


class BinderIfaceEvents : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceEvents);
	virtual ~BinderIfaceEvents() {}
	
	virtual void Dispatch(const CtrlEvent& state) = 0;
	
};


class BinderIfaceVideo : RTTIBase {
	
public:
	RTTI_DECL0(BinderIfaceVideo);
	BinderIfaceVideo();
	virtual ~BinderIfaceVideo() {}
	
	virtual bool Render(Draw& d) = 0;
	virtual bool Arg(const String& key, const String& value) = 0;
	
	virtual void Initialize() {}
	virtual void Uninitialize() {}
	virtual void Visit(RuntimeVisitor& vis) {}
	
};


/*class CpuBuffer;
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
	
};*/


NAMESPACE_TOPSIDE_END

#endif
