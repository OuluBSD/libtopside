#ifndef _EcsCore_Defs_h_
#define _EcsCore_Defs_h_


#define RTTI_COMP0(comp) RTTI_DECL1(comp, ComponentT)
#define RTTI_COMP1(comp, iface0) RTTI_DECL2(comp, ComponentT, iface0)
#define RTTI_COMP2(comp, iface0, iface1) RTTI_DECL3(comp, ComponentT, iface0, iface1)
#define RTTI_COMP3(comp, iface0, iface1, iface2) RTTI_DECL4(comp, ComponentT, iface0, iface1, iface2)
#define RTTI_COMP4(comp, iface0, iface1, iface2, iface3) RTTI_DECL5(comp, ComponentT, iface0, iface1, iface2, iface3)

#define RTTI_DCOMP0(comp) RTTI_DECL1(comp, comp::Component)
#define RTTI_DCOMP1(comp, iface0) RTTI_DECL2(comp, comp::Component, iface0)
#define RTTI_DCOMP2(comp, iface0, iface1) RTTI_DECL3(comp, comp::Component, iface0, iface1)
#define RTTI_DCOMP3(comp, iface0, iface1, iface2) RTTI_DECL4(comp, comp::Component, iface0, iface1, iface2)
#define RTTI_DCOMP4(comp, iface0, iface1, iface2, iface3) RTTI_DECL5(comp, comp::Component, iface0, iface1, iface2, iface3)

#define RTTI_CONN0(comp) RTTI_DECL1(comp, TS::Connector<comp>)
#define RTTI_CONN1(comp, iface0) RTTI_DECL2(comp, TS::Connector<comp>, iface0)
#define RTTI_CONN2(comp, iface0, iface1) RTTI_DECL3(comp, TS::Connector<comp>, iface0, iface1)
#define RTTI_CONN3(comp, iface0, iface1, iface2) RTTI_DECL4(comp, TS::Connector<comp>, iface0, iface1, iface2)
#define RTTI_CONN4(comp, iface0, iface1, iface2, iface3) RTTI_DECL5(comp, TS::Connector<comp>, iface0, iface1, iface2, iface3)


#define NAMESPACE_PBR_NAME Pbr
#define NAMESPACE_PBR_BEGIN namespace  NAMESPACE_TOPSIDE_NAME { namespace  NAMESPACE_PBR_NAME {
#define NAMESPACE_PBR_END }}


#endif
