#ifndef _ChainCore_Header_h_
#define _ChainCore_Header_h_

NAMESPACE_PLAN_BEGIN


class Header : public Unit {
	
};


template <class Base_, class Sink_, class Src_>
class HeaderT : public Header {
	
public:
	using BaseT = Base_;
	using Sink = Sink_;
	using Src = Src_;
	
	static_assert(std::is_convertible<BaseT&, Base&>::value, "T must inherit Base");
	
};








NAMESPACE_PLAN_END

#endif
