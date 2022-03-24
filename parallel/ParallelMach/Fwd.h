#ifndef _ParallelMach_Fwd_h_
#define _ParallelMach_Fwd_h_


NAMESPACE_TOPSIDE_BEGIN

namespace Parallel {
	
class Space;
using SpaceParent			= HierExBaseParent;
using SpaceRef				= Ref<Space,				SpaceParent>;
using SpaceVec				= RefLinkedList<Space,		SpaceParent>;

}



namespace Serial {

class LinkBase;
class Loop;
using LoopParent			= DirExBaseParent;
using LinkBaseRef			= Ref<LinkBase,				RefParent1<MetaDirectoryBase>>;
using LoopRef				= Ref<Loop,					LoopParent>;

class MachineVerifier;
class ScriptLoopLoader;

namespace Script {
class Action;
}

}

NAMESPACE_TOPSIDE_END


#endif
