#include "AudioHost.h"

#ifdef flagLV2

NAMESPACE_TOPSIDE_BEGIN


int Lv2Host::private_id = 0;

Lv2Host::Lv2Host(int t, int samprate, int audio_buf_size, String path, int plugin_number) :
		ID(private_id++),
		initialized(false),
		track(t),
		samplerate(samprate),
		audio_buf_size(audio_buf_size) {
	port_count = 0;
	ctrl_count_inputs = 0;
	ctrl_count_outputs = 0;
	audio_in_count = 0;
	audio_out_count = 0;
	
	for (int i = 0; i < 255; i++) {
		ctrl_buffer.push_back(0.0);
		ctrl_out_buffer.push_back(0.0);
	}
	
	String loadString = path;
	
	LoadPlugin(path);
}

void Lv2Host::LoadPlugin(String inPluginUriStr) {
	LOG( "Lv2Host::LoadPlugin()!" );
	
	// A world contains all the info about every plugin on the system
	world = new Lilv::World();
	
	LOG( "LvTwoHost(): lilv loads world of plugins now" );
	
	// load the entire world
	world->load_all();
	
	// then get them: so far they're only stored in memory, and now we get
	// a variable name with which we can acces / instantiate the plugins
	Lilv::Plugins tmp_plugs = (Lilv::Plugins)world->get_all_plugins();
	
	//ListPlugins( &tmp_plugins_list );
	
	String plugin_uri_str = inPluginUriStr;
	
	Lilv::Node plugin_uri = world->new_uri(plugin_uri_str.Begin());
	
	Lilv::Plugin p = tmp_plugs.get_by_uri(plugin_uri);
	plugin = &p;
	
	port_count = plugin->get_num_ports();
	
	Lilv::Node tmp_uri_node = plugin->get_name();
	plugin_string = tmp_uri_node.as_string();
	
	GetPluginPorts(world, plugin);
	
	//   Create new instance
	instance = Lilv::Instance::create(p, samplerate, NULL);
	
	port_count = (int)plugin->get_num_ports();
	
	if (!instance) {
		LOG( "Instanciating of " << plugin_uri_str << " failed!" );
		initialized = false;
		return;
	}
	
	else {
		LOG( "Instanciating of " << plugin_uri_str << " OK, activating now!" );
		instance->activate();
		initialized = true;
	}
	
	ConnectPorts();
}

void Lv2Host::ListPlugins(Lilv::Plugins* pluginsList) {
	// loop over the array of plugins, printing data for each.
	for (LilvIter* i = pluginsList->begin(); !pluginsList->is_end(i); i = pluginsList->next(i)) {
		// Get a variable that denotes a plugin in the library
		Lilv::Plugin p = pluginsList->get(i);
		
		// Nodes represent information, this one the plugins name
		Lilv::Node nameNode = p.get_name();
		LOG( nameNode.as_string() );
		
		// this one the plugins uri
		Lilv::Node uriNode = p.get_uri();
		LOG( uriNode.as_uri() );
	}
}

void Lv2Host::InfoPlugin(Lilv::Plugin* plugin) {
	// print out the info we have on this plugin, author, website etc
	PrintPlugin(plugin);
	
	// get features that this plugin supports, and print them
	Lilv::Nodes supportedFeatures = plugin->get_supported_features();
	
	LOG( "Supported features:" );
	
	for (LilvIter* i = supportedFeatures.begin(); !supportedFeatures.is_end(i); i = supportedFeatures.next(i)) {
		Lilv::Node tmp = supportedFeatures.get(i);
		PrintNode(&tmp);
	}
	
	LOG("");
	
	// get features that this plugin *requires* and print them
	Lilv::Nodes requiredFeatures = plugin->get_required_features();
	LOG( "Required features:" );
	
	for (LilvIter* i = requiredFeatures.begin(); !requiredFeatures.is_end(i); i = requiredFeatures.next(i)) {
		Lilv::Node tmp = requiredFeatures.get(i);
		PrintNode(&tmp);
		
	}
	
	LOG("");
	
}

