#include "std_include.hpp"

#include "cef/cef_ui.hpp"
#include "cef/cef_ui_handler.hpp"

namespace cef
{
	cef_ui_handler::cef_ui_handler()
	{

	}

	cef_ui_handler::~cef_ui_handler()
	{

	}

	void cef_ui_handler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		CEF_REQUIRE_UI_THREAD();
		this->browser_list.push_back(browser);
	}

	void cef_ui_handler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
	{
		CEF_REQUIRE_UI_THREAD();

		for (auto bit = this->browser_list.begin(); bit != this->browser_list.end(); ++bit)
		{
			if ((*bit)->IsSame(browser))
			{
				this->browser_list.erase(bit);
				break;
			}
		}

		if (this->browser_list.empty())
		{
			CefQuitMessageLoop();
		}
	}

	bool cef_ui_handler::DoClose(CefRefPtr<CefBrowser> browser)
	{
		SetParent(browser->GetHost()->GetWindowHandle(), nullptr);
		return false;
	}

	void cef_ui_handler::OnBeforeContextMenu(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/, CefRefPtr<CefContextMenuParams> /*params*/, CefRefPtr<CefMenuModel> model)
	{
		model->Clear();
	}

	bool cef_ui_handler::OnContextMenuCommand(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/, CefRefPtr<CefContextMenuParams> /*params*/, int /*command_id*/, CefContextMenuHandler::EventFlags /*event_flags*/)
	{
		return false;
	}

	void cef_ui_handler::OnContextMenuDismissed(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/)
	{

	}

	bool cef_ui_handler::RunContextMenu(CefRefPtr<CefBrowser> /*browser*/, CefRefPtr<CefFrame> /*frame*/, CefRefPtr<CefContextMenuParams> /*params*/, CefRefPtr<CefMenuModel> /*model*/, CefRefPtr<CefRunContextMenuCallback> /*callback*/)
	{
		return false;
	}

	bool cef_ui_handler::is_closed(CefRefPtr<CefBrowser> browser)
	{
		for(const auto& browser_entry : this->browser_list)
		{
			if(browser_entry == browser)
			{
				return false;
			}
		}

		return true;
	}
}
