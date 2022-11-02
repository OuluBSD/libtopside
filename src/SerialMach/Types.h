#ifndef _SerialMach_Types_h_
#define _SerialMach_Types_h_

NAMESPACE_SERIAL_BEGIN
using namespace Parallel;


using ValCls				= Parallel::ValCls;
using DevCls				= Parallel::DevCls;
using ValDevCls				= Parallel::ValDevCls;
using ValDevTuple			= Parallel::ValDevTuple;
using Format				= Parallel::Format;
using PacketId				= Parallel::PacketId;
using PacketValue			= Parallel::PacketValue;
using Machine				= Parallel::Machine;
using Packet				= Parallel::Packet;
using SimpleValue			= Parallel::SimpleValue;
using Value					= Parallel::Value;
using AtomParent			= Parallel::AtomParent;
using DefaultExchangePoint	= Parallel::DefaultExchangePoint;
using SideStatus			= Parallel::SideStatus;
using PacketIO				= Parallel::PacketIO;
template <class T> using RefT_Loop	= Ref<T, LoopParent>;
template <class T> using System		= Parallel::System<T>;

#if HAVE_PACKETTRACKER
using TrackerInfo			= Parallel::TrackerInfo;
#endif


class LoopStore;
using LoopStoreRef			= Ref<LoopStore,			ParallelSystemParent>;
using LoopVec				= RefLinkedList<Loop,		LoopParent>;
using LinkVec				= RefLinkedList<LinkBase,	LinkParent>;


using SerialSystemParent	= MetaSystemParent;



typedef dword LoopId;



NAMESPACE_SERIAL_END

#endif
