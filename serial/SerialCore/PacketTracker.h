#ifndef _SerialCore_PacketTracker_h_
#define _SerialCore_PacketTracker_h_

NAMESPACE_SERIAL_BEGIN


#define RTTI_CTX_SYS(sys) \
		RTTI_DECL1(sys, System<sys>)

class PacketTracker :
	public System<PacketTracker>
{
	PacketId id_counter = 1;
	
	
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
	SYS_DEF_VISIT
	
	static void Track(TrackerInfo info, Packet& p) {Track(info, *p);}
	static void Checkpoint(TrackerInfo info, Packet& p) {Checkpoint(info, *p);}
	static void StopTracking(TrackerInfo info, Packet& p) {StopTracking(info, *p);}
	
	static void Track(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->Track0(info,p);}
	static void Checkpoint(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->Checkpoint0(info,p);}
	static void StopTracking(TrackerInfo info, PacketValue& p) {if (active_tracker()) active_tracker()->StopTracking0(info,p);}
	
};

#undef RTTI_CTX_SYS


NAMESPACE_SERIAL_END

#endif
