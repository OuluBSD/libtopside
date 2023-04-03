#ifndef _Core_Uuid_h_
#define _Core_Uuid_h_

NAMESPACE_UPP_BEGIN


struct Uuid {
	uint64 v[2];

	Uuid() {}

	hash_t GetHashValue() const { CombineHash ch; ch.Put(v[0]); ch.Put(v[1]); return ch;}

	void     New();
	
	String ToString() const;
	static Uuid Create() { Uuid uuid; uuid.New(); return uuid; }
};


NAMESPACE_UPP_END

#endif
