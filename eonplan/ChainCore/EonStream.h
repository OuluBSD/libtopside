#ifndef _ChainCore_EonStream_h_
#define _ChainCore_EonStream_h_

class Chain;
class LoopBase;

class EonStream {
	Vector<int> tmp_links;
	
public:
	
	
	virtual void Serialize(Chain& c) {TODO}
	virtual void Serialize(LoopBase& c) {TODO}
	
	void Link(const char* c);
	
	template <class T> EonStream& operator% (T& o) {Serialize(o); return *this;}
	
};
#endif
