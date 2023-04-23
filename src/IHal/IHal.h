// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IHal_IHal_h_
#define _IHal_IHal_h_

#include <ParallelLib/ParallelLib.h>
#include <IGraphics/IGraphics.h>

NAMESPACE_PARALLEL_BEGIN

#define HAL_CLS_LIST(x) \
	HAL_CLS(AudioSinkDevice, x) \
	HAL_CLS(CenterVideoSinkDevice, x) \
	HAL_CLS(CenterFboSinkDevice, x) \
	HAL_CLS(OglVideoSinkDevice, x) \
	HAL_CLS(D12VideoSinkDevice, x) \
	HAL_CLS(ContextBase, x) \
	HAL_CLS(EventsBase, x) \
	HAL_CLS(UppEventsBase, x) \
	HAL_CLS(UppOglDevice, x) \

#define HAL_VNDR_LIST \
	HAL_VNDR(HalSdl) \
	HAL_VNDR(HalHolo) \

#define HAL_CLS(x, v) struct v##x;
#define HAL_VNDR(x) HAL_CLS_LIST(x)
HAL_VNDR_LIST
#undef HAL_VNDR
#undef HAL_CLS

#if defined flagSDL2
struct HalSdl {
	struct NativeAudioSinkDevice;
	struct NativeCenterVideoSinkDevice;
	struct NativeCenterFboSinkDevice;
	#if defined flagOGL
	struct NativeOglVideoSinkDevice;
	#endif
	#if defined flagDX12
	struct NativeD12VideoSinkDevice;
	#endif
	struct NativeContextBase;
	struct NativeEventsBase;
	#if defined flagUPPCORE
	struct NativeUppEventsBase;
	#endif
	#if (defined flagOGL && defined flagUPPCORE)
	struct NativeUppOglDevice;
	#endif
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif
#if (defined flagUWP && defined flagDX12)
struct HalHolo {
	struct NativeAudioSinkDevice;
	struct NativeCenterVideoSinkDevice;
	struct NativeCenterFboSinkDevice;
	#if defined flagOGL
	struct NativeOglVideoSinkDevice;
	#endif
	#if defined flagDX12
	struct NativeD12VideoSinkDevice;
	#endif
	struct NativeContextBase;
	struct NativeEventsBase;
	#if defined flagUPPCORE
	struct NativeUppEventsBase;
	#endif
	#if (defined flagOGL && defined flagUPPCORE)
	struct NativeUppOglDevice;
	#endif
	
