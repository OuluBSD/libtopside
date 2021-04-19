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
	EntityPool& root = es.GetRoot();
	
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    
    reg.SetAppName("ECS ActionPlanner");
    
    SharedEntity cat = root.Create<Cat>();
    SharedEntity mouse = root.Create<Mouse>();
    
    cat		->Get<DemoEntity>()->InitCat();
    mouse	->Get<DemoEntity>()->InitMouse();
    
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





void DemoEntity::InitCat() {
	type = CAT;
	ActionAgent& act = *GetEntity().Get<ActionAgent>();
	
	
	act.Init(ACT_COUNT, ATOM_COUNT);
	#define ACT(x) act.SetAction(x, ToLower(#x));
	ACT_LIST
	#undef ACT
	
	
	WorldState& cur = act.GetStateCurrent();
	#define ATOM(x,y) cur.Set(x, y);
	ATOM_LIST
	#undef ATOM
	
	
	WorldState& goal = act.GetStateGoal();
	goal.Set(MOUSE_ALIVE, false );
	goal.Set(ALIVE, true ); // add this to avoid hurting by fall actions in plan.
	
	
}

void DemoEntity::InitMouse() {
	type = MOUSE;
	
}
