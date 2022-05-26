#pragma once


NAMESPACE_PARALLEL_BEGIN


// IFrameworkView class. Connects the app with the Windows shell and handles application lifecycle events.
template <class Holo>
class AppViewT : public Holo::template AppViewBase<AppViewT<Holo>>
{
public:
	using HoloSpace = typename Holo::HoloSpace;
	using CoreApplicationView = typename Holo::CoreApplicationView;
	using CoreWindow = typename Holo::CoreWindow;
	using NativeString = typename Holo::NativeString;
	using LaunchActivatedEventArgs = typename Holo::LaunchActivatedEventArgs;
	using IActivatedEventArgs = typename Holo::IActivatedEventArgs;
	using SuspendingEventArgs = typename Holo::SuspendingEventArgs;
	using IInspectable = typename Holo::IInspectable;
	using VisibilityChangedEventArgs = typename Holo::VisibilityChangedEventArgs;
	using CoreWindowEventArgs = typename Holo::CoreWindowEventArgs;
	using PointerEventArgs = typename Holo::PointerEventArgs;
	using KeyEventArgs = typename Holo::KeyEventArgs;
	using NativeEventToken = typename Holo::NativeEventToken;
	
	
    // IFrameworkView methods.
    void Initialize(const CoreApplicationView& app_view);
    void SetWindow(const CoreWindow& window);
    void Load(const NativeString& entry_point);
    void Run();
    void Uninitialize();

protected:
    // Application lifecycle event handlers.
    void OnLaunched(const LaunchActivatedEventArgs& args);
    void OnViewActivated(const CoreApplicationView& sender, const IActivatedEventArgs& args);
    void OnSuspending(const IInspectable& sender, const SuspendingEventArgs& args);
    void OnResuming(const IInspectable& sender, const IInspectable& args);

    // Window event handlers.
    void OnVisibilityChanged(const CoreWindow& sender, const VisibilityChangedEventArgs& args);
    void OnWindowClosed(const CoreWindow& sender, const CoreWindowEventArgs& args);

    // CoreWindow input event handlers.
    void OnKeyPressed(const CoreWindow& sender, const KeyEventArgs& args);
    void OnPointerPressed(const CoreWindow& sender, const PointerEventArgs& args);

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
    HoloSpace							holospace = 0;
    
};

template <class Holo>
class AppViewSourceT : public Holo::template AppViewSourceBase<AppViewSourceT<Holo>> {
	
public:
	using IFrameworkView = typename Holo::IFrameworkView;
	
    // IFrameworkViewSource method.
    IFrameworkView CreateView();

private:
    AppViewT<Holo> holographic_view;
    
};


NAMESPACE_PARALLEL_END

