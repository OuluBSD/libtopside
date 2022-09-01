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
//class Link;
using Link = LinkBase;
class Loop;
class ScriptLoader;
using LoopParent			= DirExBaseParent;
using LinkParent			= RefParent1<MetaDirectoryBase>;
using LinkBaseRef			= Ref<LinkBase,				RefParent1<MetaDirectoryBase>>;
using LoopRef				= Ref<Loop,					LoopParent>;
using LinkRef				= Ref<LinkBase,				LinkParent>;

class MachineVerifier;
class ScriptLoopLoader;
class ScriptDriverLoader;
class LinkSystem;

using LinkSystemRef			= Ref<LinkSystem,			MetaSystemParent>;

namespace Script {
class Action;
}

bool Serial_Link_ForwardAsyncMem(Link* l, byte* data, int size);
void Serial_Link_PostContinueForward(Link* l);

}

NAMESPACE_TOPSIDE_END


#endif