	struct Thread {
		
	};
	
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};
#endif

struct HalAudioSinkDevice : public Atom {
	RTTI_DECL1(HalAudioSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalAudioSinkDevice() {}
};

struct HalCenterVideoSinkDevice : public Atom {
	RTTI_DECL1(HalCenterVideoSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalCenterVideoSinkDevice() {}
};

struct HalCenterFboSinkDevice : public Atom {
	RTTI_DECL1(HalCenterFboSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalCenterFboSinkDevice() {}
};

#if defined flagOGL
struct HalOglVideoSinkDevice : public Atom {
	RTTI_DECL1(HalOglVideoSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalOglVideoSinkDevice() {}
};
#endif

#if defined flagDX12
struct HalD12VideoSinkDevice : public Atom {
	RTTI_DECL1(HalD12VideoSinkDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalD12VideoSinkDevice() {}
};
#endif

struct HalContextBase : public Atom {
	RTTI_DECL1(HalContextBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalContextBase() {}
};

struct HalEventsBase : public Atom {
	RTTI_DECL1(HalEventsBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalEventsBase() {}
};

#if defined flagUPPCORE
struct HalUppEventsBase : public Atom {
	RTTI_DECL1(HalUppEventsBase, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalUppEventsBase() {}
};
#endif

#if (defined flagOGL && defined flagUPPCORE)
struct HalUppOglDevice : public Atom {
	RTTI_DECL1(HalUppOglDevice, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~HalUppOglDevice() {}
};
#endif


template <class Hal> struct HalAudioSinkDeviceT : HalAudioSinkDevice {
	using CLASSNAME = HalAudioSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalAudioSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::AudioSinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalAudioSinkDevice>(this);
	}
	typename Hal::NativeAudioSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::AudioSinkDevice_Create(dev))
			return false;
		if (!Hal::AudioSinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::AudioSinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::AudioSinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::AudioSinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::AudioSinkDevice_Uninitialize(*dev, *this);
		Hal::AudioSinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::AudioSinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::AudioSinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::AudioSinkDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::AudioSinkDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::AudioSinkDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::AudioSinkDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::AudioSinkDevice_DetachContext(*dev, *this, a);
	}
};
template <class Hal> struct HalCenterVideoSinkDeviceT : HalCenterVideoSinkDevice {
	using CLASSNAME = HalCenterVideoSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalCenterVideoSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::CenterVideoSinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalCenterVideoSinkDevice>(this);
	}
	typename Hal::NativeCenterVideoSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::CenterVideoSinkDevice_Create(dev))
			return false;
		if (!Hal::CenterVideoSinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::CenterVideoSinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::CenterVideoSinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::CenterVideoSinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::CenterVideoSinkDevice_Uninitialize(*dev, *this);
		Hal::CenterVideoSinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::CenterVideoSinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::CenterVideoSinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::CenterVideoSinkDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::CenterVideoSinkDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::CenterVideoSinkDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::CenterVideoSinkDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::CenterVideoSinkDevice_DetachContext(*dev, *this, a);
	}
};
template <class Hal> struct HalCenterFboSinkDeviceT : HalCenterFboSinkDevice {
	using CLASSNAME = HalCenterFboSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalCenterFboSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::CenterFboSinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalCenterFboSinkDevice>(this);
	}
	typename Hal::NativeCenterFboSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::CenterFboSinkDevice_Create(dev))
			return false;
		if (!Hal::CenterFboSinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::CenterFboSinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::CenterFboSinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::CenterFboSinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::CenterFboSinkDevice_Uninitialize(*dev, *this);
		Hal::CenterFboSinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::CenterFboSinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::CenterFboSinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::CenterFboSinkDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::CenterFboSinkDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::CenterFboSinkDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::CenterFboSinkDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::CenterFboSinkDevice_DetachContext(*dev, *this, a);
	}
};
#if defined flagOGL
template <class Hal> struct HalOglVideoSinkDeviceT : HalOglVideoSinkDevice {
	using CLASSNAME = HalOglVideoSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalOglVideoSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::OglVideoSinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalOglVideoSinkDevice>(this);
	}
	typename Hal::NativeOglVideoSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::OglVideoSinkDevice_Create(dev))
			return false;
		if (!Hal::OglVideoSinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::OglVideoSinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::OglVideoSinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::OglVideoSinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::OglVideoSinkDevice_Uninitialize(*dev, *this);
		Hal::OglVideoSinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::OglVideoSinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::OglVideoSinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::OglVideoSinkDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::OglVideoSinkDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::OglVideoSinkDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::OglVideoSinkDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::OglVideoSinkDevice_DetachContext(*dev, *this, a);
	}
};
#endif
#if defined flagDX12
template <class Hal> struct HalD12VideoSinkDeviceT : HalD12VideoSinkDevice {
	using CLASSNAME = HalD12VideoSinkDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalD12VideoSinkDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::D12VideoSinkDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalD12VideoSinkDevice>(this);
	}
	typename Hal::NativeD12VideoSinkDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::D12VideoSinkDevice_Create(dev))
			return false;
		if (!Hal::D12VideoSinkDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::D12VideoSinkDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::D12VideoSinkDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::D12VideoSinkDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::D12VideoSinkDevice_Uninitialize(*dev, *this);
		Hal::D12VideoSinkDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::D12VideoSinkDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::D12VideoSinkDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::D12VideoSinkDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::D12VideoSinkDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::D12VideoSinkDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::D12VideoSinkDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::D12VideoSinkDevice_DetachContext(*dev, *this, a);
	}
};
#endif
template <class Hal> struct HalContextBaseT : HalContextBase {
	using CLASSNAME = HalContextBaseT<Hal>;
	RTTI_DECL1(CLASSNAME, HalContextBase)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::ContextBase_Visit(*dev, *this, vis);
		vis.VisitThis<HalContextBase>(this);
	}
	typename Hal::NativeContextBase* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::ContextBase_Create(dev))
			return false;
		if (!Hal::ContextBase_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::ContextBase_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::ContextBase_Start(*dev, *this);
	}
	void Stop() override {
		Hal::ContextBase_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::ContextBase_Uninitialize(*dev, *this);
		Hal::ContextBase_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::ContextBase_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::ContextBase_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::ContextBase_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::ContextBase_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::ContextBase_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::ContextBase_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::ContextBase_DetachContext(*dev, *this, a);
	}
};
template <class Hal> struct HalEventsBaseT : HalEventsBase {
	using CLASSNAME = HalEventsBaseT<Hal>;
	RTTI_DECL1(CLASSNAME, HalEventsBase)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::EventsBase_Visit(*dev, *this, vis);
		vis.VisitThis<HalEventsBase>(this);
	}
	typename Hal::NativeEventsBase* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::EventsBase_Create(dev))
			return false;
		if (!Hal::EventsBase_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::EventsBase_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::EventsBase_Start(*dev, *this);
	}
	void Stop() override {
		Hal::EventsBase_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::EventsBase_Uninitialize(*dev, *this);
		Hal::EventsBase_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::EventsBase_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::EventsBase_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::EventsBase_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::EventsBase_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::EventsBase_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::EventsBase_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::EventsBase_DetachContext(*dev, *this, a);
	}
};
#if defined flagUPPCORE
template <class Hal> struct HalUppEventsBaseT : HalUppEventsBase {
	using CLASSNAME = HalUppEventsBaseT<Hal>;
	RTTI_DECL1(CLASSNAME, HalUppEventsBase)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::UppEventsBase_Visit(*dev, *this, vis);
		vis.VisitThis<HalUppEventsBase>(this);
	}
	typename Hal::NativeUppEventsBase* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::UppEventsBase_Create(dev))
			return false;
		if (!Hal::UppEventsBase_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::UppEventsBase_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::UppEventsBase_Start(*dev, *this);
	}
	void Stop() override {
		Hal::UppEventsBase_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::UppEventsBase_Uninitialize(*dev, *this);
		Hal::UppEventsBase_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::UppEventsBase_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::UppEventsBase_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::UppEventsBase_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::UppEventsBase_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::UppEventsBase_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::UppEventsBase_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::UppEventsBase_DetachContext(*dev, *this, a);
	}
};
#endif
#if (defined flagOGL && defined flagUPPCORE)
template <class Hal> struct HalUppOglDeviceT : HalUppOglDevice {
	using CLASSNAME = HalUppOglDeviceT<Hal>;
	RTTI_DECL1(CLASSNAME, HalUppOglDevice)
	void Visit(RuntimeVisitor& vis) override {
		if (dev) Hal::UppOglDevice_Visit(*dev, *this, vis);
		vis.VisitThis<HalUppOglDevice>(this);
	}
	typename Hal::NativeUppOglDevice* dev = 0;
	bool Initialize(const Script::WorldState& ws) override {
		if (!Hal::UppOglDevice_Create(dev))
			return false;
		if (!Hal::UppOglDevice_Initialize(*dev, *this, ws))
			return false;
		return true;
	}
	bool PostInitialize() override {
		if (!Hal::UppOglDevice_PostInitialize(*dev, *this))
			return false;
		return true;
	}
	bool Start() override {
		return Hal::UppOglDevice_Start(*dev, *this);
	}
	void Stop() override {
		Hal::UppOglDevice_Stop(*dev, *this);
	}
	void Uninitialize() override {
		ASSERT(this->GetDependencyCount() == 0);
		Hal::UppOglDevice_Uninitialize(*dev, *this);
		Hal::UppOglDevice_Destroy(dev);
	}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Hal::UppOglDevice_Send(*dev, *this, cfg, out, src_ch))
			return false;
		return true;
	}
	bool Recv(int sink_ch, const Packet& in) override {
		return Hal::UppOglDevice_Recv(*dev, *this, sink_ch, in);
	}
	void Finalize(RealtimeSourceConfig& cfg) override {
		return Hal::UppOglDevice_Finalize(*dev, *this, cfg);
	}
	void Update(double dt) override {
		return Hal::UppOglDevice_Update(*dev, *this, dt);
	}
	bool IsReady(PacketIO& io) override {
		return Hal::UppOglDevice_IsReady(*dev, *this, io);
	}
	bool AttachContext(AtomBase& a) override {
		return Hal::UppOglDevice_AttachContext(*dev, *this, a);
	}
	void DetachContext(AtomBase& a) override {
		Hal::UppOglDevice_DetachContext(*dev, *this, a);
	}
};
#endif

