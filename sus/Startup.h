#include "Utils/Il2cpp/lazy_importer.hpp"
#include "Utils/bytes_font.h"
#include "Cheat/Hooks/detours/detours.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WndProcHook(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	static auto is_down = true;
	static auto is_clicked = false;

	if (GetAsyncKeyState(VK_INSERT))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GetAsyncKeyState(VK_INSERT) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked)
	{
		show = !show;
	}
	if (GetAsyncKeyState(vars::keys::locktarget) & 1) {
		vars::combat::lock_target = !vars::combat::lock_target;
	}
	auto pressed_buttons = false;
	auto pressed_menu_key = uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MOUSEWHEEL;

	if (!pressed_menu_key)
		pressed_buttons = true;
	if (!pressed_buttons && show && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return CallWindowProc(original_windowproc, hWnd, uMsg, wParam, lParam);
}
HRESULT resize_hook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {

	if (render_target_view) render_target_view->Release( );

	if (immediate_context) immediate_context->Release( );
	if (device) device->Release( );

	device = nullptr;

	return resize_original(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <string>
#pragma comment(lib, "wininet.lib")
using namespace std;


//string replaceAllgay(string subject, const string& search,
//	const string& replace) {
//	size_t pos = 0;
//	while ((pos = subject.find(search, pos)) != string::npos) {
//		subject.replace(pos, search.length(), replace);
//		pos += replace.length();
//	}
//	return subject;
//}
//
//string CheckLinkgay(string URL) {
//	HINTERNET interwebs = InternetOpenA(xorstr_("Mozilla/5.0"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
//	HINTERNET urlFile;
//	string rtn;
//	if (interwebs) {
//		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
//		if (urlFile) {
//			char buffer[2000];
//			DWORD bytesRead;
//			do {
//				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
//				rtn.append(buffer, bytesRead);
//				memset(buffer, 0, 2000);
//			} while (bytesRead);
//			InternetCloseHandle(interwebs);
//			InternetCloseHandle(urlFile);
//			string p = replaceAllgay(rtn, "|n", "\r\n");
//			return p;
//		}
//	}
//	InternetCloseHandle(interwebs);
//	string p = replaceAllgay(rtn, "|n", "\r\n");
//	return p;
//}
//void CheckVersionmenuversion(std::string version)
//{
//
//	if (CheckLinkgay(xorstr_("https://cdn.discordapp.com/attachments/1053534808531275837/1054344748359499896/pon")).c_str() != version) {
//		exit(-1);
//}
//
//};
//void Pasta() {
//	CheckVersionmenuversion(xorstr_("2.7"));
//};

HRESULT present_hook(IDXGISwapChain* swapChain, UINT SyncInterval, UINT Flags) {
	if (!device) {
		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&immediate_context);
		ID3D11Texture2D* renderTarget = nullptr;
		swapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
		device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
		renderTarget->Release( );
		ImGui::CreateContext( );
		ImGui_ImplWin32_Init(game_window);
		ImGui_ImplDX11_Init(device, immediate_context);
		//OxyRender::InitRender(swapChain);
		ImGui::StyleColorsDark();
		/*menu::style();*/
		ImFontConfig icons_config;
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig cfg;
		cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeBuilderFlags_Monochrome; //отключает антиалиасинг и дает строгий алгоритм хинта
		indShandow = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 30, NULL, io.Fonts->GetGlyphRangesCyrillic());
		pixel_s = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 13, NULL, io.Fonts->GetGlyphRangesCyrillic());
		calibri_ = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 13, NULL, io.Fonts->GetGlyphRangesCyrillic());
		fMain = io.Fonts->AddFontFromMemoryTTF(calibri, sizeof(calibri), 15, NULL, io.Fonts->GetGlyphRangesCyrillic());
		fSmall = io.Fonts->AddFontFromMemoryTTF(calibri, sizeof(calibri), 13, NULL, io.Fonts->GetGlyphRangesCyrillic());
		fName = io.Fonts->AddFontFromMemoryTTF(calibri, sizeof(calibri), 22, NULL, io.Fonts->GetGlyphRangesCyrillic());
		flogs = io.Fonts->AddFontFromMemoryTTF((void*)calibri, sizeof(calibri), 13.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	}

	immediate_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	immediate_context->RSGetViewports(&vps, &viewport);
	screen_size = {viewport.Width, viewport.Height};
	screen_center = {viewport.Width / 2.0f, viewport.Height / 2.0f};
	vars::stuff::ScreenHeight = viewport.Height;
	vars::stuff::ScreenWidth = viewport.Width;
	if (!vars::stuff::Panic) {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		DrawList = ImGui::GetBackgroundDrawList();
		notify::render();
		pre_draw();

		if (show) {
			//    drawShadowTestExampleWindow();
			//Pasta();

			menu::DrawMenu();
		}
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	else {
		vars::misc::fov = 90.f;
		MH_DisableHook(MH_ALL_HOOKS);
	}
	return present_original(swapChain, SyncInterval, Flags);
}
void Start( ) {
	vars::stor::gBase = (DWORD64)GetModuleHandleA(xorstr_("GameAssembly.dll"));
	vars::stor::uBase = (DWORD64)GetModuleHandleA(xorstr_("UnityPlayer.dll"));
	il2cpp::init();
	//init_bp();
	//unity::init_unity();

	while (!game_window) {
		EnumWindows([ ](HWND hWnd, LPARAM lParam) -> BOOL {
			DWORD pid = 0;
			GetWindowThreadProcessId(hWnd, &pid);
			if (pid == GetCurrentProcessId( )) {
				*reinterpret_cast<HWND*>(lParam) = hWnd;
				return FALSE;
			}

			return TRUE;
			}, reinterpret_cast<LPARAM>(&game_window));
	}

	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	auto featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd = {0};
	ZeroMemory(&sd, sizeof sd);
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = game_window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBoxW(0, xorstr_(L"Failed to create D3D11 device and swap chain"), xorstr_(L"Failure"), MB_ICONERROR);
	}
	else {
		auto table = *reinterpret_cast<PVOID**>(swapChain);
		present_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(table[ 8 ]);
		resize_original = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT)>(table[ 13 ]);

		context->Release( );
		device->Release( );
		swapChain->Release( );

		original_windowproc = (WNDPROC)SetWindowLongPtrW(game_window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);

		DetourTransactionBegin( );
		DetourUpdateThread(GetCurrentThread( ));
		DetourAttach(&(LPVOID&)present_original, (PBYTE)present_hook);
		DetourTransactionCommit( );

		DetourTransactionBegin( );
		DetourUpdateThread(GetCurrentThread( ));
		DetourAttach(&(LPVOID&)resize_original, (PBYTE)resize_hook);
		DetourTransactionCommit( );
		
	}
}