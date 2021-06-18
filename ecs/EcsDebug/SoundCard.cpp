#include "EcsDebug.h"

NAMESPACE_TOPSIDE_BEGIN


#if 0

void DebugAudioSinkComponent::Initialize() {
	auto fmt = ScopeDevLibT<CenterSpec>::StageComponent::GetDefaultFormat<AudioSpec>();
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
		
		StreamCallbackArgs args;
		args.output = data.Begin();
		args.fpb = fmt.GetSampleRate();
		
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
		
		ToFormat fmt = ScopeDevLibT<DevSpec>::StageComponent::GetDefaultFormat<ToValSpec>();
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
	
		ToFormat fmt = ScopeDevLibT<DevSpec>::StageComponent::GetDefaultFormat<ToValSpec>();
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
	if (consumer.IsEmptySource())
		consumer.SetSource(par.sink_value.GetBuffer());
	
	if (args.output) {
		TS::AudioFormat fmt = par.sink_value.GetFormat();
		
		int size = fmt.GetFrameSize();
		int qsize = par.sink_value.GetQueueSize();
		if (qsize > 0 || consumer.HasLeftover()) {
			ASSERT(args.fpb == fmt.sample_rate);
			
			/*off32 begin_offset = buf.GetOffset();
			if (0) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: trying to consume " << begin_offset.ToString());
				RTLOG("BufferedAudioDeviceStream::SinkCallback: dumping");
				buf.Dump();
			}*/
			
			
			consumer.SetDestination(fmt, args.output, size);
			consumer.ConsumeAll(false);
			consumer.ClearDestination();
			int csize = consumer.GetLastMemoryBytes();
			int consumed_count = consumer.GetCount();
			if (csize != size) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: error: consumed " << csize << " (expected " << size << "), packets=" << consumed_count);
			}
			else {
				RTLOG("BufferedAudioDeviceStream::SinkCallback:  consumed " << csize << ", packets=" << consumed_count);
			}
			
			par.lock.Enter();
			par.consumed_packets.Append(consumer.consumed_packets);
			par.lock.Leave();
			
			
			auto sys = par.GetEntity()->GetMachine().TryGet<CustomerSystem>();
			if (sys && par.cfg)
				sys->AddOnce(par, *par.cfg);
			
			/*off32 end_offset = consumer.GetOffset();
			off32 diff = off32::GetDifference(begin_offset, end_offset);
			if (diff) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed count=" << diff.ToString());
				buf.RemoveFirst(diff.value);
			}
			else if (consumer.HasLeftover()) {
				RTLOG("BufferedAudioDeviceStream::SinkCallback: device consumed packet partially");
			}
			else if (!consumer.HasLeftover()) {
				RTLOG("error: BufferedAudioDeviceStream::SinkCallback: device error");
			}*/
		}
		else {
			#if DEBUG_RT_PIPE
			RTLOG("error: BufferedAudioDeviceStream::SinkCallback: got empty data");
			#endif
			
			memset(args.output, 0, size);
		}
	}
}

#endif

NAMESPACE_TOPSIDE_END
