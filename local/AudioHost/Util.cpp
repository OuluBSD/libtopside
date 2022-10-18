#include "AudioHost.h"
#ifdef flagLV2

NAMESPACE_TOPSIDE_BEGIN


void LoadAllLV2Plugins(Index<String>& lv2_list) {
	LOG("LV2-Plugins");
	
	One<LilvWorld> world = lilv_world_new();
	
	lilv_world_load_all(&*world);
	
	LOG(LILV_DEFAULT_LV2_PATH);
	const LilvPlugins* list = lilv_world_get_all_plugins(&*world);
	int j = 0;
	LILV_FOREACH (plugins, i, list) {
		const LilvPlugin* p = lilv_plugins_get(list, i);
		String s = lilv_node_as_uri(lilv_plugin_get_uri(p));
		LOG(j << ": " << s);
		lv2_list.Add(s);
		j++;
	}
}

void GetLv2InstrumentCandidates(String preset, Index<String>& lv2_list, Index<String>& candidates) {
	
	if (preset == "piano") {
		// from https://github.com/falkTX/FluidPlug
		//candidates.Add("http://kxstudio.linuxaudio.org/plugins/FluidPlug_FluidPianos");
		
		// from your linux repo
		candidates.Add("http://drobilla.net/plugins/mda/Piano");
	}
	else TODO
	
}

String FindLv2InstrumentForPreset(String preset, Index<String>& lv2_list) {
	if (preset.IsEmpty())
		return "";
	
	Index<String> candidates;
	
	GetLv2InstrumentCandidates(preset, lv2_list, candidates);
	
	for (const String& c : candidates) {
		if (lv2_list.Find(c) >= 0)
			return c;
	}
	
	TODO
	return "";
}


NAMESPACE_TOPSIDE_END

#endif
