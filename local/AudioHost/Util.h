#ifndef _AudioHost_Util_h_
#define _AudioHost_Util_h_
#ifdef flagLV2

NAMESPACE_TOPSIDE_BEGIN


void LoadAllLV2Plugins(Index<String>& lv2_list);
void GetLv2InstrumentCandidates(String preset, Index<String>& lv2_list, Index<String>& plugin_uris);
String FindLv2InstrumentForPreset(String preset, Index<String>& lv2_list);


NAMESPACE_TOPSIDE_END

#endif
#endif
