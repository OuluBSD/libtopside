#pragma once

#if 0

NAMESPACE_PARALLEL_BEGIN


// IFrameworkView class. Connects the app with the Windows shell and handles application lifecycle events.
class AppView /*: public Holo::template AppViewBase<AppView>*/
{
public:
	/*using HolographicSpace = typename Holo::HolographicSpace;
	using CoreApplicationView = typename Holo::CoreApplicationView;
	using GfxCoreWindow = typename Holo::GfxCoreWindow;
	using NativeString = typename Holo::NativeString;
	using LaunchActivatedEventArgs = typename Holo::LaunchActivatedEventArgs;
	using IActivatedEventArgs = typename Holo::IActivatedEventArgs;
	using SuspendingEventArgs = typename Holo::SuspendingEventArgs;
	using IInspectable = typename Holo::IInspectable;
	using VisibilityChangedEventArgs = typename Holo::VisibilityChangedEventArgs;
	using GfxCoreWindowEventArgs = typename Holo::GfxCoreWindowEventArgs;
	using PointerEventArgs = typename Holo::PointerEventArgs;
	using KeyEventArgs = typename Holo::KeyEventArgs;
	using NativeEventToken = typename Holo::NativeEventToken;
	*/
	
    // IFrameworkView methods.
    void Initialize(const CoreApplicationView& app_view);
    void SetWindow(const GfxCoreWindow& window);
    void Load(const String& entry_point);
    void Run();
    void Uninitialize();

protected:
    // Application lifecycle event handlers.
    void OnLaunched(const LaunchActivatedEventArgs& args);
    void OnViewActivated(const CoreApplicationView& sender, const ActivatedEventArgs& args);
    void OnSuspending(const Inspectable& sender, const SuspendingEventArgs& args);
    void OnResuming(const Inspectable& sender, const Inspectable& args);

    // Window event handlers.
    void OnVisibilityChanged(const GfxCoreWindow& sender, const VisibilityChangedEventArgs& args);
    void OnWindowClosed(const GfxCoreWindow& sender, const GfxCoreWindowEventArgs& args);

    // GfxCoreWindow input event handlers.
    void OnKeyPressed(const GfxCoreWindow& sender, const KeyEventArgs& args);
    void OnPointerPressed(const GfxCoreWindow& sender, const PointerEventArgs& args);

private:
    //One<DemoRoomMain>					main;

    bool								is_window_closed  = false;
    bool								is_window_visible = true;

    // Event registration tokens.
    NativeEventToken					suspending_event;
    NativeEventToken					resuming_event;
    NativeEventToken					keydown_event;
    NativeEventToken					pointer_pressed_event;
    NativeEventToken					window_closed_event;
    NativeEventToken					visibility_changed_event;

    // The holographic space the app will use for rendering.
    HolographicSpace*					holospace = 0;
    
};

class AppViewSource /*: public Holo::template AppViewSourceBase<AppViewSource>*/ {
	
public:
	
    // IFrameworkViewSource method.
    FrameworkView CreateView();

private:
    AppView holographic_view;
    
};


NAMESPACE_PARALLEL_END

#endif
