#ifndef _IHolograph_Atom_h_
#define _IHolograph_Atom_h_

NAMESPACE_PARALLEL_BEGIN


struct SpatialInteractionAtom : Atom {
	SpatialInteractionManager mgr;
	
	
	SpatialInteractionAtom();
	bool			Initialize(const Script::WorldState& ws) override;
	void			Uninitialize() override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	
};


NAMESPACE_PARALLEL_END

#endif
