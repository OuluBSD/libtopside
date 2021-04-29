#ifndef _EcsCore_Exchange_h_
#define _EcsCore_Exchange_h_


NAMESPACE_OULU_BEGIN

class Entity;
struct ComponentBase;
class Pool;
class ConnectorBase;
class InterfaceBase;

template <class Main, class Base> class ComponentStoreT;
using ComponentStore = ComponentStoreT<Entity, ComponentBase>;
using ConnectorStore = ComponentStoreT<Pool, ConnectorBase>;

class ComponentMap;
class Camerable;
class Renderable;
class Transform;
using ComponentRef = Ref<ComponentBase>;

typedef Ref<InterfaceBase> InterfaceBaseRef;


class Exchange {
	
protected:
	
	
public:
	virtual ~Exchange() {}
	
	
	
};



class SemanticExchange : public Exchange {
	
	
};





class ExchangePoint : public LockedScopeEnabler<ExchangePoint> {
	
protected:
	friend class MetaExchangePoint;
	
	InterfaceBaseRef src;
	InterfaceBaseRef sink;
	
	
public:
	typedef ExchangePoint CLASSNAME;
	ExchangePoint();
	
	void Set(InterfaceBaseRef src, InterfaceBaseRef sink);
	
	
	
};

typedef Ref<ExchangePoint> ExchangePointRef;



class MetaExchangePoint {
	RefLinkedList<ExchangePoint> pts;
	ConnectorBase* comp = 0;
	
public:
	typedef MetaExchangePoint CLASSNAME;
	MetaExchangePoint();
	
	void Init(ConnectorBase* comp);
	void UnlinkAll();
	
	ExchangePointRef Add();
	
	String ToString() const;
	
	
};


NAMESPACE_OULU_END


#endif
