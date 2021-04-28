#include "System.h"
#include "Internal.h"
#include "Sound.h"

NAMESPACE_OULU_BEGIN;

SoundDevice::SoundDevice(int n):index(n){
	if(n==paNoDevice){
		index=0;
		name="Null";
		return;
	}
	const PaDeviceInfo* dev=Pa_GetDeviceInfo(index);
	name=dev->name;
	API=dev->hostApi;
	InputChannels=dev->maxInputChannels;
	OutputChannels=dev->maxOutputChannels;
	LowInputLatency=dev->defaultLowInputLatency;
	LowOutputLatency=dev->defaultLowOutputLatency;
	HighInputLatency=dev->defaultHighInputLatency;
	HighOutputLatency=dev->defaultHighOutputLatency;
	SampleRate=dev->defaultSampleRate;
}

String SoundDevice::ToString()const{
	return Format("%s (index= %d, in/out= %d/%d, API= %d",name,index,InputChannels,OutputChannels,API);
}

SoundAPI::SoundAPI(int n):index(n){
	const PaHostApiInfo* a=Pa_GetHostApiInfo(index);
	name=a->name;
	type=a->type;
	deviceCount=a->deviceCount;
	defaultInputDevice=a->defaultInputDevice;
	defaultOutputDevice=a->defaultOutputDevice;
}

String SoundAPI::ToString()const{
	return String().Cat() << name;
}

/* SoundSystem */

bool SoundSystem::exists = false;

GLOBAL_VAR(SoundSystem, SoundSys);

SoundSystem::SoundSystem(){
	ASSERT_(!exists,"SoundSystem already instantiated!");
	err=Pa_Initialize();
	CHECK_ERR;
	exists=true;
}

SoundSystem::~SoundSystem(){
	Close();
}

void SoundSystem::Close() {
	if (exists) {
		err=Pa_Terminate();
		CHECK_ERR;
		exists=false;
	}
}

int SoundSystem::GetCount()const{
	err=Pa_GetDeviceCount();
	CHECK_ERR;
	return err;
}

int SoundSystem::GetAPICount()const{
	err=Pa_GetHostApiCount();
	CHECK_ERR;
	return err;
}

const Vector<SoundDevice> SoundSystem::GetDevices()const{
	Vector<SoundDevice> v;
	for(int i=0;i<GetCount();i++)
		v.Add(SoundDevice(i));
	return v;
}
const Vector<SoundAPI> SoundSystem::GetAPIs()const{
	Vector<SoundAPI> v;
	for(int i=0;i<GetAPICount();i++)
		v.Add(SoundAPI(i));
	return v;
}

const SoundDevice SoundSystem::GetDefaultInput()const{
	int n=Pa_GetDefaultInputDevice();
	return SoundDevice((n<0)?0:n);
}

const SoundDevice SoundSystem::GetDefaultOutput()const{
	int n=Pa_GetDefaultOutputDevice();
	return SoundDevice((n<0)?0:n);
}

const SoundAPI SoundSystem::GetDefaultAPI()const{
	int n=Pa_GetDefaultHostApi();
	return SoundAPI((n<0)?0:n);
}

const SoundDevice SoundSystem::Get(int n)const{
	return SoundDevice((n>=0&&n<GetCount())?n:0);
}

const SoundAPI SoundSystem::GetAPI(int n)const{
	return SoundAPI((n>=0&&n<GetAPICount())?n:0);
}

String SoundSystem::ToString()const{
	String s="APIs:\n";
	for(int i=0;i<GetAPICount();i++){
		s<<"["<<i<<"] = "<<SoundAPI(i)<<'\n';
	}
	s<<"\nDevices:\n";
	for(int i=0;i<GetCount();i++){
		s<<"["<<i<<"] = "<<SoundDevice(i)<<'\n';
	}
	return s;
}








SoundOutStream::SoundOutStream() {
	
}

void SoundOutStream::Put(const Record& rec) {
	TODO
}

bool SoundOutStream::IsOpen() const {
	TODO
}

SoundOutStream SoundOutStream::OpenDefault() {
	TODO
}


	
NAMESPACE_OULU_END;



#if defined flagBUILTIN_PORTAUDIO || defined BUILTIN_PORTAUDIO
INITBLOCK {
	// Check if the sizes of types match current platform
	ASSERT_((sizeof(PaUint16) == 2) &&
	        (sizeof(PaInt16)  == 2) &&
	        (sizeof(PaUint32) == 4) &&
	        (sizeof(PaInt32)  == 4),
	        "PortAudio: type sizes in <plugin/portaudio/pa_types.h> does not match your platform");
}
#endif
