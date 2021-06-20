#include "EcsDebug.h"

NAMESPACE_TOPSIDE_BEGIN


#if 0

void DebugAudioSinkComponent::Initialize() {
	auto fmt = ScopeDevCoreT<CenterSpec>::GetDefaultFormat<AudioSpec>();
	sink_value.SetFormat(fmt);
	sink_value.SetMinBufSamples(fmt.GetSampleRate() * 2);
	
	flag.Start(1);
	Thread::Start(THISBACK(FakeHardwareProcess));
}

void DebugAudioSinkComponent::Uninitialize() {
	flag.Stop();
}

void DebugAudioSinkComponent::FakeHardwareProcess() {
	AudioFormat fmt = sink_value.GetFormat();
	Vector<byte> data;
	data.SetCount(fmt.GetFrameSize());
	double step_s = fmt.GetFrameSeconds();
	TimeStop ts;
	while (flag.IsRunning()) {
		double t = ts.Seconds();
		
		if (t < step_s) {
			Sleep(1);
			continue;
		}
		ts.Reset();
		
		StreamCallbackArgs	args;
		args.output			= data.Begin();
		args.size			= data.GetCount();
		args.fpb			= fmt.GetSampleRate();
		
		sink_value.SinkCallback(args);
	}
	flag.DecreaseRunning();
}

void DebugAudioSinkComponent::Forward(FwdScope& fwd) {
	using FromValSpec				= AudioSpec;
	using ToValSpec					= ReceiptSpec;
	using DevSpec					= CenterSpec;
	
	using DevMach					= ScopeDevMachT<DevSpec>;
	using InternalPacketData		= typename DevMach::InternalPacketData;
	
	using FromValDevSpec			= VD<DevSpec, FromValSpec>;
	using FromValMach				= ScopeValMachT<FromValSpec>;
	using FromValDevMach			= ScopeValDevMachT<FromValDevSpec>;
	using FromValDevCore			= ScopeValDevCoreT<FromValDevSpec>;
	using FromPacket				= typename FromValMach::Packet;
	
	using ToValDevSpec				= VD<DevSpec, ToValSpec>;
	using ToValMach					= ScopeValMachT<ToValSpec>;
	using ToValDevMach				= ScopeValDevMachT<ToValDevSpec>;
	using ToValDevCore				= ScopeValDevCoreT<ToValDevSpec>;
	using ToValLib					= ScopeValLibT<ToValSpec>;
	using ToPacket					= typename ToValMach::Packet;
	using ToFormat					= typename ToValMach::Format;
	using ToPacketTracker			= typename ToValLib::PacketTracker;
	
	Audio& sink_value = GetValue(AUDCTX);
	//Receipt& src_value = GetStream(RCPCTX).Get();
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	
	cfg = &fwd.Cfg();
	
	/*
	while (sink_buf.GetCount() && !src_value.IsQueueFull()) {
		FromPacket in = sink_buf.First();
		sink_buf.RemoveFirst();
		
		Process(in);
		
		ToPacket to = ToValMach::CreatePacket(in->GetOffset());
		
		ToFormat fmt = ScopeDevCoreT<DevSpec>::GetDefaultFormat<ToValSpec>();
		RTLOG("DebugAudioSinkComponent::Forward: sending packet in format: " << fmt.ToString());
		to->SetFormat(fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		src_value.StorePacket(to);
		
		ToPacketTracker::Track(TrackerInfo("DebugSoundGeneratorComponent::Forward", __FILE__, __LINE__), *to);
		src_buf.Add(to);
	}*/
	
	lock.Enter();
	
	Index<dword> offs;
	for (auto& in : consumed_packets) {
		off32 o = in->GetOffset();
		if (offs.Find(o.value) >= 0)
			continue;
		offs.Add(o.value);
		
		ToPacket to = ToValMach::CreatePacket(o);
	
		ToFormat fmt = ScopeDevCoreT<DevSpec>::GetDefaultFormat<ToValSpec>();
		RTLOG("DebugAudioSinkComponent::Forward: sending packet in format: " << fmt.ToString());
		to->SetFormat(fmt);
		
		InternalPacketData& data = to->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		src_value.StorePacket(to);
		
		ToPacketTracker::Track(TrackerInfo("DebugSoundGeneratorComponent::Forward", __FILE__, __LINE__), *to);
		src_buf.Add(to);
	}
	
	lock.Leave();
}

void DebugAudioSinkComponent::ForwardExchange(FwdScope& fwd) {
	auto& src_buf = src_value.GetBuffer();
	if (!src_buf.IsEmpty()) {
		ReceiptSource& src = *this;
		auto& conns = src.GetConnections();
		for(auto& link : conns) {
			ExchangePointRef expt = link.expt;
			ASSERT(expt);
			if (expt) {
				fwd.AddNext(*expt);
			}
		}
	}
}

void DebugAudioSinkComponent::Process(AudioPacket& p) {
	RTLOG("DebugAudioSinkComponent::Process: omnomnomnomnom... packet " << p->GetOffset().ToString() << " content sunk in the sink hole");
}



void DebugAudioSinkComponent::LocalSinkValue::SinkCallback(StreamCallbackArgs& args) {
	if (args.output) {
		ASSERT(args.fpb == GetValue(AUDCTX).GetFormat().sample_rate);
		par.ForwardMem(args.output, args.size);
	}
}

#endif

NAMESPACE_TOPSIDE_END
