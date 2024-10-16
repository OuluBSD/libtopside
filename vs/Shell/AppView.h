#pragma once

#include "Common\DeviceResources.h"
#include "BasicHologramMain.h"

namespace BasicHologram
{
    // IFrameworkView class. Connects the app with the Windows shell and handles application lifecycle events.
    ref class AppView sealed : public Windows::ApplicationModel::Core::IFrameworkView
    {
    public:
        AppView();

        // IFrameworkView methods.
        virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
        virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
        virtual void Load(Platform::String^ entryPoint);
        virtual void Run();
        virtual void Uninitialize();

    protected:
        // Application lifecycle event handlers.
        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args);
        void OnViewActivated(Windows::ApplicationModel::Core::CoreApplicationView^ sender, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
        void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
        void OnResuming(Platform::Object^ sender, Platform::Object^ args);

        // Window event handlers.
        void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
        void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);

        // CoreWindow input event handlers.
        void OnKeyPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
        void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);

    private:
        std::unique_ptr<BasicHologramMain> m_main;

        std::shared_ptr<DX::DeviceResources>                m_deviceResources;
        bool                                                m_windowClosed  = false;
        bool                                                m_windowVisible = true;

        // The holographic space the app will use for rendering.
        Windows::Graphics::Holographic::HolographicSpace^   m_holographicSpace = nullptr;
    };

    // The entry point for the app.
    ref class AppViewSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
    {
    public:
        virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
    };
}
