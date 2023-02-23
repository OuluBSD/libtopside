#ifndef _Core_Atomic_h_
#define _Core_Atomic_h_

NAMESPACE_UPP_BEGIN


using AtomicBool = std::atomic<bool>;
using AtomicInt = std::atomic<int>;
using Atomic = AtomicInt;


inline int AtomicInc(AtomicInt& a) {return ++a;}
inline int AtomicDec(AtomicInt& a) {return --a;}


NAMESPACE_UPP_END

#endif