void Lv2Host::GetPluginPorts(Lilv::World* world, Lilv::Plugin* plugin) {
	// here we iter over each port that's associated with the plugin,
	// and print out that ports info
	
	//create some nodes that represent certain features: Input / Output, Audio / MIDI
	Lilv::Node audio    = world->new_uri(LILV_URI_AUDIO_PORT);
	Lilv::Node control    = world->new_uri(LILV_URI_CONTROL_PORT);
	Lilv::Node event    = world->new_uri(LILV_URI_EVENT_PORT);
	Lilv::Node input    = world->new_uri(LILV_URI_INPUT_PORT);
	Lilv::Node midi_event  = world->new_uri(LILV_URI_MIDI_EVENT);
	Lilv::Node output    = world->new_uri(LILV_URI_OUTPUT_PORT);
	Lilv::Node logarithmic  = world->new_uri("http://lv2plug.in/ns/dev/extportinfo#logarithmic");
	
	//LOG( "Port properties:" << EOL;
	
	
	// get port min & max & default values
	Vector<float> min_array;
	Vector<float> max_array;
	Vector<float> def_array;
	
	min_array.SetCount(port_count, 0.0);
	max_array.SetCount(port_count, 0.0);
	def_array.SetCount(port_count, 0.0);
	
	plugin->get_port_ranges_float(&min_array[0], &max_array[0], &def_array[0]);
	
	
	audio_buf.SetCount(port_count);
	
	for (int i = 0; i < port_count; i++) {
		Lilv::Port port = plugin->get_port_by_index(i);
		
		Lilv::Nodes portNodes = port.get_properties();
		
		Lilv::Node portName = port.get_name();
		Lilv::Node portSymb = port.get_symbol();
		
		// port ID, and name
		String s;
		s << "\tPort Num:" << i << "\tName: " << portName.as_string() << "\tType:   ";
		
		// port_details vector, one instance of class per port, use that in the process callback
		port_details.push_back(new PortDetails());
		
		if (port.is_a(audio)) {
			s << "Audio ";
			port_details[port_details.GetCount() - 1]->audio    = true;
		}
		
		if (port.is_a(event)) {
			s << "Event ";
			port_details[port_details.GetCount() - 1]->event    = true;
		}
		
		if (port.is_a(midi_event)) {
			s << "Midi event ";
			port_details[port_details.GetCount() - 1]->midi_event = true;
		}
		
		if (port.is_a(control)) {
			s << "Control ";
			port_details[port_details.GetCount() - 1]->control  = true;
		}
		
		if (port.is_a(input)) {
			s << " input ";
			port_details[port_details.GetCount() - 1]->input    = true;
		}
		
		if (port.is_a(output)) {
			s << " output ";
			port_details[port_details.GetCount() - 1]->output   = true;
		}
		
		LOG(s);
		
		// store MIN MAX & DEFAULT values (got them earlier)
		port_details[port_details.GetCount() - 1]->min = min_array[i];
		port_details[port_details.GetCount() - 1]->max = max_array[i];
		port_details[port_details.GetCount() - 1]->def = def_array[i];
		
		if (port.has_property(logarithmic)) {
			port_details[port_details.GetCount() - 1]->logarithmic = true;
		}
		
		ctrl_buffer.push_back(0.0);
		
		ctrl_out_buffer.push_back(0.0);
		
		if (port.is_a(control) && port.is_a(input)) {
			// push the "i" value, and its corresponding name onto a map,
			// to be retrived later when changing parameters
			param_name_map.Add(i, portName.as_string());
			// keep track of how many ctrl-ins we have
			ctrl_count_inputs++;
			SetParameter(i, port_details[i]->def);
			
		}
		
		else
		if (port.is_a(control) && port.is_a(input)) {
			param_name_map.Add(i, "not a control input port");
			audio_in_count++;
		}
		
		else
		if (port.is_a(control) && port.is_a(output)) {
			param_name_map.Add(i, "not a control input port");
			audio_out_count++;
		}
		
		else {
			param_name_map.Add(i, "not a control input port");
		}
				
		int counter = 0;
		
		for (LilvIter* i = portNodes.begin(); !portNodes.is_end(i); i = portNodes.next(i), counter++) {
			Lilv::Node node = portNodes.get(i);
			//LOG( "\t\tProperty"  << counter << ": ";
			//PrintNode( &node );
		}
	}
	
	LOG( "Lv2Host::GetPluginPorts() DONE!" );
}

