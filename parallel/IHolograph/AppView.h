#pragma once


NAMESPACE_PARALLEL_BEGIN


// IFrameworkView class. Connects the app with the Windows shell and handles application lifecycle events.
class AppView sealed : public winrt::implements<AppView, IFrameworkView>
{
public:
    // IFrameworkView methods.
    void Initialize(const CoreApplicationView& applicationView);
    void SetWindow(CoreWindow const& window);
    void Load(winrt::hstring const& entryPoint);
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
    One<DemoRoomMain>					m_main;

    bool								m_windowClosed  = false;
    bool								m_windowVisible = true;

    // Event registration tokens.
    NativeEventToken					m_suspendingEventToken;
    NativeEventToken					m_resumingEventToken;
    NativeEventToken					m_keyDownEventToken;
    NativeEventToken					m_pointerPressedEventToken;
    NativeEventToken					m_windowClosedEventToken;
    NativeEventToken					m_visibilityChangedEventToken;

    // The holographic space the app will use for rendering.
    HoloSpace					m_holospace = nullptr;
};

class AppViewSource sealed : public winrt::implements<AppViewSource, IFrameworkViewSource>
{
public:
    // IFrameworkViewSource method.
    IFrameworkView CreateView();

private:
    AppView holographicView;
    
};


NAMESPACE_PARALLEL_END

