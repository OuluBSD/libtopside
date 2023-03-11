#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


PushButtonComp::PushButtonComp() {
	AddSink("A");
	AddSource("B");
}


NAMESPACE_TOPSIDE_END
