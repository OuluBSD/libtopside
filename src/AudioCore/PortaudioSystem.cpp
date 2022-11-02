#include "AudioCore.h"


NAMESPACE_TOPSIDE_BEGIN;
namespace Portaudio {

AudioDevice::AudioDevice(int n): index(n){
	if (n == paNoDevice) {
		index = 0;
		name = "Null";
		return;
	}
	const PaDeviceInfo* dev = Pa_GetDeviceInfo(index);
	name = dev->name;
	api = dev->hostApi;
	input_channels = dev->maxInputChannels;
	output_channels = dev->maxOutputChannels;
	low_input_latency = dev->defaultLowInputLatency;
	low_output_latency = dev->defaultLowOutputLatency;
	high_input_latency = dev->defaultHighInputLatency;
	high_output_latency = dev->defaultHighOutputLatency;
	sample_rate = dev->defaultSampleRate;
}

String AudioDevice::ToString() const {
	String s;
	s	<< name << " (index=" << index
		<< ", in/out=" << input_channels << "/" << output_channels
		<< ", API=" << api << ")";
	return s;
}

AudioAPI::AudioAPI(int n): index(n) {
	const PaHostApiInfo* a = Pa_GetHostApiInfo(index);
	name = a->name;
	type = a->type;
	device_count = a->deviceCount;
	default_input_dev = a->defaultInputDevice;
	default_output_dev = a->defaultOutputDevice;
}

String AudioAPI::ToString() const {
	return String().Cat() << name;
}











bool AudioSystem::exists = false;

GLOBAL_VAR(AudioSystem, AudioSys);




AudioSystem::AudioSystem() {
	ASSERT_(!exists, "AudioSystem already instantiated!");
	err = Pa_Initialize();
	CHECK_ERR;
	exists = true;
}

AudioSystem::~AudioSystem() {
	Close();
}

void AudioSystem::Close() {
	if (exists) {
		err = Pa_Terminate();
		CHECK_ERR;
		exists = false;
	}
}

int AudioSystem::GetCount() const {
	err = Pa_GetDeviceCount();
	CHECK_ERR;
	return err;
}

int AudioSystem::GetAPICount() const {
	err = Pa_GetHostApiCount();
	CHECK_ERR;
	return err;
}

const Vector<AudioDevice> AudioSystem::GetDevices() const {
	Vector<AudioDevice> v;
	for (int i = 0;i < GetCount();i++)
		v.Add(AudioDevice(i));
	return v;
}
const Vector<AudioAPI> AudioSystem::GetAPIs() const {
	Vector<AudioAPI> v;
	for (int i = 0;i < GetAPICount();i++)
		v.Add(AudioAPI(i));
	return v;
}

const AudioDevice AudioSystem::GetDefaultInput() const {
	int n = Pa_GetDefaultInputDevice();
	return AudioDevice((n < 0) ? 0 : n);
}

const AudioDevice AudioSystem::GetDefaultOutput() const {
	int n = Pa_GetDefaultOutputDevice();
	return AudioDevice((n < 0) ? 0 : n);
}

const AudioAPI AudioSystem::GetDefaultAPI() const {
	int n = Pa_GetDefaultHostApi();
	return AudioAPI((n < 0) ? 0 : n);
}

const AudioDevice AudioSystem::Get(int n) const {
	return AudioDevice((n >= 0 && n < GetCount()) ? n : 0);
}

const AudioAPI AudioSystem::GetAPI(int n) const {
	return AudioAPI((n >= 0 && n < GetAPICount()) ? n : 0);
}

String AudioSystem::ToString() const {
	String s = "APIs:\n";
	for (int i = 0;i < GetAPICount();i++) {
		s << "[" << i << "] = " << AudioAPI(i) << '\n';
	}
	s << "\nDevices:\n";
	for (int i = 0;i < GetCount();i++) {
		s << "[" << i << "] = " << AudioDevice(i) << '\n';
	}
	return s;
}








AudioOutStream::AudioOutStream() {
	
}

void AudioOutStream::Put(const Record& rec) {
	TODO
}

bool AudioOutStream::IsOpen() const {
	TODO
}

AudioOutStream AudioOutStream::OpenDefault() {
	TODO
}



}
NAMESPACE_TOPSIDE_END;



#if defined flagBUILTIN_PORTAUDIO || defined BUILTIN_PORTAUDIO
INITBLOCK_(PortaudioSystem) {
	// Check if the sizes of types match current platform
	ASSERT_((sizeof(PaUint16) == 2) &&
	        (sizeof(PaInt16)  == 2) &&
	        (sizeof(PaUint32) == 4) &&
	        (sizeof(PaInt32)  == 4),
	        "PortAudio: type sizes in <portaudio/pa_types.h> does not match your platform");
}
#endif
