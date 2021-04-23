#ifndef _EcsCore_Exchange_h_
#define _EcsCore_Exchange_h_


NAMESPACE_OULU_BEGIN

class ComponentStore;
struct ComponentBase;
class ComponentMap;
class Entity;
class Camerable;
class Renderable;
class Transform;
using ComponentRef = Ref<ComponentBase>;



class Exchange {
	
protected:
	
	
public:
	virtual ~Exchange() {}
	
	
	
};



class SemanticExchange : public Exchange {
	
	
};


NAMESPACE_OULU_END


#endif
