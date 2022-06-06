#ifndef _EcsLocal_InteractionSystem_h_
#define _EcsLocal_InteractionSystem_h_

NAMESPACE_ECS_BEGIN


struct ControllerEventArgs {
	
};


struct PlayerInteractionListener :
	WeakRefScopeEnabler<PlayerInteractionListener, Engine>,
	RTTIBase
{
	RTTI_DECL0(PlayerInteractionListener)
	
    virtual void OnControllerDetected(const ControllerEventArgs& args) {};
    virtual void OnControllerLost(const ControllerEventArgs& args) {};
    virtual void OnControllerPressed(const ControllerEventArgs& args) {};
    virtual void OnControllerUpdated(const ControllerEventArgs& args) {};
    virtual void OnControllerReleased(const ControllerEventArgs& args) {};
    
};

using PlayerInteractionListenerRef = Ref<PlayerInteractionListener, RefParent1<Ecs::Engine>>;



class PlayerInteractionSystem :
	public Ecs::System<PlayerInteractionSystem>
{
public:
	ECS_SYS_CTOR(PlayerInteractionSystem)
	
    void AddListener(PlayerInteractionListenerRef listener) {
        player_interaction_listeners.Add(listener);
    }

    void RemoveListener(PlayerInteractionListenerRef listener) {
        player_interaction_listeners.Remove(listener);
    }

    
protected:
    bool Initialize() override;
    void Uninitialize() override;
    void Update(double dt) override;

private:
    Array<PlayerInteractionListenerRef> player_interaction_listeners;
    
    
    void BindEventHandlers();
    
    /*enum SourceEvent {
        Detected, Pressed, Updated, Released, Lost, Count
    };

    NativeEventToken source_tokens[SourceEvent::Count];
    */
    
	
    void ReleaseEventHandlers();
	
    // Events Handlers
    void HandleSourceDetected(const ControllerEventArgs& args);
    void HandleSourceLost(const ControllerEventArgs& args);
    void HandleSourcePressed(const ControllerEventArgs& args);
    void HandleSourceUpdated(const ControllerEventArgs& args);
    void HandleSourceReleased(const ControllerEventArgs& args);
    
};


NAMESPACE_ECS_END

#endif
