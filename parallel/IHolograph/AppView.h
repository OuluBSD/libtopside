#pragma once


NAMESPACE_PARALLEL_BEGIN


// IFrameworkView class. Connects the app with the Windows shell and handles application lifecycle events.
class AppView sealed : public winrt::implements<AppView, IFrameworkView>
{
public:
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
    One<DemoRoomMain>					main;

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

class AppViewSource sealed : public winrt::implements<AppViewSource, IFrameworkViewSource>
{
public:
    // IFrameworkViewSource method.
    IFrameworkView CreateView();

private:
    AppView holographic_view;
    
};


NAMESPACE_PARALLEL_END

