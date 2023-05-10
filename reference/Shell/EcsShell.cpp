#include "EcsShell.h"


// UWP solution is different
#ifdef flagUWP

using namespace concurrency;
using namespace std::placeholders;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::UI::Core;

NAMESPACE_TOPSIDE_BEGIN


void DesktopMain() {
	using namespace Parallel;
	
    CoreApplication::Run(AppViewSource());
}


NAMESPACE_TOPSIDE_END


GUI_APP_MAIN
{
	using namespace TS;
	Serial::Machine::WhenInitialize << callback(DefaultSerialInitializer);
	Serial::Machine::WhenPreFirstUpdate << callback(DefaultStartup);
	Serial::Machine::WhenUserProgram << callback(DesktopMain);
	
	SingleMachine mach;
	if (mach.Start()) {
		DefaultRunner(0, "Shell");
		
		mach.Stop();
	}
}


#else


#ifdef flagGUI

// Just call default macro in AtomComplete
DEFAULT_ECS_SHELL

#else

DEFAULT_ATOMSHELL

#endif


#endif


#include <Complete/Cmake.inl>
