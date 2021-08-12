#ifndef _ChainCore_Header_h_
#define _ChainCore_Header_h_

NAMESPACE_PLAN_BEGIN


template <class T>
class Header : public T {
	
	
public:
	static_assert(std::is_convertible<T&, Base&>::value, "T must inherit Base");
	
	
};


#define HEADER(x, base) class x : public Header<base> {};


NAMESPACE_PLAN_END

#endif
