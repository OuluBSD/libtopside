#pragma once


NAMESPACE_ECS_BEGIN


// SpatialInteraction event listener
struct SpatialInteractionListener : WeakRefScopeEnabler<SpatialInteractionListener, Engine>, RTTIBase
{
	RTTI_DECL0(SpatialInteractionListener)
	using SpatialSourceEventArgs = int;
	
    virtual void OnSourceDetected(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceLost(const SpatialSourceEventArgs& args) {};
    virtual void OnSourcePressed(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceUpdated(const SpatialSourceEventArgs& args) {};
    virtual void OnSourceReleased(const SpatialSourceEventArgs& args) {};
    
};

using SpatialInteractionListenerRef = Ref<SpatialInteractionListener, RefParent1<Ecs::Engine>>;



// SpatialInteractionSystem
// Manages events from SpatialInteractionManager with additional filtering
class SpatialInteractionSystem final : public Ecs::System<SpatialInteractionSystem>
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
/*
    ISpatialInteractionManager GetInteractionManager() const
    {
        fail_fast_if(spatial_interaction_manager == nullptr);
        return spatial_interaction_manager;
    }*/

protected:
    bool Initialize() override;
    void Uninitialize() override;

private:
    Array<SpatialInteractionListenerRef> spatial_interaction_listeners;
    
    /*ISpatialInteractionManager spatial_interaction_manager = 0;

    enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    NativeEventToken source_tokens[SourceEvent::Count];


    void BindEventHandlers();
    void ReleaseEventHandlers();*/

    // Events Handlers
    /*void HandleSourceDetected(
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
*/
};


NAMESPACE_ECS_END
