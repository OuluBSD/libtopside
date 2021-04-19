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
using SharedComponent = Shared<ComponentBase>;



class ExchangeValue {
	
protected:
	
	
public:
	virtual ~ExchangeValue() {}
	
	
	
};



class SemanticExchange : public ExchangeValue {
	
	
};


NAMESPACE_OULU_END


#endif
