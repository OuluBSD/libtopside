#ifndef _ShaderPlayer_ShaderPlayer_h_
#define _ShaderPlayer_ShaderPlayer_h_

#include <Complete/Complete.h>
using namespace Topside;

NAMESPACE_TOPSIDE_BEGIN


class ShaderPlayer :
	public Component<ShaderPlayer>
{
	EntityRef accel;
	AccelContextComponentRef ctx;
	
public:
	RTTI_COMP0(ShaderPlayer)
	VIS_COMP_0_0
	typedef ShaderPlayer CLASSNAME;
	ShaderPlayer() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & accel & ctx;}
	void operator=(const ShaderPlayer& t) {Panic("Can't copy ShaderPlayer");}
	
};


NAMESPACE_TOPSIDE_END

#endif
