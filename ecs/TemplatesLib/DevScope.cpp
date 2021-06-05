#include "TemplatesLib.h"

NAMESPACE_TOPSIDE_BEGIN



#define DEV(x) \
template <> template <> \
typename ScopeValMachT<AudioSpec>::Format \
ScopeDevLibT<x##Spec>::StageComponent::GetDefaultFormat<AudioSpec>() { \
	typename ScopeValMachT<AudioSpec>::Format fmt; \
	fmt.Set<x##Spec>(SoundSample::S16_LE, 2, 44100, 1024); \
	return fmt; \
} \
template <> template <> \
typename ScopeValMachT<VideoSpec>::Format \
ScopeDevLibT<x##Spec>::StageComponent::GetDefaultFormat<VideoSpec>() { \
	typename ScopeValMachT<VideoSpec>::Format fmt; \
	fmt.Set<x##Spec>(LightSampleFD::U8_LE_ABCD, Size(640, 480), 60, 1); \
	return fmt; \
}
DEV(Center)
DEV(Net)
DEV(Perma)
#undef DEV



NAMESPACE_TOPSIDE_END
