#include "Backend.h"


NAMESPACE_TOPSIDE_BEGIN

Namespace::Namespace() {
	
}

Class& Namespace::GetAddClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetParent(this);
	o.name = name;
	return o;
}

Class& Namespace::GetAddTemplateClass(String name) {
	int i = classes.Find(name);
	if (i >= 0)
		return classes[i];
	Class& o = classes.Add(name);
	o.SetParent(this);
	o.is_template = true;
	o.name = name;
	return o;
}

NAMESPACE_TOPSIDE_END
