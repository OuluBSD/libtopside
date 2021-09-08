#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


void AudioFormat::Set(SoundSample::Type type, int channels, int freq, int sample_rate) {
	SampleBase<SoundSample>::SetType(type);
	DimBase<1>::SetSize(channels);
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
}

String AudioFormat::ToString() const {
	return		SampleBase<SoundSample>::ToString() + ", " +
				DimBase<1>::ToString() + ", " +
				TimeSeriesBase::ToString();
}

int AudioFormat::GetFrameSize() const {
	return		DimBase<1>::GetArea() *
				TimeSeriesBase::GetSampleRate() *
				SampleBase<SoundSample>::GetSampleSize();
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









void VideoFormat::Set(LightSampleFD::Type type, int w, int h, int freq, int sample_rate) {
	SampleBase<LightSampleFD>::SetType(type);
	DimBase<2>::SetSize(Size(w,h));
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
}

int VideoFormat::GetFrameSize() const {
	TODO
}

String VideoFormat::ToString() const {
	return		SampleBase<LightSampleFD>::ToString() + ", " +
				DimBase<2>::ToString() + ", " +
				TimeSeriesBase::ToString();
}

bool VideoFormat::IsValid() const {
	return		TimeSeriesBase::IsValid() && \
				SampleBase<LightSampleFD>::IsValid() && \
				DimBase<2>::IsValid();
}

bool VideoFormat::IsSame(const VideoFormat& b) const {
	return		TimeSeriesBase::IsSame(b) &&
				SampleBase<LightSampleFD>::IsCopyCompatible(b) &&
				DimBase<2 >::IsSame(b);
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
	if (IsVideo()) return "VideoFormat(" + vd.ToString() + ", " + vid.ToString() + ")";
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


void Format::SetAudio(DevCls dev, SoundSample::Type t, int channels, int freq, int sample_rate) {
	vd.dev = dev;
	vd.val = ValCls::AUDIO;
	memset(data, 0, sizeof(data));
	aud.Set(t, channels, freq, sample_rate);
}

void Format::SetOrder(DevCls dev) {
	vd.dev = dev;
	vd.val = ValCls::ORDER;
	memset(data, 0, sizeof(data));
}

void Format::SetReceipt(DevCls dev) {
	vd.dev = dev;
	vd.val = ValCls::RECEIPT;
	memset(data, 0, sizeof(data));
}

void Format::SetMidi(DevCls dev) {
	vd.dev = dev;
	vd.val = ValCls::MIDI;
	memset(data, 0, sizeof(data));
	mid.SetDefault();
}

void Format::SetVideo(DevCls dev, LightSampleFD::Type t, int w, int h, int freq, int sample_rate) {
	vd.dev = dev;
	vd.val = ValCls::VIDEO;
	memset(data, 0, sizeof(data));
	vid.Set(t, w, h, freq, sample_rate);
}

void Format::operator=(const Format& f) {
	vd = f.vd;
	memcpy(data, f.data, sizeof(data));
}


NAMESPACE_SERIAL_END
