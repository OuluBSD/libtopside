#ifndef _ShaderViewer_ShaderViewer_h_
#define _ShaderViewer_ShaderViewer_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Oulu;

NAMESPACE_OULU_BEGIN


class ShaderViewer :
	public Component<ShaderViewer>
{
	EntityRef fusion;
	FusionContextComponentRef ctx;
	
public:
	VIS_COMP_0_0
	typedef ShaderViewer CLASSNAME;
	ShaderViewer() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & fusion & ctx;}
	void operator=(const ShaderViewer& t) {Panic("Can't copy ShaderViewer");}
	
};


NAMESPACE_OULU_END

#endif
