#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


#if 0

// IFrameworkViewSource methods

typename Holo::IFrameworkView
	AppViewSource::CreateView()
{
    return holographic_view;
}

// IFrameworkView methods

// The first method called when the IFrameworkView is being created.
// Use this method to subscribe for Windows shell events and to initialize your app.
void AppView::Initialize(const CoreApplicationView& app_view)
{
    app_view.Activated(std::bind(&AppView::OnViewActivated, this, _1, _2));

    // Register event handlers for app lifecycle.
    suspending_event = CoreApplication::Suspending(std::bind(&AppView::OnSuspending, this, _1, _2));

    resuming_event = CoreApplication::Resuming(std::bind(&AppView::OnResuming, this, _1, _2));

    main = std::make_unique<DemoRoomMain>();
}

void AppView::OnKeyPressed(const GfxCoreWindow& sender, const KeyEventArgs& args)
{
}

void AppView::OnPointerPressed(const GfxCoreWindow& sender, const PointerEventArgs& args)
{
}

// Called when the GfxCoreWindow object is created (or re-created).
void AppView::SetWindow(const GfxCoreWindow& window)
{
    // Register for keypress notifications.
    keydown_event = window.KeyDown(std::bind(&AppView::OnKeyPressed, this, _1, _2));

    // Register for pointer pressed notifications.
    pointer_pressed_event = window.PointerPressed(std::bind(&AppView::OnPointerPressed, this, _1, _2));

    // Register for notification that the app window is being closed.
    window_closed_event = window.Closed(std::bind(&AppView::OnWindowClosed, this, _1, _2));

    // Register for notifications that the app window is losing focus.
    visibility_changed_event = window.VisibilityChanged(std::bind(&AppView::OnVisibilityChanged, this, _1, _2));

    // Create a holographic space for the core window for the current view.
    // Presenting holographic frames that are created by this holographic space will put
    // the app into exclusive mode.
    holospace = HolographicSpace::CreateForGfxCoreWindow(window);

    // The main class uses the holographic space for updates and rendering.
    main->SetHolographicSpace(holospace);
}

// The Load method can be used to initialize scene resources or to load a
// previously saved app state.
void AppView::Load(const String& entry_point) {
	
}

// This method is called after the window becomes active. It oversees the
// update, draw, and present loop, and it also oversees window message processing.
void AppView::Run()
{
    while (!is_window_closed)
    {
        if (is_window_visible && (holospace != nullptr)) {
            GfxCoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

            main->Update();
        }
        else {
            GfxCoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }
}

// Terminate events do not cause Uninitialize to be called. It will be called if your IFrameworkView
// class is torn down while the app is in the foreground, for example if the Run method exits.
void AppView::Uninitialize()
{
    main.reset();

    CoreApplication::Suspending(suspending_event);
    CoreApplication::Resuming(resuming_event);

    auto const& window = GfxCoreWindow::GetForCurrentThread();
    window.KeyDown(keydown_event);
    window.PointerPressed(pointer_pressed_event);
    window.Closed(window_closed_event);
    window.VisibilityChanged(visibility_changed_event);
}


// Application lifecycle event handlers

// Called when the app is prelaunched. Use this method to load resources ahead of time
// and enable faster launch times.
void AppView::OnLaunched(const LaunchActivatedEventArgs& args)
{
    if (args.PrelaunchActivated())
    {
        //
        // TODO: Insert code to preload resources here.
        //
    }
}

// Called when the app view is activated. Activates the app's GfxCoreWindow.
void AppView::OnViewActivated(const CoreApplicationView& sender, const IActivatedEventArgs& args)
{
    // Run() won't start until the GfxCoreWindow is activated.
    sender.GfxCoreWindow().Activate();
}

void AppView::OnSuspending(const IInspectable& sender, SuspendingEventArgs const& args)
{
    // Save app state asynchronously after requesting a deferral. Holding a deferral
    // indicates that the application is busy performing suspending operations. Be
    // aware that a deferral may not be held indefinitely; after about five seconds,
    // the app will be forced to exit.
    SuspendingDeferral deferral = args.SuspendingOperation().GetDeferral();

    create_task([this, deferral]
    {
        if (main) {
            main->SaveAppState();
        }

        deferral.Complete();
    });
}

void AppView::OnResuming(const IInspectable& sender, const IInspectable& args)
{
    // Restore any data or state that was unloaded on suspend. By default, data
    // and state are persisted when resuming from suspend. Note that this event
    // does not occur if the app was previously terminated.

    if (main)
    {
        main->LoadAppState();
    }
}


// Window event handlers

void AppView::OnVisibilityChanged(const GfxCoreWindow& sender, const VisibilityChangedEventArgs& args)
{
    is_window_visible = args.Visible();
}

void AppView::OnWindowClosed(const GfxCoreWindow& sender, const GfxCoreWindowEventArgs& args)
{
    is_window_closed = true;
}


#endif

NAMESPACE_PARALLEL_END
