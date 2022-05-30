#pragma once


NAMESPACE_ECS_BEGIN


// SpatialInteraction event listener
struct SpatialInteractionListener : WeakRefScopeEnabler<SpatialInteractionListener, Engine>, RTTIBase
{
	RTTI_DECL0(SpatialInteractionListener)
	
    virtual void OnSourceDetected(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceLost(const SpatialSourceEventArgs& args) {};
    virtual void OnSourcePressed(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceUpdated(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceReleased(const SpatialSourceEventArgs& args) {};
    
};

using SpatialInteractionListenerRef = Ref<SpatialInteractionListener, RefParent1<Ecs::Engine>>;



// SpatialInteractionSystem
// Manages events from SpatialInteractionManager with additional filtering
class SpatialInteractionSystem final :
	public Ecs::System<SpatialInteractionSystem>,
	public HolographicScopeBinder
{
public:
	ECS_SYS_CTOR(SpatialInteractionSystem)
	
	/*using ISpatialInteractionListener = ISpatialInteractionListenerT<Holo>;
	using ISpatialInteractionManager = typename Holo::ISpatialInteractionManager;
	using SpatialInteractionManager = typename Holo::SpatialInteractionManager;
	using SpatialSourceEventArgs = typename Holo::SpatialSourceEventArgs;
	using NativeEventToken = typename Holo::NativeEventToken;*/
	
    void AddListener(SpatialInteractionListenerRef listener)
    {
        spatial_interaction_listeners.Add(listener);
    }

    void RemoveListener(SpatialInteractionListenerRef listener)
    {
        spatial_interaction_listeners.Remove(listener);
    }

    //SpatialInteractionManager& GetInteractionManager() {ASSERT(spatial_interaction_manager); return *spatial_interaction_manager;}
	//const SpatialInteractionManager& GetInteractionManager() const {ASSERT(spatial_interaction_manager); return *spatial_interaction_manager;}
	
protected:
    bool Initialize() override;
    void Uninitialize() override;
    void Update(double dt) override;

private:
    Array<SpatialInteractionListenerRef> spatial_interaction_listeners;
    //SpatialInteractionManager* spatial_interaction_manager = 0;
    
    
    void BindEventHandlers();
    
    /*enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    NativeEventToken source_tokens[SourceEvent::Count];
    */
    

    void ReleaseEventHandlers();

    // Events Handlers
    void HandleSourceDetected(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs&  args);

    void HandleSourceLost(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourcePressed(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourceUpdated(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);

    void HandleSourceReleased(
        const SpatialInteractionManager& sender,
        const SpatialSourceEventArgs& args);
    
};


NAMESPACE_ECS_END
