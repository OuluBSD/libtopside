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
	FusionContextComponent* ctx = 0;
	
public:
	typedef ShaderViewer CLASSNAME;
	ShaderViewer() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void operator=(const ShaderViewer& t) {Panic("Can't copy ShaderViewer");}
	
};


NAMESPACE_OULU_END

#endif
