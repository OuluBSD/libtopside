#ifndef _ParallelMach_Fwd_h_
#define _ParallelMach_Fwd_h_


NAMESPACE_TOPSIDE_BEGIN

namespace Serial {

class Loop;
using LoopParent			= HierExBaseParent;
using LoopRef				= Ref<Loop,					LoopParent>;

class MachineVerifier;
class ScriptLoopLoader;

namespace Script {
class Action;
}

}

NAMESPACE_TOPSIDE_END


#endif
