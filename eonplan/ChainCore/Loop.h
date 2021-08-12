#ifndef _ChainCore_Loop_h_
#define _ChainCore_Loop_h_

NAMESPACE_PLAN_BEGIN


class LoopBase : public Node {
	
	
};




template <class First_>
class Loop0 {
	First_		o;
	
public:
	using First = First_;
	using Last = First_;
	
	template <class T> static constexpr bool HasSide() {return First_::template HasSide<T>();}
	
	
	
};


template <class First_, class Rest>
class LoopN : public Rest {
	First_		o;
	
public:
	static constexpr bool valid_link = std::is_same<typename First_::Src, typename Rest::First::Sink>::value;
	static_assert(valid_link, "Loop's link source must be same as sink.");
	
	using First = First_;
	using Last = typename Rest::Last;
	
	template <class T> static constexpr bool HasSide() {return First_::template HasSide<T>() || Rest::template HasSide<T>();}
	
	
	
};



template <class T>
class Loop : public LoopBase {
	T			parts;
	
public:
	static constexpr bool valid_end_to_begin = std::is_same<typename T::Last::Src, typename T::First::Sink>::value;
	static_assert(valid_end_to_begin, "Loop's last source must be same as first sink.");
	
	template <class C> static constexpr bool HasSide() {return T::template HasSide<C>();}
	
	void Serialize(EonStream& s) override {TODO}
	
	
};




NAMESPACE_PLAN_END

#endif
