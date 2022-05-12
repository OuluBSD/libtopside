#ifndef _ChainCore_DefHeader_h_
#define _ChainCore_DefHeader_h_

#define BASE(x)													class x : public BaseT<x> {};
#define HEADER11(x, base, role, content, sink, src)				using x = HeaderT<base, sink, src>;
#define HEADER12(x, base, role, content, sink, side, src)		using x = HeaderT<base, sink, src>;
#define HEADER12_U01(x, base, role, content, sink, side, src)	using x = HeaderT<base, sink, src>;
#define HEADER13_U02(x, base, role, content, sink, s0, s1, src)	using x = HeaderT<base, sink, src>;
#define HEADER15_U04(x, base, role, content, sink, side, src)	using x = HeaderT<base, sink, src>;
#define HEADER21(x, base, role, content, sink, side, src)		using x = HeaderT<base, sink, src>;
#define HEADER21_U10(x, base, role, content, sink, side, src)	using x = HeaderT<base, sink, src>;
#define HEADER22_U11(x, base, role, content, sink, s0, s1, src)	using x = HeaderT<base, sink, src>;
#define HEADER31_U20(x, base, role, content, sink, s0, s1, src)	using x = HeaderT<base, sink, src>;
#define HEADER55_U44(x, base, role, content, sink, side, src)	using x = HeaderT<base, sink, src>;
#define BASE_FLAG(x, flag)
#define BASE_ACTION(x, act)
#define HEADER_LINK(x, key, role)
#define HEADER_ACTION(x, act)
#define HEADER_INHERITS(x, cls)
#define HEADER_ARG(x, key, value)


#define LOOP2(x, a, b) \
	using x = Loop<LoopN<a, Loop0<b>>>;
#define LOOP3(x, a, b, c) \
	using x = Loop<LoopN<a, LoopN<b, Loop0<c>>>>;
#define LOOP4(x, a, b, c, d) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, Loop0<d>>>>>;
#define LOOP5(x, a, b, c, d, e) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, LoopN<d, Loop0<e>>>>>>;

#define LINK(name, from, to)



#define CHAIN1(x, a, links) \
	\
	using x = Chain<Chain0<a>>;

#define CHAIN2(x, a, b, links) \
	\
	using x = Chain<ChainN<a,Chain0<b>>>;

#define CHAIN3(x, a, b, c, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,Chain0<c>>>>;

#define CHAIN4(x, a, b, c, d, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,Chain0<d>>>>>;

#define CHAIN5(x, a, b, c, d, e, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,Chain0<e>>>>>>;

#define CHAIN6(x, a, b, c, d, e, f, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,Chain0<f>>>>>>>;

#define CHAIN7(x, a, b, c, d, e, f, g, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,Chain0<g>>>>>>>>;

#define CHAIN8(x, a, b, c, d, e, f, g, h, links) \
	\
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,ChainN<g,Chain0<h>>>>>>>>>;



#define SCOPE1(x, a, links) \
	\
	using x = Scope<Scope0<a>>;

#define SCOPE2(x, a, b, links) \
	\
	using x = Scope<ScopeN<a,Scope0<b>>>;

#define SCOPE3(x, a, b, c, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,Scope0<c>>>>;

#define SCOPE4(x, a, b, c, d, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,Scope0<d>>>>>;

#define SCOPE5(x, a, b, c, d, e, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,Scope0<e>>>>>>;

#define SCOPE6(x, a, b, c, d, e, f, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,Scope0<f>>>>>>>;

#define SCOPE7(x, a, b, c, d, e, f, g, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,Scope0<g>>>>>>>>;

#define SCOPE8(x, a, b, c, d, e, f, g, h, links) \
	\
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,ScopeN<g,Scope0<h>>>>>>>>>;



#define MACHINE1(x, a, links) \
	\
	using x = Machine<Machine0<a>>;

#define MACHINE2(x, a, b, links) \
	\
	using x = Machine<MachineN<a,Machine0<b>>>;

#define MACHINE3(x, a, b, c, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,Machine0<c>>>>;

#define MACHINE4(x, a, b, c, d, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,Machine0<d>>>>>;

#define MACHINE5(x, a, b, c, d, e, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,Machine0<e>>>>>>;

#define MACHINE6(x, a, b, c, d, e, f, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,Machine0<f>>>>>>>;

#define MACHINE7(x, a, b, c, d, e, f, g, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,Machine0<g>>>>>>>>;

#define MACHINE8(x, a, b, c, d, e, f, g, h, links) \
	\
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,MachineN<g,Machine0<h>>>>>>>>>;



#endif
