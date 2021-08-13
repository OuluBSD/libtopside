#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


String TrackerInfo::ToString() const {
	String s;
	
	if (handler_cls)
		s << "@" << handler_cls->GetDynamicName();
	if (handler_fn)
		s << "::" << handler_fn;
	
	if (file && line)
		s << " (" << file << ":" << IntStr(line) << ")";
	else if (file)
		s << " (" << file << ")";
	
	if (s.IsEmpty())
		s = "<no info>";
	return s;
}


NAMESPACE_SERIAL_END
