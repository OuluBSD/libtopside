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



struct HolographicScope {
	int refs = 0;
    HolographicSpace				holospace;
    HolographicFrame				current_frame;
	SpatialStageFrameOfReference	stage_frame_of_ref;
	SpatialLocator					hmd;
	SpatialInteractionManager		spatial_interaction_manager;
    DeviceResources					dev_res;
	SpatialInteractionSource		controller[2];
	
	//Pbr::Resources					pbr_res;
	
};


HolographicScope& GetGlobalHolographicScope(int idx=0);


template <class Gfx>
struct HolographicFboAtomT :
	FboAtomT<Gfx>
{
	int holo_scope_idx = 0;
	
	HolographicScope& GetScope() const {return GetGlobalHolographicScope(holo_scope_idx);}
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	
};





#if defined flagVR && defined flagOGL
using X11OglHoloFboBase = HolographicFboAtomT<X11OglGfx>;
#endif

NAMESPACE_PARALLEL_END

#endif
