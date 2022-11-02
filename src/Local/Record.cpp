#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;





Record::Record() {
	
}

Record::Record(const Record& r) {
	
}


void Record::operator=(const Record& r) {
	
}

void Record::Clear() {
	if (data) {
		data->Retain();
		data = 0;
	}
}

void Record::SetData(FFT1& fft, int ch, int pos, int count) {
	TODO
}

#define PROXY_TO_DATA(x, def) if (data) data->buffer.x; return def;

int Record::GetSampleRate() const {
	PROXY_TO_DATA(GetSampleRate(), 0)
}

float Record::Get(int ch, int i) const {
	PROXY_TO_DATA(Get(ch, i), 0)
}

int Record::GetCount() const {
	PROXY_TO_DATA(GetCount(), 0)
}

int Record::GetChannels() const {
	PROXY_TO_DATA(GetChannels(), 0)
}

bool Record::IsEmpty() const {
	return !data;
}









Record StreamRecord::LoadAny(String path) {
	TODO
}


NAMESPACE_TOPSIDE_END
