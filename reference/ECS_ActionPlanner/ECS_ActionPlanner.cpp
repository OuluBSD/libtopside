#include "ECS_ActionPlanner.h"

#define ACT_LIST \
	ACT(CAT) \
	ACT(APPROACH) \
	ACT(COME_DOWN) \
	ACT(AIM) \
	ACT(ATTACK) \
	ACT(WAIT) \
	ACT(VERY_HIGH_JUMP_ATTACK) \
	ACT(FLEE)

enum {
	#define ACT(x) x,
	ACT_LIST
	#undef ACT
	ACT_COUNT
};


#define ATOM_LIST \
	ATOM(ARMED_WITH_CLAWS,	true) \
	ATOM(MOUSE_VISIBLE,		false) \
	ATOM(NEAR_MOUSE,		false) \
	ATOM(AT_HIGH_PLACE,		true) \
	ATOM(CLAWS_EXTENDED,	false) \
	ATOM(READY_TO_ATTACK,	false) \
	ATOM(MOUSE_ALIVE,		true) \
	ATOM(ALIVE,				true)

enum {
	#define ATOM(x,y) x,
	ATOM_LIST
	#undef ATOM
	ATOM_COUNT
};


CONSOLE_APP_MAIN {
	SetCoutLog();
	
	Machine& mach = GetMachine();
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& es = *mach.Add<EntityStore>();
	Pool& root = es.GetRoot();
	Pool& actors = root.AddPool("actors");
	Pool& routes = root.AddPool("routes");
	Pool& route_cls = root.AddPool("route_classes");
	
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    mach.Add<RouteSystem>();
    
    reg.SetAppName("ECS ActionPlanner");
    
    VAR cat = actors.CreateConnectedInternal<Cat>();
    VAR mouse = actors.CreateConnectedInternal<Mouse>();
    
    VAR high_place		= route_cls.Create<RouteRidgeHigh>();
    VAR ground			= route_cls.Create<RouteGroundSoft>();
    
    VAR tree_branch	= routes.Create<RouteNode>();
    VAR tree_ground	= routes.Create<RouteNode>();
    VAR mouse_ground	= routes.Create<RouteNode>();
    
    tree_branch->FindOverlapSource()->LinkManually(*high_place->FindOverlapSink());
    tree_ground->FindOverlapSource()->LinkManually(*ground->FindOverlapSink());
    mouse_ground->FindOverlapSource()->LinkManually(*ground->FindOverlapSink());
    
    if (!mach.Start()) {
        LOG("error: machine wouldn't start");
        return;
    }
    
    try {
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






void DemoCat::OnLink(Ref provider, Cookie cookie) {
	TODO
	/*ActionSource* asrc = CastPtr<ActionSource*>(iface);
	
	if (asrc) {
		ag = asrc->AddActionGroup(ACT_COUNT, ATOM_COUNT);
		
		#define ACT(x) asrc->SetActionName(ag, x, ToLower(#x));
		ACT_LIST
		#undef ACT
		
		#define ATOM(x,y) asrc->SetCurrentAtom(ag, x, y);
		ATOM_LIST
		#undef ATOM
		
		asrc->SetGoalAtom(ag, MOUSE_ALIVE, false );
		asrc->SetGoalAtom(ag, ALIVE, true ); // add this to avoid hurting by fall actions in plan.
	}*/
}
