#ifndef _EcsCore_Connector_h_
#define _EcsCore_Connector_h_

NAMESPACE_OULU_BEGIN

class Connector;


class ConnectorSystem : public System<ConnectorSystem> {
	Index<void*> conns;
	Ref<EntityStore> es;
	
public:
	using System::System;
	
	void Update(float dt) override;
	void Uninitialize() override;
	
	
protected:
	friend class Connector;
	
	void Add(Connector* c) {conns.FindAdd(c);}
	void Remove(Connector* c) {conns.RemoveKey(c);}
	
};



class Connector : public Component<Connector> {
	
	
public:
	using Component::Component;
	
	
	Connector();
	
	void Initialize() override;
	void Uninitialize() override;
	
	void operator=(const Connector& c) {}
	
	
	void ConnectAll(ConnectorArea a);
	#define IFACE(x) void Connect##x##Sink (ConnectorArea a); void Connect##x##Source (ConnectorArea a);
	IFACE_LIST
	#undef IFACE
	
	void SignalAll();
	#define IFACE(x) void Signal##x##Sink (); void Signal##x##Source ();
	IFACE_LIST
	#undef IFACE
	
	const Vector<InterfaceBase*>& GetSourceInterfaces() const {return src_ifaces;}
	const Vector<InterfaceBase*>& GetSinkInterfaces() const {return sink_ifaces;}
	bool HasInterfaces() const {return src_ifaces.GetCount() || sink_ifaces.GetCount();}
	void SetUpdateInterfaces(bool b=true) {update_ifaces = b;}
	bool IsUpdateInterfaces() const {return update_ifaces;}
	void UnlinkAll();
	
protected:
	friend class ConnectorSystem;
	friend class Entity;
	
	uint64 connect_bits[CONNAREA_COUNT];
	uint64 signal_bits = 0;
	Vector<InterfaceBase*> src_ifaces, sink_ifaces;
	bool update_ifaces = true;
	
	void ClearInterfaces() {src_ifaces.Clear(); sink_ifaces.Clear();}
	void AddSourceInterface(InterfaceBase* base) {src_ifaces.Add(base);}
	void AddSinkInterface(InterfaceBase* base) {sink_ifaces.Add(base);}
	
	bool IsConnectAny(ConnectorArea t) const {return connect_bits[t] != 0;}
	uint64 GetConnectBits(ConnectorArea t) const {return connect_bits[t];}
	void ClearConnectBits(ConnectorArea t) {connect_bits[t] = 0;}
	
	bool IsSignalAny() const {return signal_bits != 0;}
	uint64 GetSignalBits() const {return signal_bits;}
	void ClearSignalBits() {signal_bits = 0;}
	
};


NAMESPACE_OULU_END

#endif
