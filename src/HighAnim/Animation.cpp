#include "HighAnim.h"

NAMESPACE_TOPSIDE_BEGIN


Animation::Animation() {
	
}

void Animation::Clear() {
	scenes.Clear();
	active_scene = 0;
}

AnimScene& Animation::AddScene(String name) {
	AnimScene& s = scenes.Add();
	s.name = name;
	return s;
}

int Animation::GetKeysFromTime(double seconds) {
	int i = (int)(seconds * keys_per_second);
	return i;
}


NAMESPACE_TOPSIDE_END
