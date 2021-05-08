#ifndef _OrchestraConductor_OrchestraConductor_h_
#define _OrchestraConductor_OrchestraConductor_h_

#include <Complete/Complete.h>
#include <FusionCore/FusionCore.h>
#include <AudioCore/System.h>
#include <Music/Music.h>
#include <EscAlt/Esc.h>
using namespace Oulu;

NAMESPACE_OULU_BEGIN


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


NAMESPACE_OULU_END

#endif
