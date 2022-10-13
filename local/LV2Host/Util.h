#ifndef _LV2Host_Util_h_
#define _LV2Host_Util_h_

NAMESPACE_TOPSIDE_BEGIN


void LoadAllLV2Plugins(Index<String>& lv2_list);
String FindLv2InstrumentForPreset(String preset, Index<String>& lv2_list);


NAMESPACE_TOPSIDE_END

#endif
