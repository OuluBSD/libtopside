#ifndef _ShaderViewer_ShaderViewer_h_
#define _ShaderViewer_ShaderViewer_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Topside;

NAMESPACE_TOPSIDE_BEGIN


class ShaderViewer :
	public Component<ShaderViewer>
{
	EntityRef fusion;
	FusionContextComponentRef ctx;
	
public:
	RTTI_COMP0(ShaderViewer)
	VIS_COMP_0_0
	typedef ShaderViewer CLASSNAME;
	ShaderViewer() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & fusion & ctx;}
	void operator=(const ShaderViewer& t) {Panic("Can't copy ShaderViewer");}
	
};


NAMESPACE_TOPSIDE_END

#endif
