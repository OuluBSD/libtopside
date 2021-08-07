#include "TemplatesMach.h"


NAMESPACE_ECS_BEGIN


void AudioFormat::Set(SoundSample::Type type, int channels, int freq, int sample_rate) {
	SampleBase<SoundSample>::SetType(type);
	DimBase<1>::SetSize(2);
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
}

String AudioFormat::ToString() const {
	return SampleBase<SoundSample>::ToString() + ", " + DimBase<1>::ToString() + ", " + TimeSeriesBase::ToString() + ", " + SampleBase<SoundSample>::ToString();
}

int AudioFormat::GetFrameSize() const {
	return DimBase<1>::GetArea() * TimeSeriesBase::GetSampleRate() * SampleBase<SoundSample>::GetSampleSize();
}

bool AudioFormat::IsValid() const {
	return		TimeSeriesBase::IsValid() && \
				SampleBase<SoundSample>::IsValid() && \
				DimBase<1>::IsValid();
}

bool AudioFormat::IsSame(const AudioFormat& b) const {
	return		TimeSeriesBase::IsSame(b) &&
				SampleBase<SoundSample>::IsCopyCompatible(b) &&
				DimBase<1>::IsSame(b);
}









int VideoFormat::GetFrameSize() const {
	TODO
}

String VideoFormat::ToString() const {
	TODO
}

bool VideoFormat::IsValid() const {
	TODO
}

bool VideoFormat::IsSame(const VideoFormat& fmt) const {
	TODO
}



int MidiFormat::GetFrameSize() const {
	TODO
}

String MidiFormat::ToString() const {
	TODO
}

bool MidiFormat::IsValid() const {
	return true;
}

bool MidiFormat::IsSame(const MidiFormat& fmt) const {
	return true;
}



#define PROXY(x,y) \
	if (IsAudio()) return aud.x(y); \
	if (IsVideo()) return vid.x(y); \
	if (IsMidi())  return mid.x(y); \
	PANIC("Invalid type");
#define PROXY_CHK(x,y) ASSERT(IsValid()); PROXY(x,y)

String Format::ToString() const {
	if (IsAudio()) return "AudioFormat(" + vd.ToString() + ", " + aud.ToString() + ")";
	if (IsVideo()) return "VideoFormat(" + vd.ToString() + ", " + aud.ToString() + ")";
	if (vd.val.type == ValCls::ORDER) return "OrderFormat";
	if (vd.val.type == ValCls::RECEIPT) return "ReceiptFormat";
	return "Invalid Format";
}

int Format::GetSampleSize() const {
	PROXY_CHK(GetSampleSize,)
}

int Format::GetArea() const {
	PROXY_CHK(GetArea,)
}

int Format::GetFrameSize() const {
	PROXY_CHK(GetFrameSize,)
}

double Format::GetFrameSeconds() const {
	PROXY_CHK(GetFrameSeconds,)
}

int Format::GetMinBufSamples() const {
	PROXY_CHK(GetMinBufSamples,)
}

bool Format::HasData() const {
	return	vd.val != ValCls::ORDER &&
			vd.val != ValCls::RECEIPT;
}

bool Format::IsValid() const {
	if (!vd.IsValid()) return false;
	if (!HasData()) return true;
	PROXY(IsValid,)
}

bool Format::IsSame(const Format& f) const {
	if (vd != f.vd) return false;
	if (!HasData()) return true;
	PROXY_CHK(IsSame, f)
}

bool Format::IsCopyCompatible(const Format& f) const {
	if (vd != f.vd) return false;
	if (!HasData()) return true;
	PROXY_CHK(IsCopyCompatible, f)
}

bool Format::operator ==(const Format& f) {
	return IsSame(f);
}

bool Format::operator !=(const Format& f) {
	return !IsSame(f);
}

void Format::SetDefault(ValDevCls t) {
	TODO
}

void Format::Clear() {
	vd.Clear();
	memset(data, 0, sizeof(data));
}


void Format::SetAudio(SoundSample::Type t, int channels, int freq, int sample_rate) {
	vd = VD(CENTER, AUDIO);
	aud.Set(t, channels, freq, sample_rate);
}

void Format::SetOrder() {
	vd = VD(CENTER, ORDER);
	memset(data, 0, sizeof(data));
}

void Format::SetReceipt() {
	vd = VD(CENTER, RECEIPT);
	memset(data, 0, sizeof(data));
}

void Format::SetMidi() {
	vd = VD(CENTER, MIDI);
	memset(data, 0, sizeof(data));
	mid.SetDefault();
}

void Format::operator=(const Format& f) {
	vd = f.vd;
	memcpy(data, f.data, sizeof(data));
}



String PacketValue::ToString() const {
	String s;
	s.Cat('{');
	s << "size: " << data.GetCount();
	s << ", id: " << IntStr64(id);
	s<< ", format: {" << fmt.ToString() << "}";
	
	s.Cat('}');
	return s;
}







void ValStreamState::Clear() {
	fmt.Clear();
	sink_frame = 0;
	is_sync = 0;
	
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

void ValStreamState::Reset() {
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

void ValStreamState::Step() {
	frames++;
	frame_time.Reset();
}



#if HAVE_OPENGL

bool PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

#endif












void PacketBufferBase::StorePacket(Packet& p) {
	if (buf.GetCount()) {
		Packet n = buf.First();
		buf.RemoveFirst();
		
		n->SetOffset(p->GetOffset());
		p = n;
	}
}



NAMESPACE_ECS_END
