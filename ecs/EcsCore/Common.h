#ifndef _EcsCore_Common_h_
#define _EcsCore_Common_h_


NAMESPACE_OULU_BEGIN


struct RealtimeSourceConfig;
class Entity;
class ComponentBase;
class Pool;
class ComponentMap;
class Camerable;
class Renderable;
class Transform;
class Camerable;
class Renderable;
class Machine;
class EntityStore;
class RegistrySystem;
struct ConnectorBase;
struct AudioSource;
struct AudioSink;
struct VideoSource;
struct VideoSink;
template <class Main, class Base> class ComponentStoreT;

using PoolParent			= RefParent2<EntityStore,Pool>;
using ComponentStore		= ComponentStoreT<Entity, ComponentBase>;
using ConnectorStore		= ComponentStoreT<Pool, ConnectorBase>;

using AudioExchangePointRef	= Ref<AudioExchangePoint,	RefParent1<MetaExchangePoint>>;
using VideoExchangePointRef	= Ref<VideoExchangePoint,	RefParent1<MetaExchangePoint>>;
using ComponentRef			= Ref<ComponentBase,		RefParent1<Entity>>;
using AudioSourceRef		= Ref<AudioSource,			RefParent1<Entity>>;
using AudioSinkRef			= Ref<AudioSink,			RefParent1<Entity>>;
using VideoSourceRef		= Ref<VideoSource,			RefParent1<Entity>>;
using VideoSinkRef			= Ref<VideoSink,			RefParent1<Entity>>;
using CamerableRef			= Ref<Camerable,			RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;
using RenderableRef			= Ref<Renderable,			RefParent1<Entity>>;
using ConnectorRef			= Ref<ConnectorBase,		RefParent1<Pool>>;
using EntityRef				= Ref<Entity,				RefParent1<Pool>>;
using PoolRef				= Ref<Pool,					PoolParent>;
using EntityStoreRef		= Ref<EntityStore,			RefParent1<Machine>>;
using RegistrySystemRef		= Ref<RegistrySystem,		RefParent1<Machine>>;
using ComponentStoreRef		= Ref<ComponentStore,		RefParent1<Machine>>;
using ConnectorStoreRef		= Ref<ConnectorStore,		RefParent1<Machine>>;

using ConnectorMapBase		= RefTypeMapIndirect<	ConnectorBase,	RefParent1<Pool>>;
using EntityVec				= RefLinkedList<		Entity,			RefParent1<Pool>>;
using PoolVec				= RefLinkedList<		Pool,			PoolParent>;

using VAR					= EntityRef;
using EntityId				= int64;

template <class T>
using RefT_Entity			= Ref<T,					RefParent1<Entity>>;

template <class T>
using RefT_Pool				= Ref<T,					RefParent1<Pool>>;


struct PerceptionTimestamp {
	double ts = 0;
};

struct HolographicFramePrediction {
	PerceptionTimestamp ts;
	
	
	PerceptionTimestamp Timestamp() const {
		return ts;
	}
};

struct HolographicFrame {
	HolographicFramePrediction pred;
	
	HolographicFramePrediction CurrentPrediction() const {
		return pred;
	}
	
	
};

struct SpatialCoordinateSystem {

};

class IPredictionUpdateListener {

public:
	enum PredictionUpdateReason {
		HolographicSpaceCreateNextFrame,
		HolographicFrameUpdatePrediction,
	};
	
	virtual void OnPredictionUpdated(
		PredictionUpdateReason reason,
		const HolographicFramePrediction& prediction) const = 0;
};

struct HolographicSpace {

};



#define PREFAB_BEGIN(x) \
struct x : \
	EntityPrefab<

#define PREFAB_END \
> { \
    static Components Make(Entity& e) \
    { \
        auto components = EntityPrefab::Make(e); \
		return components; \
    } \
};





typedef enum {
	CONNAREA_INTERNAL,
	CONNAREA_POOL_CURRENT,
	CONNAREA_POOL_CHILDREN_ONLY,
	CONNAREA_POOL_PARENTS_ONLY,
	
	CONNAREA_COUNT
} ConnectorArea;


NAMESPACE_OULU_END

#endif
