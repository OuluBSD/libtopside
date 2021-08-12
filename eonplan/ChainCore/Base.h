#ifndef _ChainCore_Base_h_
#define _ChainCore_Base_h_

NAMESPACE_PLAN_BEGIN


class Base : public Unit {
	
	
};


template <class Sink_, class Src_>
class Base2 : public Base {
	
public:
	using Sink = Sink_;
	using Side = void;
	using Src = Src_;
	
	template <class T> static constexpr bool HasSide() {return false;}
	
	
};


template <class Sink_, class Side_, class Src_>
class Base3 : public Base {
	
public:
	using Sink = Sink_;
	using Side = Side_;
	using Src = Src_;
	
	template <class T> static constexpr bool HasSide() {return std::is_same<T, Side>::value;}
	
	
};


#define BASE2(x, sink, src)			using x = Base2<sink, src>;
#define BASE3(x, sink, side, src)	using x = Base3<sink, side, src>;


NAMESPACE_PLAN_END

#endif
