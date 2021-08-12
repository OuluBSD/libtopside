#ifndef _ChainCore_ValDev_h_
#define _ChainCore_ValDev_h_

NAMESPACE_PLAN_BEGIN


class SrcBase : public Unit {
	
public:
	
};


class SinkBase : public Unit {
	
public:
	
};

template <class T>
class Src : public SrcBase {
	
public:
	
	
};

template <class T>
class Sink : public SinkBase {
	
public:
	
	
};


class ValDevSpec {
	
public:
	
	
};

#define VAL2(x, val) \
	class x##val : public ValDevSpec { \
		\
	public: \
		\
	}; \
	using Src##x##val	= Src<x##val>; \
	using Sink##x##val	= Sink<x##val>;
#define DEV(x) VAL2_LIST(x)

DEV_LIST

#undef DEV
#undef VAL2


#define VAL(x) \
	using x##Src		= Src<Center##x>; \
	using x##Sink		= Sink<Center##x>;

VAL_LIST

#undef VAL


NAMESPACE_PLAN_END

#endif
