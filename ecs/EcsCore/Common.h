#ifndef _EcsCore_Common_h_
#define _EcsCore_Common_h_


NAMESPACE_OULU_BEGIN


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
