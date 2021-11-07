#include "SerialCore.h"

NAMESPACE_SERIAL_BEGIN


bool& EnvState::SetBool(dword key, bool b) {
	Object& o = data.GetAdd(key);
	return o.Set<bool>(b);
}

int& EnvState::SetInt(dword key, int i) {
	Object& o = data.GetAdd(key);
	return o.Set<int>(i);
}

bool& EnvState::GetBool(dword key) {
	Object& o = data.GetAdd(key);
	if (o.Is<bool>())
		return o.Get<bool>();
	else
		return o.Create<bool>(false);
}

int& EnvState::GetInt(dword key) {
	Object& o = data.GetAdd(key);
	if (o.Is<int>())
		return o.Get<int>();
	else
		return o.Create<int>(0);
}


NAMESPACE_SERIAL_END
