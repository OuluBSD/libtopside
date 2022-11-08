#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN


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
	return		DimBase<1>::GetScalar() *
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
	DimBase<2>::operator=(Size(w,h));
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
	cubemap = false;
}

int VideoFormat::GetFrameSize() const {
	return		SampleBase<LightSampleFD>::GetSampleSize() *
				DimBase<2>::GetScalar() *
				TimeSeriesBase::GetSampleRate();
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




void VolumeFormat::Set(BinarySample::Type type, int w, int h, int d, int freq, int sample_rate) {
	SampleBase<BinarySample>::SetType(type);
	DimBase<3>::operator=(Size3(w,h,d));
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
}

int VolumeFormat::GetFrameSize() const {
	return		SampleBase<BinarySample>::GetSampleSize() *
				DimBase<3>::GetVolume() *
				TimeSeriesBase::GetSampleRate();
}

String VolumeFormat::ToString() const {
	return		SampleBase<BinarySample>::ToString() + ", " +
				DimBase<3>::ToString() + ", " +
				TimeSeriesBase::ToString();
}

bool VolumeFormat::IsValid() const {
	return		TimeSeriesBase::IsValid() && \
				SampleBase<BinarySample>::IsValid() && \
				DimBase<3>::IsValid();
}

bool VolumeFormat::IsSame(const VolumeFormat& b) const {
	return		TimeSeriesBase::IsSame(b) &&
				SampleBase<BinarySample>::IsCopyCompatible(b) &&
				DimBase<3>::IsSame(b);
}

bool VolumeFormat::IsCopyCompatible(const VolumeFormat& b) const {
	return		SampleBase<BinarySample>::IsCopyCompatible(b);
}





void FboFormat::Set(BinarySample::Type t, int w, int h, int d, int freq, int sample_rate) {
	SampleBase<BinarySample>::SetType(t);
	DimBase<3>::operator=(Size3(w,h,d));
	TimeSeriesBase::SetTimeSeries(freq, sample_rate);
}

int FboFormat::GetFrameSize() const {
	return		SampleBase<BinarySample>::GetSampleSize() *
				DimBase<3>::GetScalar() *
				TimeSeriesBase::GetSampleRate();
}

String FboFormat::ToString() const {
	return		SampleBase<BinarySample>::ToString() + ", " +
				DimBase<3>::ToString() + ", " +
				TimeSeriesBase::ToString();
}

bool FboFormat::IsValid() const {
	return		TimeSeriesBase::IsValid() && \
				SampleBase<BinarySample>::IsValid() && \
				DimBase<3>::IsValid2D();
}

bool FboFormat::IsSame(const FboFormat& b) const {
	return		TimeSeriesBase::IsSame(b) &&
				SampleBase<BinarySample>::IsCopyCompatible(b) &&
				DimBase<3>::IsSame(b);
}




int MidiFormat::GetFrameSize() const {
	return		SampleBase<MidiSample>::GetSampleSize() *
				DimBase<1>::GetScalar() *
				SparseTimeSeriesBase::GetSampleRate();
}

String MidiFormat::ToString() const {
	return		SampleBase<MidiSample>::ToString() + ", " +
				DimBase<1>::ToString() + ", " +
				SparseTimeSeriesBase::ToString();
}

bool MidiFormat::IsValid() const {
	return true;
}

bool MidiFormat::IsSame(const MidiFormat& fmt) const {
	return true;
}







String EventFormat::ToString() const {
	return		SampleBase<EventSample>::ToString() + ", " +
				DimBase<1>::ToString() + ", " +
				SparseTimeSeriesBase::ToString();
}

bool EventFormat::IsValid() const {
	return true;
}

bool EventFormat::IsSame(const EventFormat& fmt) const {
	return true;
}

int EventFormat::GetFrameSize() const {
	return		DimBase<1>::GetScalar() *
				SparseTimeSeriesBase::GetSampleRate() *
				SampleBase<EventSample>::GetSampleSize();
}








String ProgFormat::ToString() const {
	return		SampleBase<BinarySample>::ToString() + ", " +
				DimBase<1>::ToString() + ", " +
				SparseTimeSeriesBase::ToString();
}

bool ProgFormat::IsValid() const {
	return true;
}

bool ProgFormat::IsSame(const ProgFormat& fmt) const {
	return true;
}

int ProgFormat::GetFrameSize() const {
	return		DimBase<1>::GetScalar() *
				SparseTimeSeriesBase::GetSampleRate() *
				SampleBase<BinarySample>::GetSampleSize();
}








#define PROXY(x) \
	if (IsAudio()) return aud.x(); \
	if (IsVideo()) return vid.x(); \
	if (IsVolume()) return vol.x(); \
	if (IsMidi())  return mid.x(); \
	if (IsEvent()) return ev.x(); \
	if (IsFbo())   return fbo.x(); \
	if (IsProg())  return prog.x(); \
	PANIC("Invalid type");

#define PROXY_(x,y) \
	if (IsAudio()) return aud.x((const AudioFormat&)y); \
	if (IsVideo()) return vid.x((const VideoFormat&)y); \
	if (IsVolume()) return vol.x((const VolumeFormat&)y); \
	if (IsMidi())  return mid.x((const MidiFormat&)y); \
	if (IsEvent()) return ev.x((const EventFormat&)y); \
	if (IsFbo())   return fbo.x((const FboFormat&)y); \
	if (IsProg())  return prog.x((const ProgFormat&)y); \
	PANIC("Invalid type");

#define PROXY_CHK(x) ASSERT(IsValid()); PROXY(x)

#define PROXY_CHK_(x,y) ASSERT(IsValid()); PROXY_(x,y)

String Format::ToString() const {
	if (IsAudio()) return "AudioFormat(" + vd.ToString() + ", " + aud.ToString() + ")";
	if (IsVideo()) return "VideoFormat(" + vd.ToString() + ", " + vid.ToString() + ")";
	if (IsVolume()) return "VolumeFormat(" + vd.ToString() + ", " + vol.ToString() + ")";
	if (IsMidi())  return "MidiFormat(" + vd.ToString() + ", " + mid.ToString() + ")";
	if (IsEvent()) return "EventFormat(" + vd.ToString() + ", " + ev.ToString() + ")";
	if (IsFbo())   return "FboFormat(" + vd.ToString() + ", " + fbo.ToString() + ")";
	if (IsProg())   return "ProgFormat(" + vd.ToString() + ", " + prog.ToString() + ")";
	if (vd.val.type == ValCls::ORDER) return "OrderFormat";
	if (vd.val.type == ValCls::RECEIPT) return "ReceiptFormat";
	return "Invalid Format";
}

int Format::GetSampleSize() const {
	PROXY_CHK(GetSampleSize)
}

int Format::GetScalar() const {
	PROXY_CHK(GetScalar)
}

int Format::GetFrameSize() const {
	PROXY_CHK(GetFrameSize)
}

double Format::GetFrameSeconds() const {
	PROXY_CHK(GetFrameSeconds)
}

bool Format::HasData() const {
	return	vd.val != ValCls::ORDER &&
			vd.val != ValCls::RECEIPT;
}

bool Format::IsValid() const {
	if (!vd.IsValid()) return false;
	if (!HasData()) return true;
	PROXY(IsValid)
}

bool Format::IsSame(const Format& f) const {
	if (vd != f.vd) return false;
	if (!HasData()) return true;
	PROXY_CHK_(IsSame, f)
}

bool Format::IsCopyCompatible(const Format& f) const {
	if (vd != f.vd) return false;
	if (!HasData()) return true;
	PROXY_CHK_(IsCopyCompatible, f)
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

void Format::SetVolume(DevCls dev, BinarySample::Type t, int w, int h, int d, int freq, int sample_rate) {
	vd.dev = dev;
	vd.val = ValCls::VOLUME;
	memset(data, 0, sizeof(data));
	vol.Set(t, w, h, d, freq, sample_rate);
	ASSERT(IsValid());
}

void Format::SetVideo(DevCls dev, LightSampleFD::Type t, int w, int h, int freq, int sample_rate) {
	vd.dev = dev;
	vd.val = ValCls::VIDEO;
	memset(data, 0, sizeof(data));
	vid.Set(t, w, h, freq, sample_rate);
}

void Format::SetVideo(DevCls dev, const VideoFormat& vid) {
	vd.dev = dev;
	vd.val = ValCls::VIDEO;
	memset(data, 0, sizeof(data));
	this->vid = vid;
}

void Format::SetFbo(DevCls dev, BinarySample::Type t, int w, int h, int d, int freq, int sample_rate) {
	vd.dev = dev;
	vd.val = ValCls::FBO;
	memset(data, 0, sizeof(data));
	fbo.Set(t, w, h, d, freq, sample_rate);
	ASSERT(IsValid());
}

void Format::SetEvent(DevCls dev) {
	vd.dev = dev;
	vd.val = ValCls::EVENT;
	memset(data, 0, sizeof(data));
}

void Format::SetProg(DevCls dev) {
	vd.dev = dev;
	vd.val = ValCls::PROG;
	memset(data, 0, sizeof(data));
}

void Format::operator=(const Format& f) {
	vd = f.vd;
	memcpy(data, f.data, sizeof(data));
}



GVar::Sample GetGVarSampleFromBinarySample(BinarySample::Type t) {
	int sz = Parallel::BinarySample::GetPackedSingleSize(t);
	if (Parallel::BinarySample::IsFloating(t)) {
		if (sz == 4)
			return GVar::SAMPLE_FLOAT;
	}
	else {
		switch (sz) {
			case 1:	return GVar::SAMPLE_U8;
			case 2:	return GVar::SAMPLE_U16;
			case 4:	return Parallel::BinarySample::IsSigned(t) ? GVar::SAMPLE_S32 : GVar::SAMPLE_U32;
			default: break;
		}
	}
	Panic("GetGvarSampleFromBinarySample: conversion failed");
	NEVER();
}

NAMESPACE_PARALLEL_END
