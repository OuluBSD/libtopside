#ifndef _SerialMach_Types_h_
#define _SerialMach_Types_h_

NAMESPACE_SERIAL_BEGIN
using namespace Parallel;


using ValCls = Parallel::ValCls;
using DevCls = Parallel::DevCls;
using ValDevCls = Parallel::ValDevCls;
using ValDevTuple = Parallel::ValDevTuple;
using Format = Parallel::Format;
using PacketId = Parallel::PacketId;
using TrackerInfo = Parallel::TrackerInfo;
using PacketValue = Parallel::PacketValue;
using Machine = Parallel::Machine;
using Packet = Parallel::Packet;
using SimpleValue = Parallel::SimpleValue;
using Value = Parallel::Value;
using AtomParent = Parallel::AtomParent;
using DefaultExchangePoint = Parallel::DefaultExchangePoint;
using SideStatus = Parallel::SideStatus;
using PacketIO = Parallel::PacketIO;
template <class T> using System = Parallel::System<T>;
template <class T> using RefT_Loop = Parallel::RefT_Loop<T>;

//class AtomBase;
//struct AtomTypeCls;


//class Loop;
class LoopStore;
//using LoopParent			= HierExBaseParent;
//using LoopRef				= Ref<Loop,					LoopParent>;
using LoopStoreRef			= Ref<LoopStore,			ParallelSystemParent>;
using LoopVec				= RefLinkedList<Loop,		LoopParent>;


using SerialSystemParent	= MetaSystemParent;











NAMESPACE_SERIAL_END

#endif
