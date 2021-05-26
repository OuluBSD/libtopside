#ifndef _OrchestraConductor_OrchestraConductor_h_
#define _OrchestraConductor_OrchestraConductor_h_

#include <Complete/Complete.h>
#include <AccelCore/AccelCore.h>
#include <AudioCore/System.h>
#include <Music/Music.h>
using namespace Topside;

NAMESPACE_TOPSIDE_BEGIN


class OrchestraConductor :
	public Component<OrchestraConductor>
{
	
public:
	typedef OrchestraConductor CLASSNAME;
	OrchestraConductor() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	COPY_PANIC(OrchestraConductor);
	
};


NAMESPACE_TOPSIDE_END

#endif
