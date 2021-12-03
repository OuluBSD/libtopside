#ifndef _Graphics06a_Tutorial6a_h_
#define _Graphics06a_Tutorial6a_h_

#include <EcsComplete/EcsComplete.h>
#include <AccelCore/AccelCore.h>
using namespace TS;
using namespace TS::Ecs;

NAMESPACE_TOPSIDE_BEGIN

struct Tutorial6a :
	public Component<Tutorial6a>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial6a, ComponentT, BinderIfaceVideo)
	
	NS_SHADER::MultiStage ms;
	bool fail = false;
	
	
	Graphics6a() {}
	void Initialize() override;
	void operator=(const Graphics6a& t) {Panic("Can't copy Graphics6a");}
	
	void Render(Draw& draw) override;
	
};

NAMESPACE_TOPSIDE_END

#endif
