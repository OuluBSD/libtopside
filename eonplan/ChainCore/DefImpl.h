#ifndef _ChainCore_DefImpl_h_
#define _ChainCore_DefImpl_h_



#undef BASE
#undef BASE_FLAG
#undef BASE_ACTION
#undef HEADER11
#undef HEADER12
#undef HEADER12_U01
#undef HEADER13_U02
#undef HEADER21
#undef HEADER21_U10
#undef HEADER22_U11
#undef HEADER31_U20
#undef HEADER55_U44
#undef HEADER_ACTION
#undef HEADER_INHERITS
#undef HEADER_ARG
#undef LOOP2
#undef LOOP3
#undef LOOP4
#undef LOOP5
#undef LINK
#undef CHAIN0
#undef CHAIN1
#undef CHAIN2
#undef CHAIN3
#undef CHAIN4
#undef CHAIN5
#undef CHAIN6
#undef CHAIN7
#undef CHAIN8
#undef SCOPE0
#undef SCOPE1
#undef SCOPE2
#undef SCOPE3
#undef SCOPE4
#undef SCOPE5
#undef SCOPE6
#undef SCOPE7
#undef SCOPE8
#undef MACHINE0
#undef MACHINE1
#undef MACHINE2
#undef MACHINE3
#undef MACHINE4
#undef MACHINE5
#undef MACHINE6
#undef MACHINE7
#undef MACHINE8



#define BASE(x)													Factory::RegBase<x>(#x);
#define BASE_FLAG(x, flag)										Factory::BaseFlag<x>(#x, #flag);
#define BASE_ACTION(x, act)										Factory::BaseAction<x>(#x, #act);
#define HEADER11(x, base, role, content, sink, src)				Factory::RegHeader<x>(#x, #base, #role, #content,	0,0,	#sink, 0, 0, 0, 0,		#src, 0, 0, 0, 0);
#define HEADER12(x, base, role, content, sink, side, src)		Factory::RegHeader<x>(#x, #base, #role, #content,	0,0,	#sink, 0, 0, 0, 0,		#src, #side, 0, 0, 0);
#define HEADER12_U01(x, base, role, content, sink, side, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	0,1,	#sink, 0, 0, 0, 0,		#src, #side, 0, 0, 0);
#define HEADER13_U02(x, base, role, content, sink, s0, s1, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	0,2,	#sink, 0, 0, 0, 0,		#src, #s0, #s1, 0, 0);
#define HEADER21(x, base, role, content, sink, side, src)		Factory::RegHeader<x>(#x, #base, #role, #content,	0,0,	#sink, #side, 0, 0, 0,	#src, 0, 0, 0, 0);
#define HEADER21_U10(x, base, role, content, sink, side, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	1,0,	#sink, #side, 0, 0, 0,	#src, 0, 0, 0, 0);
#define HEADER22_U11(x, base, role, content, sink, s0, s1, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	1,1,	#sink, #s0, 0, 0, 0,	#src, #s1, 0, 0, 0);
#define HEADER31_U20(x, base, role, content, sink, s0, s1, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	2,0,	#sink, #s0, #s1, 0, 0,	#src, 0, 0, 0, 0);
#define HEADER55_U44(x, base, role, content, sink, side, src)	Factory::RegHeader<x>(#x, #base, #role, #content,	4,4,	#sink, #side, #side, #side, #side,		#src, #side, #side, #side, #side);
#define HEADER_ACTION(x, act)									Factory::HeaderAction<x>(#x, #act);
#define HEADER_LINK(x, key, role)								Factory::HeaderLinktype<x>(#x, #key, #role);
#define HEADER_INHERITS(x, cls)									Factory::HeaderInherits<x>(#x, #cls);
#define HEADER_ARG(x, key, value)								Factory::HeaderArg<x>(#x, #key, #value);


#define LOOP2(x, a, b) Factory::RegLoop<x>(#x, #a "\n" #b);
#define LOOP3(x, a, b, c) Factory::RegLoop<x>(#x, #a "\n" #b "\n" #c);
#define LOOP4(x, a, b, c, d) Factory::RegLoop<x>(#x, #a "\n" #b "\n" #c "\n" #d);
#define LOOP5(x, a, b, c, d, e) Factory::RegLoop<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e);

#define LINK(name, from, to) Factory::RegLink<from, to>(#name, #from, #to);

#define CHAIN1(x, a, links) Factory::RegChain<x>(#x, #a, links);
#define CHAIN2(x, a, b, links) Factory::RegChain<x>(#x, #a "\n" #b, links);
#define CHAIN3(x, a, b, c, links) Factory::RegChain<x>(#x, #a "\n" #b "\n" #c, links);
#define CHAIN4(x, a, b, c, d, links) Factory::RegChain<x>(#x, #a "\n" #b "\n" #c "\n" #d, links);
#define CHAIN5(x, a, b, c, d, e, links) Factory::RegChain<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e, links);
#define CHAIN6(x, a, b, c, d, e, f, links) Factory::RegChain<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f, links);
#define CHAIN7(x, a, b, c, d, e, f, g, links) Factory::RegChain<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g, links);
#define CHAIN8(x, a, b, c, d, e, f, g, h, links)Factory::RegChain<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g "\n" #h, links);

#define SCOPE1(x, a, links) Factory::RegScope<x>(#x, #a, links);
#define SCOPE2(x, a, b, links) Factory::RegScope<x>(#x, #a "\n" #b, links);
#define SCOPE3(x, a, b, c, links) Factory::RegScope<x>(#x, #a "\n" #b "\n" #c, links);
#define SCOPE4(x, a, b, c, d, links) Factory::RegScope<x>(#x, #a "\n" #b "\n" #c "\n" #d, links);
#define SCOPE5(x, a, b, c, d, e, links) Factory::RegScope<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e, links);
#define SCOPE6(x, a, b, c, d, e, f, links) Factory::RegScope<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f, links);
#define SCOPE7(x, a, b, c, d, e, f, g, links) Factory::RegScope<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g, links);
#define SCOPE8(x, a, b, c, d, e, f, g, h, links)Factory::RegScope<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g "\n" #h, links);

#define MACHINE1(x, a, links) Factory::RegMachine<x>(#x, #a, links);
#define MACHINE2(x, a, b, links) Factory::RegMachine<x>(#x, #a "\n" #b, links);
#define MACHINE3(x, a, b, c, links) Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c, links);
#define MACHINE4(x, a, b, c, d, links) Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c "\n" #d, links);
#define MACHINE5(x, a, b, c, d, e, links) Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e, links);
#define MACHINE6(x, a, b, c, d, e, f, links) Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f, links);
#define MACHINE7(x, a, b, c, d, e, f, g, links) Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g, links);
#define MACHINE8(x, a, b, c, d, e, f, g, h, links)Factory::RegMachine<x>(#x, #a "\n" #b "\n" #c "\n" #d "\n" #e "\n" #f "\n" #g "\n" #h, links);



#endif
