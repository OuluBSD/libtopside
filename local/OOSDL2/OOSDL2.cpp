#include <AtomSDL2/AtomSDL2.h>

NAMESPACE_SDL2_BEGIN


void Bundle::AddDefaultComponents() {
	GetAddComponent<Timer>();
	if (IsEnabled(AUDIO_IN))	GetAddComponent<AudioInput>();
	if (IsEnabled(AUDIO_OUT))	GetAddComponent<AudioOutput>();
#ifdef flagSCREEN
	if (IsEnabled(SCREEN))		GetAddComponent<Screen>();
#endif
	if (IsEnabled(EVENTS))		GetAddComponent<Events>();
	if (IsEnabled(JOYSTICK))	GetAddComponent<Joystick>();
	if (IsEnabled(GAMECTRL))	GetAddComponent<GameController>();
	if (IsEnabled(SENSOR))		GetAddComponent<Sensor>();
}

bool Bundle::Open() {
	Context* ctx = this;
	
	if (comps.IsEmpty())
		AddDefaultComponents();
	
	
	for (Component& c : comps)
		Context::Add(c);
	
	return Context::Open();
}

void Bundle::Close() {
	return Context::Close();
}



PacketBuffer& Component::GetSinkBuffer() {
	ASSERT(ab);
	const int sink_ch_i = 0;
	Value& sink_val = ab->GetSink()->GetValue(sink_ch_i);
	return sink_val.GetBuffer();
}

NAMESPACE_SDL2_END
