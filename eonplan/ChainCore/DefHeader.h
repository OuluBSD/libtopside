#ifndef _ChainCore_DefHeader_h_
#define _ChainCore_DefHeader_h_

#define BASE2(x, sink, src)			using x = Base2<sink, src>;
#define BASE3(x, sink, side, src)	using x = Base3<sink, side, src>;

#define HEADER(x, base) class x : public Header<base> {};

#define LOOP2(x, a, b) \
	using x = Loop<LoopN<a, Loop0<b>>>;
#define LOOP3(x, a, b, c) \
	using x = Loop<LoopN<a, LoopN<b, Loop0<c>>>>;
#define LOOP4(x, a, b, c, d) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, Loop0<d>>>>>;
#define LOOP5(x, a, b, c, d, e) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, LoopN<e, Loop0<d>>>>>>;

#define LINK(name, from, to)



#define CHAIN1(x, a, links) \
	char x##_link[] = links; \
	using x = Chain<Chain0<a>,x##_link>;

#define CHAIN2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,Chain0<b>>,x##_link>;

#define CHAIN3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,Chain0<c>>>,x##_link>;

#define CHAIN4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,Chain0<d>>>>,x##_link>;

#define CHAIN5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,Chain0<e>>>>>,x##_link>;

#define CHAIN6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,Chain0<f>>>>>>,x##_link>;

#define CHAIN7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,Chain0<g>>>>>>>,x##_link>;

#define CHAIN8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,ChainN<g,Chain0<h>>>>>>>>,x##_link>;



#define SCOPE1(x, a, links) \
	char x##_link[] = links; \
	using x = Scope<Scope0<a>,x##_link>;

#define SCOPE2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,Scope0<b>>,x##_link>;

#define SCOPE3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,Scope0<c>>>,x##_link>;

#define SCOPE4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,Scope0<d>>>>,x##_link>;

#define SCOPE5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,Scope0<e>>>>>,x##_link>;

#define SCOPE6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,Scope0<f>>>>>>,x##_link>;

#define SCOPE7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,Scope0<g>>>>>>>,x##_link>;

#define SCOPE8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,ScopeN<g,Scope0<h>>>>>>>>,x##_link>;



#define MACHINE1(x, a, links) \
	char x##_link[] = links; \
	using x = Machine<Machine0<a>,x##_link>;

#define MACHINE2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,Machine0<b>>,x##_link>;

#define MACHINE3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,Machine0<c>>>,x##_link>;

#define MACHINE4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,Machine0<d>>>>,x##_link>;

#define MACHINE5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,Machine0<e>>>>>,x##_link>;

#define MACHINE6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,Machine0<f>>>>>>,x##_link>;

#define MACHINE7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,Machine0<g>>>>>>>,x##_link>;

#define MACHINE8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,MachineN<g,Machine0<h>>>>>>>>,x##_link>;



#endif
