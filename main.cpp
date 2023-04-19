#include "pch.h"
#include "Order.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Microsoft::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Fake
{
	class MainWindow : public WindowT<MainWindow>
	{
	public:
		MainWindow()
		{
			StackPanel stackPanel;
			stackPanel.HorizontalAlignment(HorizontalAlignment::Stretch);
			stackPanel.VerticalAlignment(VerticalAlignment::Stretch);

			for (int i = 0; i < 100; i++)
			{
				auto order = make<Fake::implementation::Order>();
				order.Amount(L"100.00");

				m_Orders.Append(order);
			}

			//for (auto item : m_Orders)
			//{
			//	auto order = item.as<Fake::Order>();
			//	OutputDebugString((order.Amount() + L"\r\n").c_str());
			//}

			DataTemplate dt = winrt::Microsoft::UI::Xaml::Markup::XamlReader::Load(LR"(
					<DataTemplate xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation'
								  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
								  xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
								  xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
								  mc:Ignorable="d"
								  xmlns:local="using:winrt.Fake">
						<StackPanel Orientation="Horizontal">
							<TextBlock Text='{Binding Amount}' FontFamily="Consolas" FontSize="12"/>
						</StackPanel>
					</DataTemplate>	
							 )").as<DataTemplate>();
			m_ListView.ItemsSource(m_Orders);
			m_ListView.ItemTemplate(dt);
			
			m_MainViewer.Content(stackPanel);
			Content(m_MainViewer);

			stackPanel.Children().Append(m_ListView);
		}

	private:
		ScrollViewer m_MainViewer{ ScrollViewer() };
		ListView m_ListView{ ListView() };
		IObservableVector<Fake::Order> m_Orders{ winrt::single_threaded_observable_vector<Fake::Order>() };
	};

	class App : public ApplicationT<App, IXamlMetadataProvider>
	{
	public:
		void OnLaunched(LaunchActivatedEventArgs const&)
		{
			Resources().MergedDictionaries().Append(XamlControlsResources());

			window = make<MainWindow>();
			window.Activate();
		}
		IXamlType GetXamlType(TypeName const& type)
		{
			return provider.GetXamlType(type);
		}
		IXamlType GetXamlType(hstring const& fullname)
		{
			return provider.GetXamlType(fullname);
		}
		com_array<XmlnsDefinition> GetXmlnsDefinitions()
		{
			return provider.GetXmlnsDefinitions();
		}
	private:
		Window window{ nullptr };
		XamlControlsXamlMetaDataProvider provider;
	};
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment();
	Application::Start([](auto&&) { make<Fake::App>(); });
	return 0;
}
