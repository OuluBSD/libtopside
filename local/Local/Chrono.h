#ifndef _Local_Chrono_h_
#define _Local_Chrono_h_

NAMESPACE_TOPSIDE_BEGIN

using NanoSeconds	= std::chrono::nanoseconds;
using MicroSeconds	= std::chrono::microseconds;
using MilliSeconds	= std::chrono::milliseconds;
using Seconds		= std::chrono::seconds;
using Minutes		= std::chrono::minutes;
using Hours			= std::chrono::hours;

inline MilliSeconds operator "" _ms(unsigned long long u) {return MilliSeconds {u};}


NAMESPACE_TOPSIDE_END

#endif
