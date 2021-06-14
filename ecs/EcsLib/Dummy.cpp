#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN



DummySoundGeneratorAudio::DummySoundGeneratorAudio() {
	fmt.channels = 2;
	fmt.sample_rate = 777;
	fmt.freq = 44100;
	fmt.SetType(SoundSample::U8_LE);
	gen.GenerateStereoSine(fmt);
}

void DummySoundGeneratorAudio::StorePacket(AudioPacket& p) {
	int frame = fmt.GetFrameSize();
	dword off = p->GetOffset().value;
	int64 offset = (int64)off * (int64)frame;
	ASSERT(offset < (int64)std::numeric_limits<int>::max());
	double time = off * fmt.GetFrameSeconds();
	p->Set(fmt, time);
	p->Data().SetCount(frame, 0);
	gen.Play((int)offset, p);
}

/*void DummySoundGeneratorAudio::Exchange(AudioEx& e) {
	TODO
	if (e.IsStoring()) {
		Audio& sink = e.Sink();
		const RealtimeSourceConfig& conf = e.SourceConfig();
		
		AudioVolatileBuffer* vol_aud;
		SimpleBufferedAudio* buf_aud;
		if ((vol_aud = CastPtr<AudioVolatileBuffer>(&sink))) {
			while (!vol_aud->IsQueueFull()) {
				off32 offset = og.Create();
				AudioPacket p = CreateAudioPacket(offset);
				AudioPacketTracker::Track(TrackerInfo(this, __FILE__, __LINE__), p);
				p->Set(fmt, time);
				p->Data().SetCount(fmt.GetFrameSize(), 0);
				gen.Play(p);
				vol_aud->Put(p, false);
				time += fmt.GetFrameSeconds();
			}
		}
		else if ((buf_aud = CastPtr<SimpleBufferedAudio>(&sink))) {
			buf_aud->Exchange(e);
		}
		else TODO
	}
	else TODO
}

int DummySoundGeneratorAudio::GetQueueSize() const {
	return 10;
}

AudioFormat DummySoundGeneratorAudio::GetFormat() const {
	return fmt;
}

bool DummySoundGeneratorAudio::IsQueueFull() const {
	return true;
}*/














DummySoundGeneratorComponent::DummySoundGeneratorComponent() {
	
}

void DummySoundGeneratorComponent::Initialize() {
	Component::Initialize();
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
	
	auto fmt = ScopeDevLibT<CenterSpec>::StageComponent::GetDefaultFormat<OrderSpec>();
	sink_value.SetFormat(fmt);
	
	GetStream(AUDCTX).Get().Lock();
}

