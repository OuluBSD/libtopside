#ifndef _EcsCore_Defs_h_
#define _EcsCore_Defs_h_


#define RTTI_COMP0(comp) RTTI_DECL1(comp, TS::Component<comp>)
#define RTTI_COMP1(comp, iface0) RTTI_DECL2(comp, TS::Component<comp>, iface0)
#define RTTI_COMP2(comp, iface0, iface1) RTTI_DECL3(comp, TS::Component<comp>, iface0, iface1)
#define RTTI_COMP3(comp, iface0, iface1, iface2) RTTI_DECL4(comp, TS::Component<comp>, iface0, iface1, iface2)
#define RTTI_COMP4(comp, iface0, iface1, iface2, iface3) RTTI_DECL5(comp, TS::Component<comp>, iface0, iface1, iface2, iface3)


#endif
