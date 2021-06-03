#ifndef _TemplatesLib_ValScope_h_
#define _TemplatesLib_ValScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValSpec>
struct ScopeValLibT {
	using Mach = ScopeValMachT<ValSpec>;
	using PacketValue = typename Mach::PacketValue;
	using Packet = typename Mach::Packet;
	using TrackerInfo = typename Mach::TrackerInfo;
	using PacketId = typename Mach::PacketId;
	
	
	
	#define RTTI_CTX_SYS(sys) \
			RTTI_DECL_1(sys, System<sys>, ValSpec::GetName() + #sys)
	
	class PacketTracker :
		public System<PacketTracker>
	{
		PacketId id_counter = 1;
		
		void Visit(RuntimeVisitor& vis) override {}
		
	protected:
	    bool Initialize() override;
	    void Start() override;
	    void Update(double dt) override;
	    void Stop() override;
	    void Uninitialize() override;
	    
		void Track0(TrackerInfo info, PacketValue& p);
		void Checkpoint0(TrackerInfo info, PacketValue& p);
		void StopTracking0(TrackerInfo info, PacketValue& p);
		
		static PacketTracker*& active_tracker() {static PacketTracker* p; return p;}
	public:
		RTTI_CTX_SYS(PacketTracker)
	    SYS_CTOR(PacketTracker)
		
		
		static void Track(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->Track0(info,p);}
		static void Checkpoint(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->Checkpoint0(info,p);}
		static void StopTracking(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->StopTracking0(info,p);}
		
	};
	
	#undef RTTI_CTX_SYS
};


NAMESPACE_TOPSIDE_END

#endif
