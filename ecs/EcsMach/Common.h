#ifndef _EcsMech_Common_h_
#define _EcsMech_Common_h_


NAMESPACE_TOPSIDE_BEGIN


class ISpatialInteractionListener;



NAMESPACE_TOPSIDE_END



NAMESPACE_ECS_BEGIN


class SystemBase;

class Entity;
class ComponentBase;
class Pool;
class ComponentMap;
class Renderable;
class Transform2D;
class Renderable;
class Engine;
class EntityStore;
class RegistrySystem;
class Overlap;
class ToolSystemBase;
class ToolComponent;
class MotionControllerComponent;
class PbrRenderable;
class CoreWindow;
class DebugAudioGeneratorExt;
class PortaudioSinkComponent;
class StaticVolumeComponent;
class Viewable;
class Viewport;
class Transform;
class ExtComponent;
//class ConnectorBase;
struct PaintComponent;
class ComponentStore;
//template <class Main, class Base> class ComponentStoreT;

using EcsSystemParent		= RefParent1<Engine>;

using EntityParent			= RefParent1<Pool>;
using PoolParent			= RefParent2<EntityStore,Pool>;
//using ComponentStore		= ComponentStoreT<Entity, ComponentBase>;
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
using ViewportRef			= Ref<Viewport,				RefParent1<Entity>>;
using TransformRef			= Ref<Transform,			RefParent1<Entity>>;
//using ConnectorRef			= Ref<ConnectorBase,		EntityParent>;
using EntityRef				= Ref<Entity,				EntityParent>;
using PoolRef				= Ref<Pool,					PoolParent>;
using EntityStoreRef		= Ref<EntityStore,			EcsSystemParent>;
using RegistrySystemRef		= Ref<RegistrySystem,		EcsSystemParent>;
using ComponentStoreRef		= Ref<ComponentStore,		EcsSystemParent>;
//using ConnectorStoreRef		= Ref<ConnectorStore,		EcsSystemParent>;
using ToolSystemBaseRef		= Ref<ToolSystemBase,		EcsSystemParent>;
using ExtComponentRef		= Ref<ExtComponent,			RefParent1<Entity>>;

using DebugAudioGeneratorExtRef	= Ref<DebugAudioGeneratorExt,		RefParent1<Entity>>;
using PortaudioSinkComponentRef			= Ref<PortaudioSinkComponent,			RefParent1<Entity>>;
using StaticVolumeComponentRef			= Ref<StaticVolumeComponent,			RefParent1<Entity>>;
using MotionControllerComponentRef		= Ref<MotionControllerComponent,		RefParent1<Entity>>;
using ISpatialInteractionListenerRef	= Ref<ISpatialInteractionListener,		EcsSystemParent>;

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
using RefT_Engine			= Ref<T,					EcsSystemParent>;









#define PREFAB_BEGIN(x) \
struct x##_ : RTTIBase {RTTI_DECL0(x##_)}; \
\
struct x : \
	x##_, \
	TS::ECS::EntityPrefab<

#define PREFAB_END \
> { \
	 \
    static Components Make(TS::ECS::Entity& e) \
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



#define COMP_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this);}
#define COMP_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ComponentT>(this); x;}

#define COPY_PANIC(T) void operator=(const T& t) {Panic("Can't copy " #T);}





NAMESPACE_ECS_END

#endif
