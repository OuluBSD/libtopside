#include "SerialMach.h"

NAMESPACE_UPP




INITBLOCK_(SerialMach) {
	using namespace TS::Parallel;
	using namespace TS::Serial;
	using namespace TS;
	
	Serial::Factory::RegisterLink<CustomerLink>();
	Serial::Factory::RegisterLink<PipeLink>();
	Serial::Factory::RegisterLink<PipeOptSideLink>();
	Serial::Factory::RegisterLink<IntervalPipeLink>();
	Serial::Factory::RegisterLink<ExternalPipeLink>();
	Serial::Factory::RegisterLink<DriverLink>();
	Serial::Factory::RegisterLink<MergerLink>();
	Serial::Factory::RegisterLink<JoinerLink>();
	Serial::Factory::RegisterLink<SplitterLink>();
	Serial::Factory::RegisterLink<PollerLink>();
	
}

END_UPP_NAMESPACE
