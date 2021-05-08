#ifndef _Graphics06a_Tutorial6a_h_
#define _Graphics06a_Tutorial6a_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
using namespace Oulu;

NAMESPACE_OULU_BEGIN

struct Graphics6a : public Component<Graphics6a>, public DisplaySink {
	NS_SHADER::MultiStage ms;
	bool fail = false;
	
	
	IFACE_CB(DisplaySink);
	IFACE_GENERIC;
	
	Graphics6a() {}
	void Initialize() override;
	void operator=(const Graphics6a& t) {Panic("Can't copy Graphics6a");}
	void Visit(RuntimeVisitor& vis) override {}
	
	void Render(SystemDraw& draw) override;
	
};

NAMESPACE_OULU_END

#endif
