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

const dword TRANSFORM_O      = PKG_ECS_V  | 0x200 | 0;
const dword TRANSFORM2_O     = PKG_ECS_V  | 0x200 | 1;
const dword VIEWABLE_O       = PKG_ECS_V  | 0x200 | 2;
const dword VIEWPORT_O       = PKG_ECS_V  | 0x200 | 3;
const dword CHASECAM_O       = PKG_ECS_V  | 0x200 | 4;
const dword RENDERABLE_O     = PKG_ECS_V  | 0x200 | 5;
const dword MODELCOMPONENT_O = PKG_ECS_V  | 0x200 | 6;
const dword DEFGUIAPP_O      = PKG_ECS_V  | 0x200 | 7;


END_UPP_NAMESPACE


#endif
