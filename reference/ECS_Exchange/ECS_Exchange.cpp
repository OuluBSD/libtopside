#include "ECS_Exchange.h"

/*
-- The Club demo --
Rooms: dance-floor, bar, toilet
Entities: client-men, client-women, dj, bar server
Exchanges: harmony (music), money, interaction-futures (feelings, etc.)

*/

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	int men = 15;
	int women = 17;
	int bar_servers = 2;
	
	Machine& mach = GetMachine();
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& es = *mach.Add<EntityStore>();
	EntityPool& root = es.GetRoot();
	EntityPool& people = root.AddPool("people");
	EntityPool& rooms = root.AddPool("rooms");
	EntityPool& octree = root.AddPool("octree");
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<EventSystem>();
    mach.Add<ExchangeSystem>();
    mach.Add<StateSystem>();
    mach.Add<ActionSystem>();
    
    reg.SetAppName("ECS Exchange");
    
    if (!mach.Start()) {
        LOG("error: machine wouldn't start");
        return;
    }
    
    try {
        /*
			A silly little club (far from realistic)
			
			e - entrance
			x - wall
			f - women's toilets
			m - men's toilets
			p - personel's area
			s - bar stall
			b - bar's customer area
			d - dancefloor
			s - dj's stage
        */
        
        ArrayMap<int, EntityRef> loc_ctxs;
        EntityRef& entrance		= loc_ctxs.Add('e', rooms.Create<AnyRoom>());
        EntityRef& wall			= loc_ctxs.Add('x', rooms.Create<AnyRoom>());
        EntityRef& wtoilet		= loc_ctxs.Add('f', rooms.Create<AnyRoom>());
        EntityRef& mtoilet		= loc_ctxs.Add('m', rooms.Create<AnyRoom>());
        EntityRef& personel		= loc_ctxs.Add('p', rooms.Create<AnyRoom>());
        EntityRef& barstall		= loc_ctxs.Add('s', rooms.Create<AnyRoom>());
        EntityRef& bar			= loc_ctxs.Add('b', rooms.Create<AnyRoom>());
        EntityRef& dancefloor	= loc_ctxs.Add('d', rooms.Create<AnyRoom>());
        EntityRef& stage			= loc_ctxs.Add('s', rooms.Create<AnyRoom>());
        
        const char* map =
			"pppxmmmxffff\n"
			"pppxmmmxffff\n"
			"pssxmmmxffff\n"
			"psbxxxhhhxxx\n"
			"psbbbhhhheee\n"
			"psbbbxhhheee\n"
			"psbbbxhhxeee\n"
			"psbbbxhhxeee\n"
			"xxbbxxhhxxxx\n"
			"dddddddddddd\n"
			"dddddddddddd\n"
			"dddddddddddd\n"
			"dddddddddddd\n"
			"ddddssssdddd\n"
			"ddddssssdddd\n"
			"ddddssssdddd"
			;
		
        CreateOctreeEntityFromString(octree, map, loc_ctxs);
        
        OverlapSink& entrance3d		= *entrance->FindOverlapSink();
        OverlapSink& dancefloor3d	= *dancefloor->FindOverlapSink();
        OverlapSink& bar3d			= *bar->FindOverlapSink();
        
        for(int i = 0; i < men; i++) {
			EntityRef e = people.Create<ClientMan>();
			DemoHuman& h = *e->Get<DemoHuman>();
			Transform& t = *e->Get<Transform>();
			h.Init(DemoHuman::CLIENT_MALE);
			//t.MoveTo(entrance3d);
        }
        
        for(int i = 0; i < women; i++) {
			EntityRef e = people.Create<ClientWoman>();
			DemoHuman& h = *e->Get<DemoHuman>();
			Transform& t = *e->Get<Transform>();
			h.Init(DemoHuman::CLIENT_FEMALE);
			//t.MoveTo(entrance3d);
        }
        
        for(int i = 0; i < bar_servers; i++) {
			EntityRef e = people.Create<BarServer>();
			DemoHuman& h = *e->Get<DemoHuman>();
			Transform& t = *e->Get<Transform>();
			h.Init(DemoHuman::PERSONEL_BAR);
			//t.MoveTo(bar3d);
        }
        
        {
            EntityRef e = people.Create<DeeJay>();
			DemoHuman& h = *e->Get<DemoHuman>();
			Transform& t = *e->Get<Transform>();
			h.Init(DemoHuman::PERSONEL_DJ);
			//t.MoveTo(dancefloor3d);
        }
        
	    TimeStop t;
	    while (mach.IsRunning()) {
	        double dt = ResetSeconds(t);
	        mach.Update(dt);
	        Sleep(1);
	    }
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
    
    mach.Stop();
}









void DemoHuman::Init(Type type) {
	ActionAgent* a = GetEntity().Find<ActionAgent>();
	ASSERT(a);
	#define SetAction(x) {a->SetAction(x, ToLower(String(#x).Mid(4)));}
	a->Init(ACT_COUNT, ATOM_COUNT);
	if (type == DemoHuman::CLIENT_MALE || type == DemoHuman::CLIENT_FEMALE) {
		SetAction(ACT_GO_BAR);
		SetAction(ACT_GET_BARTENDER_ATTENTION);
		SetAction(ACT_TALK_TO_BARTENDER);
		SetAction(ACT_ORDER_DRINK);
		SetAction(ACT_PAY_DRINK);
		SetAction(ACT_TAKE_DRINK);
		SetAction(ACT_SAY_THANK_YOU);
		SetAction(ACT_TALK_WITH_NEAREST);
		SetAction(ACT_GO_DANCEFLOOR);
		SetAction(ACT_DANCE_ALONE);
		SetAction(ACT_DANCE_WITH_NEAREST);
		SetAction(ACT_SHOW_INTEREST);
		SetAction(ACT_EXIT);
		
		if (type == DemoHuman::CLIENT_MALE) {
			SetAction(ACT_GO_TO_LONELY_W);
			SetAction(ACT_GO_TOILET_M);
			SetAction(ACT_DO_YOUR_BUSINESS_M);
		}
		else {
			SetAction(ACT_GO_TO_LONELY_M);
			SetAction(ACT_GO_TOILET_W);
			SetAction(ACT_DO_YOUR_BUSINESS_W);
		}
	}
	else if (type == DemoHuman::PERSONEL_BAR) {
		SetAction(ACT_NOTICE_CLIENT);
		SetAction(ACT_GO_TO_CLIENT);
		SetAction(ACT_TALK_TO_CLIENT);
		SetAction(ACT_MAKE_DRINK_FOR_CLIENT);
		SetAction(ACT_TAKE_PAYMENT_FROM_CLIENT);
		SetAction(ACT_SAY_THANK_YOU);
	}
	else if (type == DemoHuman::PERSONEL_DJ) {
		SetAction(ACT_PLAY_DANCEHITS_150BPM);
		SetAction(ACT_PLAY_DANCEHITS_120BPM);
		SetAction(ACT_PLAY_DANCEHITS_90BPM);
		SetAction(ACT_PLAY_QUIET_BACKGROUND_MUSIC);
	}
	else Panic("invalid type");
	
}



