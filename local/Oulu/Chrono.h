#ifndef _Oulu_Chrono_h_
#define _Oulu_Chrono_h_

NAMESPACE_OULU_BEGIN

using NanoSeconds	= std::chrono::nanoseconds;
using MicroSeconds	= std::chrono::microseconds;
using MilliSeconds	= std::chrono::milliseconds;
using Seconds		= std::chrono::seconds;
using Minutes		= std::chrono::minutes;
using Hours			= std::chrono::hours;

//inline double operator "" _ms(unsigned long long u) {return u * 0.001;}


NAMESPACE_OULU_END

#endif
