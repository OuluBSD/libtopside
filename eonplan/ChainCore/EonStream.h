#ifndef _ChainCore_EonStream_h_
#define _ChainCore_EonStream_h_

NAMESPACE_PLAN_BEGIN

class ChainBase;
class LoopBase;

class EonStream {
	Vector<int> tmp_links;
	
public:
	
	
	virtual void Serialize(ChainBase& c) {TODO}
	virtual void Serialize(LoopBase& c) {TODO}
	
	void Link(const char* c);
	
	template <class T> EonStream& operator% (T& o) {Serialize(o); return *this;}
	
};

NAMESPACE_PLAN_END

#endif