void Lv2Host::PrintPlugin(Lilv::Plugin* plugin) {
	LOG( "Plugin info:" );
	LOG( "Name: " << plugin->get_name().as_string());
	LOG( "URI: " << plugin->get_uri().as_string());
	
	if (plugin->get_author_name().is_string())
		LOG( "Plugin by " << plugin->get_author_name().as_string());
		
	if (plugin->get_author_name().is_string())
		LOG( "Email     " << plugin->get_author_email().as_string());
		
	if (plugin->get_author_name().is_string())
		LOG( "Homepage  " << plugin->get_author_homepage().as_string());
		
	LOG( "Plugin has " << plugin->get_num_ports()          << " ports");
	
	LOG("");
}

void Lv2Host::PrintNode(Lilv::Node* tmp) {
	// helper function to print a node's contents
	if (tmp->is_string())
		LOG( "String: " << tmp->as_string() );
		
	if (tmp->is_uri())
		LOG( "URI: " << tmp->as_uri() );
		
	if (tmp->is_float())
		LOG( "float: " << tmp->as_float() );
		
	if (tmp->is_int())
		LOG( "int: " << tmp->as_int() );
}

void Lv2Host::PrintInfo() {
	LOG( "Lv2Host plugin:" << plugin_string << " Init: " <<  initialized);
}

/*
void Lv2Host::subscribeFunction()
{
}
*/

void Lv2Host::SetParameter(int param, float value) {
	String name;
	
	if (param >= 0 && param < port_count) { // range check the parameter
		if (port_details[param]->control && port_details[param]->input) {
			int iter = param_name_map.Find(param);
			
			if (iter != -1) {
				name = param_name_map[iter];
			}
			
			else {
				name = "invalid value";
			}
			
			// check for NaN
			
			if (value != value) {
				value = 0;
			}
			
			// Clamp values to min and max
			
			if (port_details[param]->max == port_details[param]->max && value > port_details[param]->max) {
				value = port_details[param]->max;
			}
			else
			if (port_details[param]->min == port_details[param]->min && value < port_details[param]->min) {
				value = port_details[param]->min;
			}
				
			LOG( "Lv2Host::SetParameter( " << name <<  ", " << ": " << value << " ) Min:" << port_details[param]->min << "; " << "Max:" << port_details[param]->max );
			
			ctrl_buffer[param] = value;
			
			// make GUI redraw
			//rh->sendOsc( Osc::PATH_TRACK_SET_PLUGIN_PARAMETER_ABSOLUTE, -2, ID, param, value );
		}
		
		else {
			LOG( "Lv2Host::SetParameter() not a control input port, param: " << param );
		}
	}
	
	else {
		LOG( "Lv2Host::SetParameter() accesing out of bounds, param: " << param );
	}
}

void Lv2Host::ConnectPorts() {
	for (int i = 0; i < port_count; i++) {
		if (port_details[i]->audio && port_details[i]->input) {
			LOG( "Connecting Audio Input!  port #: " << i );
			audio_buf[i] = new float[audio_buf_size];
			instance->connect_port(i, audio_buf[i]);
		}
		
		else
		if (port_details[i]->audio && port_details[i]->output) {
			LOG( "Connecting Audio Output!  port #: " << i );
			audio_buf[i] = new float[audio_buf_size];
			instance->connect_port(i, audio_buf[i]);
		}
		
		else
		if (port_details[i]->control && port_details[i]->input) {
			// LOG( "Connecting Control Input!  port #: " << i );
			instance->connect_port(i, &ctrl_buffer[i]);
		}
		
		else
		if (port_details[i]->control && port_details[i]->output) {
			// LOG( "Connecting Control Output!  port #: " << i );
			instance->connect_port(i, &ctrl_out_buffer[i]);
		}
		
		else {
			// we don't know how to connect this port properly, its an
			// unknown type, so don't let the plugin run, as it will segfault
			// when running with an un-connected port
			LOG( "Lv2Host::ConnectPorts: error: Port could not be connected #: " << i );
			initialized = 0;
		}
	}
}

Vector<float*>& Lv2Host::GetAudioBuffers() {
	return audio_buf;
}

void Lv2Host::Process(unsigned int nframes) {
	if (initialized != 1) {
		LOG( "Lv2Host::Process(): Warning: Running uninitialized plugin!" );
		return;
	}
	
	// LOG( "Lv2Host::Process(): running NOW!" );
	instance->run(nframes);
	
	return;
}

void Lv2Host::HandleEvent(const MidiIO::Event& ev) {
	TODO
}

Lv2Host::~Lv2Host() {
	LOG( "~Lv2Host() destroyed" );
}


NAMESPACE_TOPSIDE_END

#endif
