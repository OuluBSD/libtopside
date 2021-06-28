#include "TemplatesCore.h"

NAMESPACE_ECS_BEGIN



Format GetDefaultFormat(ValDevCls type) {
	//DUMP(type)
	Format fmt;
	
	if (type.dev == DevCls::CENTER) {
		if (type.val == ValCls::AUDIO) {
			fmt.SetAudio(SoundSample::FLT_LE, 2, 44100, 1024);
		}
		else if (type.val == ValCls::ORDER) {
			fmt.SetOrder();
		}
		else if (type.val == ValCls::RECEIPT) {
			fmt.SetReceipt();
		}
		else {
			TODO
		}
	}
	else {
		TODO
	}
	
	return fmt;
}


/*#define DEV(x) \
template <> template <> inline \
typename ScopeValMachT<AudioSpec>::Format \
ScopeDevCoreT<x##Spec>::GetDefaultFormat<AudioSpec>() { \
	typename ScopeValMachT<AudioSpec>::Format fmt; \
	fmt.Set<x##Spec>(SoundSample::S16_LE, 2, 44100, 1024); \
	return fmt; \
} \
template <> template <> inline \
typename ScopeValMachT<VideoSpec>::Format \
ScopeDevCoreT<x##Spec>::GetDefaultFormat<VideoSpec>() { \
	typename ScopeValMachT<VideoSpec>::Format fmt; \
	fmt.Set<x##Spec>(LightSampleFD::U8_LE_ABCD, Size(640, 480), 60, 1); \
	return fmt; \
}
DEV(Center)
DEV(Net)
DEV(Perma)
#undef DEV*/


NAMESPACE_ECS_END
