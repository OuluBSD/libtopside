#ifndef LV2_HOST
#define LV2_HOST

#ifdef flagLV2

NAMESPACE_TOPSIDE_BEGIN


// Lilv: Lv2 host library, and extensions

class PortDetails {

public:
	bool input;
	bool output;
	
	bool audio;
	bool event;
	bool control;
	bool midi_event;
	
	bool logarithmic;
	
	float min;
	float max;
	float def;
	
	PortDetails() {
		input = false;
		output = false;
		
		audio = false;
		event = false;
		control = false;
		midi_event = false;
		
		logarithmic = false;
		
		min = 0.f;
		max = 0.f;
		def = 0.f;
	}
};

class Lv2Host {

public:
	Lv2Host(int track, int samplerate, int audio_buf_size, String path, int plugin_number = 0);
	~Lv2Host();
	
	void PrintInfo();
	
	void SetParameter(int, float);
	void SetParameterAbsolute(int, float);
	
	void LoadPlugin(String);
	void HandleEvent(const MidiIO::Event& ev);
	
	void Process(unsigned int nframes);
	Vector<float*>& GetAudioBuffers();
	
	bool IsInitialized() const {return initialized;}
	
protected:
	int ID;
	static int private_id;
	
	int track;
	
	// General purpose vars
	bool push_changes_to_ui;
	
	bool initialized;
	bool ports_suitable;
	
	int nframes;
	int samplerate;
	String plugin_string;
	
	// Lilv variables
	Lilv::World* world;
	Lilv::Plugin* plugin;
	Lilv::Instance* instance;
	Lilv::Plugins* tmp_plugins_list;
	
protected:
	// Lv2 functions
	void PrintNode(Lilv::Node* tmp);
	void InfoPlugin(Lilv::Plugin* plugin);
	void PrintPlugin(Lilv::Plugin* plugin);
	void ListPlugins(Lilv::Plugins* pluginsList);
	void GetPluginPorts(Lilv::World* world, Lilv::Plugin* plugin);
	
protected:
	// all port number variables
	int port_count;
	
	int input_count;
	int output_count;
	
	int audio_count;
	int ctrl_count;
	
	int audio_in_count;
	int audio_out_count;
	
	int ctrl_count_inputs;
	int ctrl_count_outputs;
	
	int in_port_left;
	int in_port_right;
	int out_port_left;
	int out_port_right;
	int ctrl_in_port;
	
	int osc_n_frame_counter;
	
	int audio_buf_size;
	
	
	void AnalysePorts();
	void ConnectPorts();
	void CheckSuitablility();
	void InstantiatePlugin();
	void LoadLibrary(String filename);
	
	// buffers to pass in / out control / audio data
	Vector<float> ctrl_buffer;
	Vector<float> ctrl_out_buffer;
	Vector<float*> audio_buf;
	Vector<PortDetails*> port_details;
	VectorMap<int, String> param_name_map;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif

