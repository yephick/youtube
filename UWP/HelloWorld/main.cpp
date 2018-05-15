#include "pch.h"

using namespace winrt;

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Markup;

struct App : ApplicationT<App>{
    fire_and_forget OnLaunched(const LaunchActivatedEventArgs &)
    {
        const auto packageFolder = Package::Current().InstalledLocation();
        const auto file = co_await packageFolder.GetFileAsync(L"MainPage.xaml");
        const auto xaml = co_await FileIO::ReadTextAsync(file);

        const auto body = XamlReader::Load(xaml).as<Page>();

        auto window = Window::Current();
        window.Content(body);
        window.Activate();
    }
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    Application::Start([](auto&&){make<App>();});
}
