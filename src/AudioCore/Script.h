#ifndef _AudioCore_SCRIPT_H
#define _AudioCore_SCRIPT_H


NAMESPACE_AUDIO_BEGIN

class Script : public Audio {
public:


	struct Message : Moveable<Message> {
		long type;
		long channel;
		float time;
		Vector<float> float_values;
		Vector<long> int_values;
		String remainder;


		Message()
			: type(0), channel(0), time(0.0f) {
			float_values.SetCount(2, 0);
			int_values.SetCount(2, 0);
		}
		Message(const Message& m) {
			*this = m;
		}
		void operator=(const Message& m) {
			type = m.type;
			channel = m.channel;
			time = m.time;
			float_values <<= m.float_values;
			int_values <<= m.int_values;
			remainder = m.remainder;
		}
	};

	Script();
	~Script();
	bool SetFile(String file_name);
	long NextMessage(Script::Message& message);
	long ParseString(const String& line, Script::Message& message);
	static String whatsThisType(long type);
	static String whatsThisController(long number);

protected:

	void Tokenize( const String& str, Vector<String>& tokens, const String& delimiters );

	FileIn file_;
};


static const float Midi2Pitch[129] = {
	8.176f, 8.662f, 9.177f, 9.723f, 10.301f, 10.913f, 11.562f, 12.25f,
	12.978f, 13.75f, 14.568f, 15.434f, 16.352f, 17.324f, 18.354f, 19.445f,
	20.602f, 21.827f, 23.125f, 24.50f, 25.957f, 27.50f, 29.135f, 30.868f,
	32.703f, 34.648f, 36.708f, 38.891f, 41.203f, 43.654f, 46.249f, 49.0f,
	51.913f, 55.0f, 58.271f, 61.735f, 65.406f, 69.296f, 73.416f, 77.782f,
	82.407f, 87.307f, 92.499f, 97.999f, 103.826f, 110.0f, 116.541f, 123.471f,
	130.813f, 138.591f, 146.832f, 155.563f, 164.814f, 174.614f, 184.997f, 195.998f,
	207.652f, 220.0f, 233.082f, 246.942f, 261.626f, 277.183f, 293.665f, 311.127f,
	329.628f, 349.228f, 369.994f, 391.995f, 415.305f, 440.0f, 466.164f, 493.883f,
	523.251f, 554.365f, 587.33f, 622.254f, 659.255f, 698.456f, 739.989f, 783.991f,
	830.609f, 880.0f, 932.328f, 987.767f, 1046.502f, 1108.731f, 1174.659f, 1244.508f,
	1318.51f, 1396.913f, 1479.978f, 1567.982f, 1661.219f, 1760.0f, 1864.655f, 1975.533f,
	2093.005f, 2217.461f, 2349.318f, 2489.016f, 2637.02f, 2793.826f, 2959.955f, 3135.963f,
	3322.438f, 3520.0f, 3729.31f, 3951.066f, 4186.009f, 4434.922f, 4698.636f, 4978.032f,
	5274.041f, 5587.652f, 5919.911f, 6271.927f, 6644.875f, 7040.0f, 7458.62f, 7902.133f,
	8372.018f, 8869.844f, 9397.273f, 9956.063f, 10548.082f, 11175.303f, 11839.822f, 12543.854f,
	13289.75f
};

NAMESPACE_AUDIO_END

#endif


