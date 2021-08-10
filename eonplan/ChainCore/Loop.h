#ifndef _ChainCore_Loop_h_
#define _ChainCore_Loop_h_


class LoopBase : public Node {
	
	
};




template <class First_>
class Loop0 {
	First_		o;
	
public:
	
	using First = First_;
	using Last = First_;
	
};


template <class First_, class Rest>
class LoopN : public Rest {
	First_		o;
	
public:
	static constexpr bool valid_link = std::is_same<typename First_::Src, typename Rest::First::Sink>::value;
	static_assert(valid_link, "Loop's link source must be same as sink.");
	
	
	using First = First_;
	using Last = typename Rest::Last;
	
	
	
};



template <class T>
class Loop : public LoopBase {
	T			parts;
	
public:
	static constexpr bool valid_end_to_begin = std::is_same<typename T::Last::Src, typename T::First::Sink>::value;
	static_assert(valid_end_to_begin, "Loop's last source must be same as first sink.");
	
	
	void Serialize(EonStream& s) override {TODO}
	
	
};



#define LOOP2(x, a, b) \
	using x = Loop<LoopN<a, Loop0<b>>>;
#define LOOP3(x, a, b, c) \
	using x = Loop<LoopN<a, LoopN<b, Loop0<c>>>>;
#define LOOP4(x, a, b, c, d) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, Loop0<d>>>>>;
#define LOOP5(x, a, b, c, d, e) \
	using x = Loop<LoopN<a, LoopN<b, LoopN<c, LoopN<e, Loop0<d>>>>>>;



#endif
