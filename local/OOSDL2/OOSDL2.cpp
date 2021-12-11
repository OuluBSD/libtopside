#include <AtomSDL2/AtomSDL2.h>

NAMESPACE_SDL2_BEGIN


const char* def_shader = R"SH4D3R(
#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = iTime;
    bool mode = mod(t, 6.0) > 3.0;
    //t = t * 504;
    //t = t * 0.2;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    if (mode)
        fragColor = vec4(
            fragCoord.x / res.x + shift.x,
            fragCoord.y / res.y + shift.y,
            1.0 - fragCoord.y / res.y + shift.z, 0);
    else
        fragColor = vec4(fragCoord.y/res.y + shift.x, (shift.y + 1.0) * 0.5, fragCoord.x/res.x, 0);
}
)SH4D3R";


void Bundle::AddDefaultComponents() {
	GetAddComponent<Timer>();
	if (IsEnabled(AUDIO_IN))	GetAddComponent<AudioInput>();
	if (IsEnabled(AUDIO_OUT))	GetAddComponent<AudioOutput>();
#ifdef flagSCREEN
	if (IsEnabled(SCREEN))		GetAddComponent<OglScreen>();
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
