// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IAudio_TmplClasses_h_
#define _IAudio_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Aud> struct AudioSinkDeviceT;
template <class Aud> struct AudioSourceDeviceT;


template <class Aud>
struct AudioSinkDeviceT : AudSinkDevice {
	using CLASSNAME = AudioSinkDeviceT<Aud>;
	RTTI_DECL1(CLASSNAME, AudSinkDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AudSinkDevice>(this);}
	
	typename Aud::NativeSinkDevice dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Aud::SinkDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Aud::SinkDevice_PostInitialize(dev))
			return false;
		return true;
	}

	bool Start() override {
		return Aud::SinkDevice_Start(dev);
	}

	void Stop() override {
		Aud::SinkDevice_Stop(dev);
	}

	void Uninitialize() override {
		Aud::SinkDevice_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Aud::SinkDevice_ProcessPacket(dev, v))
			return false;
		return true;
	}

	int GetSinkDeviceCount() {
		return Aud::SinkDevice_GetSinkDeviceCount();
	}
	
	bool CreateSinkDevice(int sink_i) {
		return Aud::SinkDevice_CreateSinkDevice(sink_i, this->dev);
	}
	
	void ClearSinkDevice() {
		Aud::SinkDevice_ClearSinkDevice(this->dev);
	}
	
	bool SetSinkCallback(void* data, DataCallbackFn cb) {
		return Aud::SinkDevice_SetSinkCallback(data, cb);
	}
	
	int GetSinkFormatCount() {
		return Aud::SinkDevice_GetSinkFormatCount(this->dev);
	}
	
	bool GetSinkFormat(int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
		return Aud::SinkDevice_GetSinkFormat(this->dev, ch_i, channels, samplerate, bytes, is_signed, is_float);
	}
	
	
};

template <class Aud>
struct AudioSourceDeviceT : AudSourceDevice {
	using CLASSNAME = AudioSourceDeviceT<Aud>;
	RTTI_DECL1(CLASSNAME, AudSourceDevice)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AudSourceDevice>(this);}
	
	typename Aud::NativeSourceDevice dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Aud::SourceDevice_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Aud::SourceDevice_PostInitialize(dev))
			return false;
		return true;
	}

	bool Start() override {
		return Aud::SourceDevice_Start(dev);
	}

	void Stop() override {
		Aud::SourceDevice_Stop(dev);
	}

	void Uninitialize() override {
		Aud::SourceDevice_Uninitialize(dev);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Aud::SourceDevice_ProcessPacket(dev, v))
			return false;
		return true;
	}

	int GetSourceDeviceCount() {
		return Aud::SourceDevice_GetSourceDeviceCount();
	}
	
	bool CreateSourceDevice(int sink_i) {
		return Aud::SourceDevice_CreateSourceDevice(sink_i, this->dev);
	}
	
	void ClearSourceDevice() {
		Aud::SourceDevice_ClearSourceDevice(this->dev);
	}
	
	bool SetSourceCallback(void* data, DataCallbackFn cb) {
		return Aud::SourceDevice_SetSourceCallback(data, cb);
	}
	
	int GetSourceFormatCount() {
		return Aud::SourceDevice_GetSourceFormatCount(this->dev);
	}
	
	bool GetSourceFormat(int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
		return Aud::SourceDevice_GetSourceFormat(this->dev, ch_i, channels, samplerate, bytes, is_signed, is_float);
	}
	
	
};

#if (defined flagLINUX) || (defined flagFREEBSD) || (defined flagWIN32)
using PortaudioSinkDevice = AudioSinkDeviceT<AudPortaudio>;
using PortaudioSourceDevice = AudioSourceDeviceT<AudPortaudio>;
#endif


NAMESPACE_PARALLEL_END



#endif

