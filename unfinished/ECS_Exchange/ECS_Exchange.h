#ifndef _ECS_Exchange_ECS_Exchange_h_
#define _ECS_Exchange_ECS_Exchange_h_

#include <Complete/Complete.h>

using namespace UPP;
using namespace TS;


struct DemoMoney : public SemanticEx {
	
};

struct DemoMusic : public SemanticEx {
	
};

struct DemoFeeling : public SemanticEx {
	
};

struct DemoHuman :
	public Component<DemoHuman>,
	public OverlapSink,
	public SemanticSink,
	public SemanticSource
{
	
	
public:
	COPY_PANIC(DemoHuman)
	IFACE_GENERIC
	IFACE_CB(OverlapSink);
	IFACE_CB(SemanticSink);
	IFACE_CB(SemanticSource);
	
	typedef enum {
		CLIENT_MALE,
		CLIENT_FEMALE,
		PERSONEL_BAR,
		PERSONEL_DJ
	} Type;
	
	enum {
		ACT_GO_BAR,
			ACT_GET_BARTENDER_ATTENTION,
			ACT_TALK_TO_BARTENDER,
				ACT_ORDER_DRINK,
				ACT_PAY_DRINK,
				ACT_TAKE_DRINK,
				ACT_SAY_THANK_YOU,
			ACT_TALK_WITH_NEAREST,
		ACT_GO_DANCEFLOOR,
			ACT_DANCE_ALONE,
			ACT_GO_TO_LONELY_W,
			ACT_GO_TO_LONELY_M,
			ACT_DANCE_WITH_NEAREST,
			ACT_SHOW_INTEREST,
		ACT_GO_TOILET_M,
			ACT_DO_YOUR_BUSINESS_M,
		ACT_GO_TOILET_W,
			ACT_DO_YOUR_BUSINESS_W,
		ACT_EXIT,
		
		ACT_NOTICE_CLIENT,
		ACT_GO_TO_CLIENT,
		ACT_TALK_TO_CLIENT,
		ACT_MAKE_DRINK_FOR_CLIENT,
		ACT_TAKE_PAYMENT_FROM_CLIENT,
		
		ACT_PLAY_DANCEHITS_150BPM,
		ACT_PLAY_DANCEHITS_120BPM,
		ACT_PLAY_DANCEHITS_90BPM,
		ACT_PLAY_QUIET_BACKGROUND_MUSIC,
		
		ACT_COUNT
	};
	
	enum {
		ATOM_TALKING,
		ATOM_GOING_TO_BAR,
		ATOM_GOING_TO_TOILET,
		ATOM_GOING_TO_DANCEFLOOR,
		ATOM_GOING_OUT,
		ATOM_COUNT
	};
	
	void Init(Type type);
	
};

struct DemoRoom :
	public Component<DemoRoom>,
	public OverlapSink
{
	
	COPY_PANIC(DemoRoom);
	IFACE_GENERIC;
	IFACE_CB(OverlapSink);
};

PREFAB_BEGIN(ClientMan)
	Transform,
	DemoHuman,
	Overlap,
	ActionAgent
PREFAB_END

PREFAB_BEGIN(ClientWoman)
	Transform,
	DemoHuman,
	Overlap,
	ActionAgent
PREFAB_END

PREFAB_BEGIN(BarServer)
	Transform,
	DemoHuman,
	Overlap,
	ActionAgent
PREFAB_END

PREFAB_BEGIN(DeeJay)
	Transform,
	DemoHuman,
	Overlap,
	ActionAgent
PREFAB_END

PREFAB_BEGIN(AnyRoom)
	DemoRoom
PREFAB_END

#endif
