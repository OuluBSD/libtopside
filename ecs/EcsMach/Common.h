#ifndef _EcsMech_Common_h_
#define _EcsMech_Common_h_


NAMESPACE_ECS_BEGIN


class SystemBase;

class Entity;
class ComponentBase;
class Pool;
class ComponentMap;
class Renderable;
class Transform2D;
class Renderable;
class Machine;
class EntityStore;
class RegistrySystem;
class Overlap;
class ToolSystemBase;
class ISpatialInteractionListener;
class ToolComponent;
class MotionControllerComponent;
class PbrRenderable;
class CoreWindow;
class DummySoundGeneratorComponent;
class PortaudioSinkComponent;
class StaticVolumeComponent;
class Viewable;
class Transform;
class ExtComponent;
//class ConnectorBase;
struct PaintComponent;
template <class Main, class Base> class ComponentStoreT;

using EntityParent			= RefParent1<Pool>;
using PoolParent			= RefParent2<EntityStore,Pool>;
using ComponentStore		= ComponentStoreT<Entity, ComponentBase>;
//using ConnectorStore		= ComponentStoreT<Pool, ConnectorBase>;

using ComponentBaseRef		= Ref<ComponentBase,		RefParent1<Entity>>;
using ComponentRef			= Ref<ComponentBase,		RefParent1<Entity>>;
using Transform2DRef		= Ref<Transform2D,			RefParent1<Entity>>;
using RenderableRef			= Ref<Renderable,			RefParent1<Entity>>;
using OverlapRef			= Ref<Overlap,				RefParent1<Entity>>;
using PaintComponentRef		= Ref<PaintComponent,		RefParent1<Entity>>;
using ToolComponentRef		= Ref<ToolComponent,		RefParent1<Entity>>;
using PbrRenderableRef		= Ref<PbrRenderable,		RefParent1<Entity>>;
using CoreWindowRef			= Ref<CoreWindow,			RefParent1<Entity>>;
using ViewableRef			= Ref<Viewable,				RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;
//using ConnectorRef			= Ref<ConnectorBase,		EntityParent>;
using EntityRef				= Ref<Entity,				EntityParent>;
using PoolRef				= Ref<Pool,					PoolParent>;
using EntityStoreRef		= Ref<EntityStore,			RefParent1<Machine>>;
using RegistrySystemRef		= Ref<RegistrySystem,		RefParent1<Machine>>;
using ComponentStoreRef		= Ref<ComponentStore,		RefParent1<Machine>>;
//using ConnectorStoreRef		= Ref<ConnectorStore,		RefParent1<Machine>>;
using ToolSystemBaseRef		= Ref<ToolSystemBase,		RefParent1<Machine>>;
using ExtComponentRef		= Ref<ExtComponent,			RefParent1<Entity>>;

using DummySoundGeneratorComponentRef	= Ref<DummySoundGeneratorComponent,		RefParent1<Entity>>;
using PortaudioSinkComponentRef			= Ref<PortaudioSinkComponent,			RefParent1<Entity>>;
using StaticVolumeComponentRef			= Ref<StaticVolumeComponent,			RefParent1<Entity>>;
using MotionControllerComponentRef		= Ref<MotionControllerComponent,		RefParent1<Entity>>;
using ISpatialInteractionListenerRef	= Ref<ISpatialInteractionListener,		RefParent1<Machine>>;

//using ConnectorMapBase		= RefTypeMapIndirect<	ConnectorBase,	EntityParent>;
using EntityVec				= RefLinkedList<		Entity,			EntityParent>;
using PoolVec				= RefLinkedList<		Pool,			PoolParent>;

using VAR					= EntityRef;
using EntityId				= int32;
using PoolId				= int32;

template <class T>
using RefT_Entity			= Ref<T,					RefParent1<Entity>>;

template <class T>
using RefT_Pool				= Ref<T,					RefParent1<Pool>>;

template <class T>
using RefT_Machine			= Ref<T,					RefParent1<Machine>>;







struct PerceptionTimestamp {
	double ts = 0;
	
	PerceptionTimestamp() {}
	PerceptionTimestamp(double ts) : ts(ts) {}
	PerceptionTimestamp(const PerceptionTimestamp& t) : ts(t.ts) {}
	
	
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
	
	
	
	operator bool() const;
	
};



#define PREFAB_BEGIN(x) \
struct x##_ : RTTIBase {RTTI_DECL0(x##_)}; \
\
struct x : \
	x##_, \
	EntityPrefab<

#define PREFAB_END \
> { \
	 \
    static Components Make(Entity& e) \
    { \
        auto components = EntityPrefab::Make(e); \
		return components; \
    } \
};





/*typedef enum {
	CONNAREA_INTERNAL,
	CONNAREA_POOL_CURRENT,
	CONNAREA_POOL_CHILDREN_ONLY,
	CONNAREA_POOL_PARENTS_ONLY,
	
	CONNAREA_COUNT
} ConnectorArea;*/



#define VIS_THIS(t) vis.VisitThis<t>(this);

#define COMP_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this);}
#define COMP_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this); x;}
#define COMP_DEF_MAKE_ACTION static bool MakeAction(Eon::Action& act) {return false;}

#define COMP_MAKE_ACTION_BEGIN static bool MakeAction(const TypeCompCls& cls, Eon::Action& act) {bool fail = false, any_changes = false; const ValDevCls& vd = cls.side.vd;
#define COMP_MAKE_ACTION_END return !fail && any_changes;}
#define COMP_MAKE_ACTION_FALSE_TO_TRUE(x) if (act.Pre().IsFalse(x)) {act.Post().SetTrue(x); any_changes = true;} else fail = true;
#define COMP_MAKE_ACTION_TO_TRUE(x) act.Post().SetTrue(x); any_changes = true;
#define COMP_MAKE_ACTION_TRUE_TO_FALSE(x) if (act.Pre().IsTrue(x)) {act.Post().SetFalse(x); any_changes = true;} else fail = true;
//#define COMP_MAKE_ACTION_REQ_TRUE_TO_TRUE(x, y) if (act.Pre().IsTrue(x)) {act.Post().SetTrue(y); any_changes = true;} else fail = true;






#define COPY_PANIC(T) void operator=(const T& t) {Panic("Can't copy " #T);}

#define IFACE_GENERIC	ComponentBase* AsComponentBase() override {return this;}




NAMESPACE_ECS_END

#endif
