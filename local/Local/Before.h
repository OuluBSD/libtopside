#ifndef _Local_Before_h_
#define _Local_Before_h_

#include <random>
#include <memory>
#include <cstring>
#include <optional>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

#define NAMESPACE_TOPSIDE_NAME Topside
#define NAMESPACE_TOPSIDE_BEGIN namespace  Topside {
#define NAMESPACE_TOPSIDE_END }


namespace Upp {}
namespace Topside {using namespace Upp;}

#endif
