#ifndef _EcsCore_Exchange_h_
#define _EcsCore_Exchange_h_


NAMESPACE_OULU_BEGIN

class Entity;
struct ComponentBase;
class EntityPool;
class PoolComponentBase;

template <class Main, class Base> class ComponentStoreT;
using ComponentStore = ComponentStoreT<Entity, ComponentBase>;
using PoolComponentStore = ComponentStoreT<EntityPool, PoolComponentBase>;

class ComponentMap;
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





class MetaExchangePoint {
	
	
public:
	typedef MetaExchangePoint CLASSNAME;
	MetaExchangePoint();
	
	String ToString() const;
	
};


NAMESPACE_OULU_END


#endif
