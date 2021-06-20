#ifndef _TemplatesLib_ValScope_h_
#define _TemplatesLib_ValScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValSpec>
struct ScopeValLibT {
	using Mach = ScopeValMachT<ValSpec>;
	using PacketValue = typename Mach::PacketValue;
	using Packet = typename Mach::Packet;
	using PacketId = typename Mach::PacketId;
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
