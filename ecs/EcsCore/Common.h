#ifndef _EcsCore_Common_h_
#define _EcsCore_Common_h_


NAMESPACE_OULU_BEGIN


class Entity;
struct ComponentBase;
class Pool;
class ConnectorBase;
//class InterfaceBase;

template <class Main, class Base> class ComponentStoreT;
using ComponentStore = ComponentStoreT<Entity, ComponentBase>;
using ConnectorStore = ComponentStoreT<Pool, ConnectorBase>;

class ComponentMap;
class Camerable;
class Renderable;
class Transform;
using ComponentRef = Ref<ComponentBase>;

struct RealtimeSourceConfig;

struct AudioSource;
struct AudioSink;
using AudioSourceRef	= Ref<AudioSource>;
using AudioSinkRef		= Ref<AudioSink>;

struct VideoSource;
struct VideoSink;
using VideoSourceRef	= Ref<VideoSource>;
using VideoSinkRef		= Ref<VideoSink>;










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
