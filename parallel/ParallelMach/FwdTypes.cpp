#include "ParallelMach.h"


NAMESPACE_TOPSIDE_BEGIN
namespace Serial {
using namespace Parallel;


String GetSubLinkString(SubLinkCls t) {
	switch (t) {
		#define LINK_TYPE(x) case LINK_##x:	return #x;
		LINK_TYPE_LIST
		#undef LINK_TYPE
		default: return "invalid";
	}
}

String GetLinkRoleString(LinkRole t) {
	switch (t) {
		#define LINK_ROLE(x) case LINKROLE_##x: return #x;
		LINK_ROLE_LIST
		#undef LINK_ROLE
		default:			return "invalid";
	}
}


hash_t LinkTypeCls::GetHashValue() const {
	CombineHash c;
	c.Put(sub);
	c.Put(role);
	return c;
}

}
NAMESPACE_TOPSIDE_END
