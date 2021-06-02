#include "RTTI.h"

namespace UPP {


bool RTTI::operator==(const RTTI& w) const {
	return Is(w.GetTypeId());
}
bool RTTI::operator!=(const RTTI& w) const {
	return !Is(w.GetTypeId());
}
bool RTTI::before(const RTTI& w) const {
	return &w < this;
}


}