#if defined flagSDL2
using SdlAudioSinkDevice = HalAudioSinkDeviceT<HalSdl>;
using SdlCenterVideoSinkDevice = HalCenterVideoSinkDeviceT<HalSdl>;
using SdlCenterFboSinkDevice = HalCenterFboSinkDeviceT<HalSdl>;
#if defined flagOGL
using SdlOglVideoSinkDevice = HalOglVideoSinkDeviceT<HalSdl>;
#endif
#if defined flagDX12
using SdlD12VideoSinkDevice = HalD12VideoSinkDeviceT<HalSdl>;
#endif
using SdlContextBase = HalContextBaseT<HalSdl>;
using SdlEventsBase = HalEventsBaseT<HalSdl>;
#if defined flagUPPCORE
using SdlUppEventsBase = HalUppEventsBaseT<HalSdl>;
#endif
#if (defined flagOGL && defined flagUPPCORE)
using SdlUppOglDevice = HalUppOglDeviceT<HalSdl>;
#endif
#endif
#if (defined flagUWP && defined flagDX12)
using HoloAudioSinkDevice = HalAudioSinkDeviceT<HalHolo>;
using HoloCenterVideoSinkDevice = HalCenterVideoSinkDeviceT<HalHolo>;
using HoloCenterFboSinkDevice = HalCenterFboSinkDeviceT<HalHolo>;
#if defined flagOGL
using HoloOglVideoSinkDevice = HalOglVideoSinkDeviceT<HalHolo>;
#endif
#if defined flagDX12
using HoloD12VideoSinkDevice = HalD12VideoSinkDeviceT<HalHolo>;
#endif
using HoloContextBase = HalContextBaseT<HalHolo>;
using HoloEventsBase = HalEventsBaseT<HalHolo>;
#if defined flagUPPCORE
using HoloUppEventsBase = HalUppEventsBaseT<HalHolo>;
#endif
#if (defined flagOGL && defined flagUPPCORE)
using HoloUppOglDevice = HalUppOglDeviceT<HalHolo>;
#endif
#endif

NAMESPACE_PARALLEL_END

#endif
