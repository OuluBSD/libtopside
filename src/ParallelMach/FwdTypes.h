#ifndef _ParallelMach_FwdTypes_h_
#define _ParallelMach_FwdTypes_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Serial {
using namespace Parallel;


#define LINK_TYPE_LIST \
	LINK_TYPE(CUSTOMER) \
	LINK_TYPE(PIPE) \
	LINK_TYPE(PIPE_OPTSIDE) \
	LINK_TYPE(INTERVAL_PIPE) \
	LINK_TYPE(EXTERNAL_PIPE) \
	LINK_TYPE(DRIVER) \
	LINK_TYPE(SPLITTER) \
	LINK_TYPE(MERGER) \
	LINK_TYPE(JOINER) \
	LINK_TYPE(POLLER_PIPE) \



#undef INVALID_LINK

typedef enum : byte {
	INVALID_LINK,
	
	#define LINK_TYPE(x) LINK_##x,
	LINK_TYPE_LIST
	#undef LINK_TYPE
	
	SUBCOMP_COUNT
} SubLinkCls;

#define LINK_ROLE_LIST \
	LINK_ROLE(CUSTOMER) \
	LINK_ROLE(PROCESS) \
	LINK_ROLE(DRIVER) \


typedef enum : int {
	INVALID_ROLE=-1,
	
	#define LINK_ROLE(x) LINKROLE_##x,
	LINK_ROLE_LIST
	#undef LINK_ROLE
	
	ROLE_COUNT
} LinkRole;


String GetSubLinkString(SubLinkCls t);
String GetLinkRoleString(LinkRole t);





struct LinkTypeCls : Moveable<LinkTypeCls> {
	SubLinkCls sub = SubLinkCls::INVALID_LINK;
	LinkRole role = LinkRole::INVALID_ROLE;
	
	bool IsValid() const {return sub != SubLinkCls::INVALID_LINK && role != LinkRole::INVALID_ROLE;}
	hash_t GetHashValue() const;
	void operator=(const Nuller& n) {sub = SubLinkCls::INVALID_LINK; role = LinkRole::INVALID_ROLE;}
	void operator=(const LinkTypeCls& o) {
		sub = o.sub;
		role = o.role;
	}
	
	bool operator==(const LinkTypeCls& c) const {
		return	sub == c.sub &&
				role == c.role
				;
	}
	bool operator!=(const LinkTypeCls& c) const {return !(*this == c);}
	String ToString() const {return GetSubLinkString(sub) + "-" + GetLinkRoleString(role);}
	
	
	LinkTypeCls() {}
	LinkTypeCls(const LinkTypeCls& c) {*this = c;}
	LinkTypeCls(SubLinkCls cls, LinkRole role) : sub(cls), role(role) {}
	
};

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefLinkTypeMapIndirect	= RefLinkedMapIndirect<LinkTypeCls, T, Parent>;



#define LINKTYPE(type, role) LinkTypeCls(SubLinkCls::LINK_##type, LinkRole::LINKROLE_##role)




class EntitySystem;
using EntitySystemRef		= Ref<EntitySystem, ParallelSystemParent>;

}



namespace Ecs {
class Engine;
//class WindowSystem;
//using WindowSystemRef = Ref<WindowSystem, RefParent1<Engine>>;
}



NAMESPACE_TOPSIDE_END

#endif
