#include "TemplatesCore.h"
NAMESPACE_TOPSIDE_BEGIN


template <>
template <>
typename ScopeValMachT<AudioSpec>::Format
ScopeDevCoreT<AccelSpec>::GetDefaultFormat<AudioSpec>() {
	using ValSpec					= AudioSpec;
	using FromDevSpec				= AccelSpec;
	using ValMach					= ScopeValMachT<ValSpec>;
	using Format					= typename ValMach::Format;
	Format fmt;
	fmt.Set<AccelSpec>(SoundSample::FLT_LE, 2, 44100, 1024);
	return fmt;
}


NAMESPACE_TOPSIDE_END