void DummySoundGeneratorComponent::Uninitialize() {
	Component::Uninitialize();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

void DummySoundGeneratorComponent::Forward(FwdScope& fwd) {
	using FromValSpec				= OrderSpec;
	using ToValSpec					= AudioSpec;
	using DevSpec					= CenterSpec;
	
	using DevMach					= ScopeDevMachT<DevSpec>;
	using InternalPacketData		= typename DevMach::InternalPacketData;
	
	using FromValDevSpec			= VD<DevSpec, FromValSpec>;
	using FromValMach				= ScopeValMachT<FromValSpec>;
	using FromValDevMach			= ScopeValDevMachT<FromValDevSpec>;
	using FromValDevCore			= ScopeValDevCoreT<FromValDevSpec>;
	using FromPacket				= typename FromValMach::Packet;
	using FromValue					= typename FromValDevMach::Value;
	using FromPacketBuffer			= typename FromValDevMach::PacketBuffer;
	using FromSimpleValue			= typename FromValDevMach::SimpleValue;
	using FromSimpleBufferedValue	= typename FromValDevMach::SimpleBufferedValue;
	using FromSink					= typename FromValDevCore::ValSink;
	#define FROMCTX (FromValSpec*)0
	
	using ToValDevSpec				= VD<DevSpec, ToValSpec>;
	using ToValMach					= ScopeValMachT<ToValSpec>;
	using ToValDevMach				= ScopeValDevMachT<ToValDevSpec>;
	using ToValDevCore				= ScopeValDevCoreT<ToValDevSpec>;
	using ToValLib					= ScopeValLibT<ToValSpec>;
	using ToPacket					= typename ToValMach::Packet;
	using ToFormat					= typename ToValMach::Format;
	using ToValue					= typename ToValDevMach::Value;
	using ToSimpleBufferedValue		= typename ToValDevMach::SimpleBufferedValue;
	using ToSimpleValue				= typename ToValDevMach::SimpleValue;
	using ToSource					= typename ToValDevCore::ValSource;
	using ToSink					= typename ToValDevCore::ValSink;
	using ToSinkRef					= typename ToValDevCore::ValSinkRef;
	using ToPacketTracker			= typename ToValLib::PacketTracker;
	#define TOCTX (ToValSpec*)0
	
	ToSource& iface_src = *this;
	FromSink& iface_sink = *this;
	FromValue& sink_val = iface_sink.GetValue(FROMCTX);
	
	FromSimpleBufferedValue* sink_buf_val;
	FromSimpleValue* sink_sval;
	FromPacketBuffer* sink_buf;
	if ((sink_buf_val = CastPtr<FromSimpleBufferedValue>(&sink_val))) {
		sink_buf = &sink_buf_val->GetBuffer();
	}
	else if ((sink_sval = CastPtr<FromSimpleValue>(&sink_val))) {
		sink_buf = &sink_sval->GetBuffer();
	}
	else TODO
		
	for(FromPacket& p : *sink_buf) {
		RTLOG("DummySoundGeneratorComponent::Forward: play packet " << p->GetOffset().ToString());
		off32 off = p->GetOffset();
		
		ToValue& val = iface_src.GetStream(TOCTX).Get();
		val.Unlock();
		ToSimpleValue* sval;
		ToSimpleBufferedValue* buf;
		if ((sval = CastPtr<ToSimpleValue>(&val))) {
			int c = sval->GetQueueSize();
			while (!sval->IsQueueFull()) {
				ToPacket p = ToValMach::CreatePacket(off);
				
				ToFormat fmt = ScopeDevLibT<DevSpec>::StageComponent::GetDefaultFormat<ToValSpec>();
				RTLOG("DummySoundGeneratorComponent::Forward: sending packet in format: " << fmt.ToString());
				p->SetFormat(fmt);
				
				InternalPacketData& data = p->template SetData<InternalPacketData>();
				data.pos = 0;
				data.count = 1;
				
				sval->StorePacket(p);
				
				ToPacketTracker::Track(TrackerInfo("DummySoundGeneratorComponent::Forward", __FILE__, __LINE__), *p);
				sval->AddPacket(p);
			}
		}
		else if ((buf = CastPtr<ToSimpleBufferedValue>(&val))) {
			ToPacket p = ToValMach::CreatePacket(off);
			
			ToFormat fmt = ScopeDevLibT<DevSpec>::StageComponent::GetDefaultFormat<ToValSpec>();
			RTLOG("DummySoundGeneratorComponent::Forward: sending packet in format: " << fmt.ToString());
			p->SetFormat(fmt);
			
			InternalPacketData& data = p->template SetData<InternalPacketData>();
			data.pos = 0;
			data.count = 1;
			
			StorePacket(p);
			
			ToPacketTracker::Track(TrackerInfo("DummySoundGeneratorComponent::Forward", __FILE__, __LINE__), *p);
			buf->AddPacket(p);
		}
		else {
			TODO
		}
		val.Lock();
	}
	sink_buf->Clear();
	
	#undef FROMCTX
	#undef TOCTX
}

void DummySoundGeneratorComponent::ForwardExchange(FwdScope& fwd) {
	AudioSource& src = *this;
	auto& conns = src.GetConnections();
	for(auto& link : conns) {
		ExchangePointRef expt = link.expt;
		ASSERT(expt);
		if (expt) {
			fwd.AddNext(*expt);
		}
	}
}

#if 0

void DummySoundGeneratorComponent::RecvMidi(const MidiFrame& e) {
	TODO
}

void DummySoundGeneratorComponent::Configure(const Midi::File& file) {
	if (mode == MODE_TRACK_NUM) {
		if (track_i >= 0 && track_i < file.GetTrackCount()) {
			Ref<FluidsynthSystem> fs_sys = GetMachine().Get<FluidsynthSystem>();
			fs_sys->Assign(file, track_i, this);
		}
	}
}

#endif

AudioStream& DummySoundGeneratorComponent::GetStream(AudCtx) {
	return gen;
}

void DummySoundGeneratorComponent::BeginStream(AudCtx) {
	TODO
}

void DummySoundGeneratorComponent::EndStream(AudCtx) {
	TODO
}











void DummyAudioSinkComponent::Forward(FwdScope& fwd) {
	using DevMach = ScopeDevMachT<CenterSpec>;
	using InternalPacketData = typename DevMach::InternalPacketData;
	
	Audio& sink_value = GetValue(AUDCTX);
	Receipt& src_value = GetStream(RCPCTX).Get();
	auto& sink_buf = sink_value.GetBuffer();
	auto& src_buf = src_value.GetBuffer();
	for(AudioPacket& in : sink_buf) {
		Process(in);
		
		ReceiptPacket out = CreateReceiptPacket(in->GetOffset());
		
		ReceiptFormat fmt = ScopeDevLibT<CenterSpec>::StageComponent::GetDefaultFormat<ReceiptSpec>();
		RTLOG("DummyAudioSinkComponent::Forward: sending packet in format: " << fmt.ToString());
		out->SetFormat(fmt);
		
		InternalPacketData& data = out->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = 1;
		
		ReceiptPacketTracker::Track(TrackerInfo("DummyAudioSinkComponent::Forward", __FILE__, __LINE__), *out);
		src_buf.Add(out);
	}
	sink_buf.Clear();
}

void DummyAudioSinkComponent::ForwardExchange(FwdScope& fwd) {
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

void DummyAudioSinkComponent::Process(AudioPacket& p) {
	RTLOG("DummyAudioSinkComponent::Process: omnomnomnomnom... packet " << p->GetOffset().ToString() << " content sunk in the sink hole");
}


NAMESPACE_TOPSIDE_END
