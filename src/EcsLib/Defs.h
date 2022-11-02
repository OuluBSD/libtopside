#ifndef _EcsLib_Defs_h_
#define _EcsLib_Defs_h_


NAMESPACE_UPP

#ifndef ECS_MAIN

bool Open_NonGUI_ECS();
void Close_NonGUI_ECS();

		
#define ECS_MAIN \
	void EcsMainFn_(); \
	\
	CONSOLE_APP_MAIN {\
		if (Open_NonGUI_ECS()) { \
			EcsMainFn_(); \
			Close_NonGUI_ECS(); \
		} \
	} \
	\
	void EcsMainFn_()


#define CONSOLE_ECS_APP_(x) ECS_MAIN {TS::SimpleEntityApp<x>();}


#endif

END_UPP_NAMESPACE


#endif
