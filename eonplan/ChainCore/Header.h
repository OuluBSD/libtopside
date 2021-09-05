#ifndef _ChainCore_Header_h_
#define _ChainCore_Header_h_

NAMESPACE_PLAN_BEGIN


class Header : public Unit {
	
};


template <class Base_, class Sink_, class Src_>
class Header2 : public Header {
	
public:
	using BaseT = Base_;
	using Sink = Sink_;
	using Side = void;
	using Src = Src_;
	
	template <class T> static constexpr bool HasSide() {return false;}
	
	
	static_assert(std::is_convertible<BaseT&, Base&>::value, "T must inherit Base");
	
};


template <class Base_, class Sink_, class Side_, class Src_>
class Header3 : public Header {
	
public:
	using BaseT = Base_;
	using Sink = Sink_;
	using Side = Side_;
	using Src = Src_;
	
	template <class T> static constexpr bool HasSide() {return std::is_same<T, Side>::value;}
	
	
	static_assert(std::is_convertible<BaseT&, Base&>::value, "T must inherit Base");
	
};





NAMESPACE_PLAN_END

#endif
