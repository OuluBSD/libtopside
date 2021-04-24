#ifndef _Oulu_Before_h_
#define _Oulu_Before_h_

#include <random>
#include <memory>
#include <cstring>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

#define NAMESPACE_OULU_NAME Oulu
#define NAMESPACE_OULU_BEGIN namespace  Oulu {
#define NAMESPACE_OULU_END }


namespace Upp {}
namespace Oulu {using namespace Upp;}

#endif
