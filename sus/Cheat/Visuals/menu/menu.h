#include <vector>
#include <algorithm>
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
bool applied = false;
static bool sh_save_cfg = false;
static bool sh_load_cfg = false;
#include <chrono>
#include "Elements/tap.hpp"
#include "Elements/childs.hpp"
#include "Elements/checkbox.hpp"
#include "Elements/combo.hpp"
#include "Elements/slider.hpp"
#include "Elements/Button.hpp"
#include <xstring>


long getMils() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

int y = 0;
#include <map>

bool SubTabEx(const char* label, const bool active, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x, label_size.y + style.FramePadding.y);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		ImGui::MarkItemEdited(id);
	ImGui::RenderNavHighlight(bb, id);
	struct TabAnimation {
		ImColor RectFilen;
		ImColor MultiRect;
		ImColor MultiRect2;
		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	ImColor one = ImColor(accent_color[0], accent_color[1], accent_color[2], 255 * 0.2), two = ImColor(accent_color[0], accent_color[1], accent_color[2], 0);
	TabItemMap->second.RectFilen = ImLerp(TabItemMap->second.RectFilen.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2]) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect = ImLerp(TabItemMap->second.MultiRect.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2], 255 * 0.2) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect2 = ImLerp(TabItemMap->second.MultiRect2.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2], 0) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	//if (active)
   // {
	window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Max.y - 4), bb.Max, TabItemMap->second.RectFilen, 4, ImDrawFlags_RoundCornersTop);

	window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Max.y - 25), bb.Max, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect, TabItemMap->second.MultiRect);
	//}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(110, 110, 110)));

	ImGui::PushFont(fMain);
	ImGui::RenderTextClipped(bb.Min, bb.Max, label, NULL, &label_size, ImVec2(0.5, 0.5), &bb);
	ImGui::PopFont();

	ImGui::PopStyleColor();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, icon, window->DC.LastItemStatusFlags);
	return pressed;
}
bool SubTab(const char* label, const bool active, const ImVec2& size_arg)
{
	return SubTabEx(label, active, size_arg, 0);
}

/*                     CHEATNAME GUI                     */
bool TabEx(const char* icon, const char* label, const bool active, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(icon);
	const ImVec2 icon_size = fIcons->CalcTextSizeA(20, FLT_MAX, 0, icon, NULL);
	const ImVec2 label_size = fMain->CalcTextSizeA(15, FLT_MAX, 0, label, NULL);

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x, label_size.y + style.FramePadding.y);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);
	if (pressed)
		ImGui::MarkItemEdited(id);
	ImGui::RenderNavHighlight(bb, id);
	struct TabAnimation {
		ImColor RectFilen;
		ImColor MultiRect;
		ImColor MultiRect2;
		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	ImColor one = ImColor(accent_color[0], accent_color[1], accent_color[2], 255 * 0.2), two = ImColor(accent_color[0], accent_color[1], accent_color[2], 0);
	TabItemMap->second.RectFilen = ImLerp(TabItemMap->second.RectFilen.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2]) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect = ImLerp(TabItemMap->second.MultiRect.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2], 255 * 0.2) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.MultiRect2 = ImLerp(TabItemMap->second.MultiRect2.Value, active ? ImColor(accent_color[0], accent_color[1], accent_color[2], 0) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	/*  if (active)
	  {*/
	window->DrawList->AddRectFilled(bb.Min, ImVec2(bb.Min.x + 4, bb.Max.y), TabItemMap->second.RectFilen, 4, ImDrawFlags_RoundCornersRight);

	window->DrawList->AddRectFilledMultiColor(bb.Min, ImVec2(bb.Min.x + 100, bb.Max.y), TabItemMap->second.MultiRect, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect2, TabItemMap->second.MultiRect);
	//}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(100, 100, 100)));

	ImGui::RenderTextClipped(bb.Min + ImVec2(30, 0), bb.Max - style.FramePadding, icon, NULL, &icon_size, ImVec2(0.f, 0.5f), &bb);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(active ? ImColor(255, 255, 255) : hovered ? ImColor(200, 200, 200) : ImColor(100, 100, 100)));

	ImGui::PushFont(fMain);
	ImGui::RenderTextClipped(bb.Min + ImVec2(55, 0), bb.Max - style.FramePadding, label, NULL, &label_size, ImVec2(0.f, 0.5f), &bb);
	ImGui::PopFont();

	ImGui::PopStyleColor(2);


	IMGUI_TEST_ENGINE_ITEM_INFO(id, icon, window->DC.LastItemStatusFlags);
	return pressed;
}
bool Tab(const char* icon, const char* label, const bool active, const ImVec2& size_arg)
{
	return TabEx(icon, label, active, size_arg, 0);
}

bool MenuChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;

	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoMove;
	//flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

	// Size
	const ImVec2 content_avail = ImGui::GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
	if (size.x <= 0.0f)
		size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
	if (size.y <= 0.0f)
		size.y = ImMax(content_avail.y + size.y, 4.0f);
	ImGui::SetNextWindowSize(size);

	// Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
	char title[256];

	const char* temp_window_name;
	if (name)
		ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
	else
		ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;
	if (!border)
		g.Style.ChildBorderSize = 0.0f;
	bool ret = ImGui::Begin(temp_window_name, NULL, flags);
	g.Style.ChildBorderSize = backup_border_size;
	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;
	child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

	// Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
	// While this is not really documented/defined, it seems that the expected thing to do.
	if (child_window->BeginCount == 1)
		parent_window->DC.CursorPos = child_window->Pos;

	auto p = parent_window->DC.CursorPos;
	parent_window->DrawList->AddRect(p, p + size, ImColor(30, 30, 30), 8, 18, 4);
	if (!(flags & ImGuiWindowFlags_NoTitleBar))
	{
		auto size_text = fMain->CalcTextSizeA(15, FLT_MAX, 0, name);
		parent_window->DrawList->AddText(fMain, 15, ImVec2(p.x + (size.x - size_text.x) / 2, p.y + 10), ImColor(255, 255, 255), name);
		parent_window->DrawList->AddRectFilled(ImVec2(p.x + 10, p.y + 30), ImVec2(p.x + size.x - 10, p.y + 34), ImColor(accent_color[0], accent_color[1], accent_color[2]));
	}

	// Process navigation-in immediately so NavInit can run on first frame
	if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
	{
		ImGui::FocusWindow(child_window);
		ImGui::NavInitWindow(child_window, false);
		ImGui::SetActiveID(id + 1, child_window); // Steal ActiveId with a dummy id so that key-press won't activate child item
		g.ActiveIdSource = ImGuiInputSource_Nav;
	}
	if (!(flags & ImGuiWindowFlags_NoTitleBar))
		ImGui::SetCursorPosY(40);
	return ret;
}
bool MenuChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	return MenuChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags);
}

bool Checkbox_(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		ImGui::MarkItemEdited(id);
	}

	const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));
	ImGui::RenderNavHighlight(total_bb, id);
	struct TabAnimation {
		ImColor CheckboxFrame;
		ImColor CircleFrame;
		ImColor Text;
		float CirclePos;
	};

	static std::map< ImGuiID, TabAnimation > TabMap;
	auto TabItemMap = TabMap.find(id);
	if (TabItemMap == TabMap.end()) {
		TabMap.insert({ id, TabAnimation() });
		TabItemMap = TabMap.find(id);
	}
	TabItemMap->second.CheckboxFrame = ImLerp(TabItemMap->second.CheckboxFrame.Value, *v ? ImColor(accent_color[0], accent_color[1], accent_color[2]) : ImColor(accent_color[0], accent_color[1], accent_color[2], 170), g.IO.DeltaTime * 8.f * 0.8);
	TabItemMap->second.CircleFrame = ImLerp(TabItemMap->second.CircleFrame.Value, *v ? ImColor(accent_color[0], accent_color[1], accent_color[2]) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 8.f * 0.8);
	window->DrawList->AddRect(check_bb.Min, check_bb.Max, TabItemMap->second.CheckboxFrame, 4);

	window->DrawList->AddRectFilled(check_bb.Min + ImVec2(3, 3), check_bb.Max - ImVec2(3, 3), TabItemMap->second.CircleFrame, 4);

	if (g.LogEnabled)
		ImGui::LogRenderedText(&total_bb.Min, *v ? "[x]" : "[ ]");
	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;
}

bool Checkbox__(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos + ImVec2(0, 0), window->DC.CursorPos + ImVec2(0, 0) + ImVec2(label_size.y + style.FramePadding.y * 2, label_size.y + style.FramePadding.y * 2));
	ImGui::ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;
	if (label_size.x > 0)
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
	const ImRect text_bb(window->DC.CursorPos + ImVec2(0, 0) + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, 0) + ImVec2(0, style.FramePadding.y) + label_size);
	if (label_size.x > 0)
	{
		ImGui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}

	if (!ImGui::ItemAdd(total_bb, id))
		return false;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);
	static std::map<ImGuiID, float> hover_animation;
	auto it_hover = hover_animation.find(id);
	if (it_hover == hover_animation.end())
	{
		hover_animation.insert({ id, 0.f });
		it_hover = hover_animation.find(id);
	}
	it_hover->second = ImClamp(it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered ? 1.f : -5.f)), 0.0f, 0.12f);
	it_hover->second *= g.Style.Alpha;
	static std::map<ImGuiID, float> filled_animation;
	auto it_filled = filled_animation.find(id);
	if (it_filled == filled_animation.end())
	{
		filled_animation.insert({ id, 0.f });
		it_filled = filled_animation.find(id);
	}
	it_filled->second = ImClamp(it_filled->second + (2.35f * ImGui::GetIO().DeltaTime * ((*v) ? 2.f : -2.f)), it_hover->second, 1.f);
	it_filled->second *= g.Style.Alpha;
	const float check_sz = ImMin(check_bb.GetWidth() - 5, check_bb.GetHeight() - 5);
	const float pad = ImMax(1.0f, (float)(int)(check_sz / 6.0f));
	ImVec4 text = ImLerp(ImVec4{ 141 / 255.f, 146 / 255.f, 154 / 255.f, g.Style.Alpha }, ImVec4{ 255 / 255.f, 255 / 255.f, 255 / 255.f, g.Style.Alpha }, it_filled->second);

	ImGui::RenderFrame(check_bb.Min + ImVec2(pad, pad), check_bb.Max - ImVec2(pad, pad), ImColor(accent_color[0], accent_color[1], accent_color[2], (int)(255 * g.Style.Alpha)), false, 4);
	ImGui::RenderFrame(check_bb.Min + ImVec2(pad + 1, pad + 1), check_bb.Max - ImVec2(pad + 1, pad + 1), ImColor(25, 25, 25, int(255 * ImGui::GetStyle().Alpha)), false, 4);
	ImGui::RenderFrame(check_bb.Min + ImVec2(pad, pad), check_bb.Max - ImVec2(pad, pad), ImColor(accent_color[0], accent_color[1], accent_color[2], (int)(255 * it_filled->second)), false, 4);
	if (*v)
		ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(5, 5), ImColor(255, 255, 255, (int)(255 * it_filled->second)), 9);

	if (label_size.x > 0.0f) {
		ImGui::GetWindowDrawList()->AddText(text_bb.GetTL(), ImColor(text), label);
	}

	return pressed;
}


namespace Anime {
	bool reverse = false;
	//bool done = false;
	int offset = 0;
	bool show_popup = false;

	void Popup(const char* text, int onScreenMils, bool* done) {
		if (!done)
			show_popup = true;

		ImGuiIO& io = ImGui::GetIO();
		int Wd = io.DisplaySize.x;

		static long oldTime = -1;

		ImGui::SetNextWindowPos(ImVec2(Wd - offset, 7));
		ImGui::Begin("PopUp Window", &show_popup, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		ImGui::BeginChild(xorstr_("##linerender"), ImVec2(110, 1)); ImGui::EndChild();
		long currentTime_ms = getMils();

		ImVec2 txtSz = ImGui::CalcTextSize(text);
		ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - txtSz.y / 2);
		ImGui::Text(text);

		/*if (ImGui::Button("Close Me")) {
			reverse = true;
		}*/
		if (!reverse)
		{
			if (offset < ImGui::GetWindowWidth())
				offset += (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);

			if (offset >= ImGui::GetWindowWidth() && oldTime == -1)
			{

				oldTime = currentTime_ms;
			}
		}
		//ImGui::Text("ot: %d", oldTime);

		if (currentTime_ms - oldTime >= onScreenMils && oldTime != -1) // close after x mils
			reverse = true;

		if (reverse)
		{
			if (offset > 0)
				offset -= (ImGui::GetWindowWidth() + 5) * ((1000.0f / ImGui::GetIO().Framerate) / 100);
			if (offset <= 0)
			{
				offset = 0;
				reverse = false;
				*done = true;
				oldTime = -1;
				show_popup = false;

			}
		}

		ImGui::End();
	}
}
class dot
{
public:
	dot(Vector3 p, Vector3 v) {
		m_vel = v;
		m_pos = p;
	}

	void update();
	void draw();

	Vector3 m_pos, m_vel;
};

std::vector<dot*> dots = { };

void dot::update() {
	auto opacity = 240 / 255.0f;

	m_pos += m_vel * (opacity);
}

void dot::draw() {
	int opacity = 55.0f * (240 / 255.0f);

	ImGui::GetWindowDrawList()->AddRectFilled({ m_pos.x - 2, m_pos.y - 2 }, { m_pos.x + 2, m_pos.y + 2 }, ImColor(255, 0, 100, 255));

	auto t = std::find(dots.begin(), dots.end(), this);
	if (t == dots.end()) {
		return;
	}

	for (auto i = t; i != dots.end(); i++) {
		if ((*i) == this) continue;

		auto dist = (m_pos - (*i)->m_pos).length_2d();

		if (dist < 128) {
			int alpha = opacity * (dist / 128);
			ImGui::GetWindowDrawList()->AddLine({ m_pos.x - 1, m_pos.y - 2 }, { (*i)->m_pos.x - 2, (*i)->m_pos.y - 1 }, ImColor(180, 68, 124, 255));
		}
	}
}
void dot_draw() {
	struct screen_size {
		int x, y;
	}; screen_size sc;

	sc.x = 3840, sc.y = 2160;

	int s = rand() % 9;

	if (s == 0) {
		dots.push_back(new dot(Vector3(rand() % (int)sc.x, -16, 0), Vector3((rand() % 7) - 3, rand() % 3 + 1, 0)));
	}
	else if (s == 1) {
		dots.push_back(new dot(Vector3(rand() % (int)sc.x, (int)sc.y + 16, 0), Vector3((rand() % 7) - 3, -1 * (rand() % 3 + 1), 0)));
	}
	else if (s == 2) {
		dots.push_back(new dot(Vector3(-16, rand() % (int)sc.y, 0), Vector3(rand() % 3 + 1, (rand() % 7) - 3, 0)));
	}
	else if (s == 3) {
		dots.push_back(new dot(Vector3((int)sc.x + 16, rand() % (int)sc.y, 0), Vector3(-1 * (rand() % 3 + 1), (rand() % 7) - 3, 0)));
	}

	auto alph = 135.0f * (240 / 255.0f);
	auto a_int = (int)(alph);

	ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

	for (auto i = dots.begin(); i < dots.end();) {
		if ((*i)->m_pos.y < -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
			delete (*i);
			i = dots.erase(i);
		}
		else {
			(*i)->update();
			i++;
		}
	}

	for (auto i = dots.begin(); i < dots.end(); i++) {
		(*i)->draw();
	}
}
//ImFont* initx;
//void Init()
//{
//	// Setup
//	auto front = ImGui::GetForegroundDrawList(); // also you can use GetWindowDrawList() or GetBackgroundDrawList()
//	ImVec2 center = ImGui::GetIO().DisplaySize / 2.f;
//	static ImColor fore_color(192, 192, 192);
//	static ImColor back_color(0, 0, 0, 25);
//	static float arc_size = 0.45f; // 0.f < x < 2.f
//	static float radius = 15.f;
//	static float thickness = 6.f;
//	static float Alpha = 0.0f;
//	int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
//	int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
//	auto back = ImGui::GetBackgroundDrawList();
//
//	if (Alpha < 0.65f)
//		Alpha += 0.005f;
//	back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX, screenHeightY), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, Alpha)));
//
//
//	// Animation
//	static float position = 0.f;
//	position = ImLerp(position, IM_PI * 2.f, ImGui::GetIO().DeltaTime * 2.3f);
//
//	// Background
//	front->PathClear();
//	front->PathArcTo(center, radius, 0.f, 2.f * IM_PI, 35.f);
//	front->PathStroke(ImGui::GetColorU32(back_color.Value), 0, thickness);
//
//	// Foreground
//	front->PathClear();
//	front->PathArcTo(center, radius, IM_PI * 1.5f + position, IM_PI * (1.5f + arc_size) + position, 35.f);
//	front->PathStroke(ImGui::GetColorU32(fore_color.Value), 0, thickness);
//	ImGui::PushFont(initx);
//	auto MiddleX = vars::stuff::_ScreenWidth / 2;
//	auto MiddleY = vars::stuff::_ScreenHigh / 2;
//	ImGui::PopFont();
//
//	// Reset animation
//	if (position >= IM_PI * 1.90f)
//		position = 0.f;
//}
const char* const KeyNames[] = {
	"None",
	"Mouse1",
	"Mouse2",
	"Esc",
	"Mouse3",
	"Mouse4",
	"Mouse5",
	"None",
	"Back",
	"Tab",
	"None",
	"None",
	"Backspace",
	"Enter",
	"None",
	"None",
	"Shift",
	"Ctrl",
	"Alt",
	"Pause Break",
	"CapsLock",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"Esc",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"Print Screen",
	"Ins",
	"Del",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Left Windows",
	"Right Windows",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9",
	"Multiply",
	"+",
	"Separator",
	"Subtract",
	"-",
	"/",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Num Lock",
	"Scroll lock",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Left Shift",
	"Right Shift",
	"Left Ctrl",
	"Right Ctrl",
	"Left Alt",
	"Right Alt"
};


static bool _IsKeyPressedMap(ImGuiKey key, bool repeat = true)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return (key_index >= 0) ? ImGui::IsKeyPressed((ImGuiKey)key_index, repeat) : false;
}
inline bool     FocusableItemRegister(ImGuiWindow* window, ImGuiID id) { IM_ASSERT(0); IM_UNUSED(window); IM_UNUSED(id); return false; }
bool KeyBind(const char* label, int& k, const ImVec2& size_arg = ImVec2(0, 0))
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 1.0f);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = FocusableItemRegister(window, g.ActiveId == id);
	//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (_IsKeyPressedMap(ImGuiKey_Escape)) {
			k = 0;
			ImGui::ClearActiveID();
		}
		else {
			k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, (ImColor(35, 35, 35)), true, 6.f);

	if (k != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, KeyNames[k]);
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "...");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding * 0.8, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Max.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}
void invis(bool background, bool dotdraw)
{
	if (background) {
		static float Alpha = 0.0f;
		int screenWidthX = GetSystemMetrics(SM_CXSCREEN);
		int screenHeightY = GetSystemMetrics(SM_CYSCREEN);
		auto back = ImGui::GetBackgroundDrawList();

		if (Alpha < 0.65f)
			Alpha += 0.005f;
		back->AddRectFilled(ImVec2(0, 0), ImVec2(screenWidthX, screenHeightY), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, Alpha)));
	}

	auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	{
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0,0,0,0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		ImGui::Begin("##menu2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove);
		{
			if (dotdraw) {
				dot_draw();
			}
		}
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
	}
}
namespace menu {
	struct TabInfo {
		ImRect bb;
		unsigned int index;
	};
	ImVec2 cursor_pos = { 0,0 };
	ImFont* title_font = nullptr, * tabs_font = nullptr, * menu_font = nullptr;
	static int tab_index = 0;
	static float border_bang = 1.0f;
	static int old_tab_index = 0;
	std::vector<TabInfo> tabs_info;

	void apply_fonts() {
		ImGuiIO& io = ImGui::GetIO();
		title_font = io.Fonts->AddFontFromFileTTF("", 24);
		tabs_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16);
		menu_font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
	}
	void HelpMarker(const char* desc) {
		ImGui::TextDisabled(xorstr_("[?]"));
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	void HelpCheckbox(const char* desc, bool* v, const char* helptext) { Checkbox_(desc, v); ImGui::SameLine(); HelpMarker(helptext); }
	void style(ImGuiStyle* dst) {

		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
		colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
		colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	bool tab_info_already_exist(std::vector<TabInfo> infos, unsigned int index) {
		for (int i = 0; i < infos.size(); i++)
			if (infos[i].index == index) return true;

		return false;
	}
	void TabBorderAnim(unsigned int current_tab, unsigned int old_tab) {
		if (tabs_info.size() > 0) {
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			if (window->SkipItems)
				return;
			auto& style = ImGui::GetStyle();
			auto old_tab_rect = tabs_info[old_tab].bb;
			auto tab_rect = tabs_info[current_tab].bb;
			auto tab_min = old_tab_rect.Min + (tab_rect.Min - old_tab_rect.Min) * border_bang;
			auto tab_max = old_tab_rect.Max + (tab_rect.Max - old_tab_rect.Max) * border_bang;
			window->DrawList->AddRectFilled(tab_min, tab_max, ImColor(110, 110, 110, 255), style.FrameRounding, ImDrawFlags_RoundCornersAll);
		}

	}
	IMGUI_API bool TabButton(const char* label, const ImVec2& size_arg, unsigned int index, ImGuiButtonFlags flags = 0) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset)
			pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id))
			return false;

		if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
			flags |= ImGuiButtonFlags_Repeat;
		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

		// Render
		const ImU32 col = ImGui::GetColorU32((hovered && held) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		const ImU32 border_col = ImGui::GetColorU32((hovered && held) ? ImGui::GetColorU32(ImVec4(1, 1, 1, 0.7)) : hovered ? ImColor(110, 110, 110, 115) : ImGui::GetColorU32(ImVec4(1, 1, 1, 0.0)));
		window->DrawList->AddRectFilled(bb.Min, bb.Max, border_col, style.FrameRounding, ImDrawFlags_RoundCornersAll);
		ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
		if (!tab_info_already_exist(tabs_info, index)) {
			TabInfo tab_info;
			tab_info.bb = bb;
			tab_info.index = index;
			tabs_info.push_back(tab_info);
		}

		return pressed;
	}
	IMGUI_API bool Tab(unsigned int index, const char* label, int* selected, float width = 0) {
		if (TabButton(label, ImVec2(width, 30), index)) {
			border_bang = 0.0f;
			old_tab_index = *selected;
			*selected = index;
		}
		return *selected == index;
	}
}
namespace menu
{
	static const char* healthbar_style[]{
		"None",
		"Left Side",
		"Bottom",
	};
	static const char* healthbar_color_style[]{
	"Defualt",
	"Gradient",
	};
	static const char* healthbar_color[]{
"Defualt",
"Custom",
	};
	static const char* npc_healthbar_color_style[]{
"Defualt",
"Gradient",
	};
	static const char* chams_type[]{
"Glow",
"Xray",
	};
	static const char* npc_healthbar_color[]{
"Defualt",
"Custom",
	};
	static const char* npc_healthbar_style[]{
		"None",
		"Left Side",
		"Bottom",
	};
	static const char* building_grade[]{
		"Twig",
		"Wood",
		"Stone",
		"Metal",
		"HQM",
	};
	static const char* npc_box_style[]{
		"None",
		"Default",
		"Cornered",
	};
	static const char* box_style[]{
		"None",
		"Default",
		"Cornered",
		"3D Box",
	};
	static const char* anti_aim_yaw[]{
		"None",
		"Backwards",
		"Backwards (down)",
		"Backwards (up)",
		"Left",
		"Left (down)",
		"Left (up)",
		"Right",
		"Right (down)",
		"Right (up)",
		"Jitter",
		"Jitter (down)",
		"Jitter (up)",
		"Spin",
		"Spin (down)",
		"Spin (up)",
		"Random",
	};
	static const char* fake_lag_type[]{
		"Basic",
		"Double Tap",
	};
	static const char* target_tracer_pos[]{
		"Default",
		"Middle",
	};
	static const char* tracer_pos[]{
		"Default",
		"Middle",
	};
	static const char* modelstate_pos[]{
		"Default",
		"On Ladder",
		"On Ground",
		"Ducked",
		"Sleeping",
	};
	static const char* autoshoot_type[]{
		"Silent",
		"Default",
	};
	static const char* desync_autoshoot_type[]{
		"Always",
		"Desync",
	};
	static const char* timeshoot_type[]{
		"Silent",
		"Default",
	};
	static const char* ignore[]{
		"Ignore NPC",
		"Ignore Teammate",
		"Ignore Sleeping",
	};
	static const char* hitmaterial[]{
	"Default",
	"Glass",
	"Water",
	"Wood",
	"Metal",
	"Sand",
	"Grass",
	"Rock",
	"Concrete",
	"Forest",
	"Cloth",
	"Generic",
	"Null",
	};
	static const char* hitsound_type[]{
    "NL",
	};
	static bool selected[3];
	static std::string previewValue1 = "";
	static int pTabs = 0;
	int pSubTabs = 0;
	int pSubTabs2 = 0;
	int pSubTabs3 = 0;
	int pSubTabs4 = 0;
	static int pSubTabs1 = 0;
	static int pWeapons = 0;
	static bool toggled;

	void Decoration()
	{
		ImGuiStyle style = ImGui::GetStyle();
		auto d = ImGui::GetWindowDrawList(); auto p = ImGui::GetWindowPos();
		d->AddRectFilled(p, ImVec2(p.x + menu_size.x, p.y + menu_size.y), ImColor(25, 25, 25), 18);//167
		d->AddRectFilled(ImVec2(p.x + 160, p.y), ImVec2(p.x + menu_size.x, p.y + menu_size.y), ImColor(25, 25, 25), 18);
		d->AddRectFilled(ImVec2(p.x + 160, p.y), ImVec2(p.x + 162, p.y + menu_size.y), ImColor(25, 26, 26), 18);
		d->AddRectFilled(ImVec2(p.x, p.y + menu_size.y - 62), ImVec2(p.x + 160, p.y + menu_size.y - 60), ImColor(25, 26, 26), 18);
		auto size = fName->CalcTextSizeA(20.f, FLT_MAX, NULL, xorstr_("SNUS"));
		d->AddText(fName, 20.f, ImVec2(p.x + 5 + ((160 - size.x) / 2), p.y + 15), ImColor(255, 255, 255), xorstr_("SNUS"));
		auto size1 = fName->CalcTextSizeA(20.f, FLT_MAX, NULL, xorstr_("Solution"));
		d->AddText(fName, 20.f, ImVec2(p.x + 5 + ((160 - size1.x) / 2), p.y + 35), ImColor(255, 255, 255), xorstr_("Solution"));
		//ImGui::AddCircleImageFilled(avatar, ImVec2(p.x + 42, p.y + menu_size.y - 32), 18, ImColor(255, 255, 255), 360);
		char name[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserNameA(name, &username_len);
		std::string winname = name;

	}

	void Tabs()
	{
		ImGui::SetCursorPos(ImVec2(0, 80));

		if (ImGui::Button2(("Combat"), ImVec2(160, 40)))
		{
			pTabs = 0;
		}

		ImGui::SetCursorPos(ImVec2(0, 120));
		if (ImGui::Button2(("Esp"), ImVec2(160, 40)))
		{
			pTabs = 1;
		}

		ImGui::SetCursorPos(ImVec2(0, 160));
		if (ImGui::Button2(("Visuals"), ImVec2(160, 40)))
		{
			pTabs = 2;
		}
		ImGui::SetCursorPos(ImVec2(0, 200));
		if (ImGui::Button2(("Misc"), ImVec2(160, 40)))
		{
			pTabs = 3;
		}

		ImGui::SetCursorPos(ImVec2(0, 240));
		if (ImGui::Button2(("Settings"), ImVec2(160, 40)))
		{
			pTabs = 4;
		}
	}

	void SubTabs()
	{
		ImGui::SetCursorPos(ImVec2(167, 5));
		if (pTabs == 0)
		{
			if (ImGui::Button2(xorstr_("Aimbot"), ImVec2(120, 25)))
			{
				pSubTabs = 0;
			}

			ImGui::SameLine(0, 20);
			if (ImGui::Button2(xorstr_("Weapons"), ImVec2(120, 25)))
			{
				pSubTabs = 1;
			}
		}
		if (pTabs == 1)
		{
			if (ImGui::Button2(xorstr_("Players"), ImVec2(120, 25)))
			{
				pSubTabs2 = 0;
			}
			ImGui::SameLine(0, 20);
			if (ImGui::Button2(xorstr_("Npc"), ImVec2(120, 25)))
			{
				pSubTabs2 = 1;
			}
		}
		if (pTabs == 2)
		{
			if (ImGui::Button2(xorstr_("Main"), ImVec2(120, 25)))
			{
				pSubTabs3 = 0;
			}
			ImGui::SameLine(0, 20);
			if (ImGui::Button2(xorstr_("World"), ImVec2(120, 25)))
			{
				pSubTabs3 = 1;
			}
		}
		if (pTabs == 3)
		{
			if (ImGui::Button2(xorstr_("Main"), ImVec2(120, 25)))
			{
				pSubTabs4 = 0;
			}
		}
		if (pTabs == 4)
		{
			//if (ImGui::SubTab("General", pSubTabs1 == 0, ImVec2(120, 35)))
			//    pSubTabs1 = 0;
			//ImGui::SameLine(0, 20);
			if (ImGui::Button2(xorstr_("Configs"), ImVec2(120, 25)))
			{
				pSubTabs1 = 0;
			}

			//ImGui::SameLine(0, 20);
			//if (ImGui::SubTab("Lua's", pSubTabs1 == 2, ImVec2(120, 35)))
			//    pSubTabs1 = 2;
		}
	}

	void combat()
	{
		if (pTabs == 0) {
			if (pSubTabs == 0) {

				MenuChild(xorstr_("Aimbot"), ImVec2(278, 420), true, 0);
				{
					Checkbox__(xorstr_("Perfect Silent"), &vars::combat::psilent);
					Checkbox__(xorstr_("Simple Aimbot"), &vars::combat::aimbot); ImGui::SameLine(); KeyBind(xorstr_("##Aiming Key"), vars::keys::aimkey, ImVec2(70, 18));
					if (vars::combat::aimbot) {
						Checkbox__(xorstr_("Smooth"), &vars::combat::smooth);
						if (vars::combat::smooth) {
							ImGui::SliderInt(xorstr_("Smooth Factor"), &vars::combat::smooth_factor, 1, 50, xorstr_("%.0f"));
						}
					}
					Checkbox__(xorstr_("Only Headshot"), &vars::combat::always_headshot);
					if (vars::combat::always_headshot) {
						vars::combat::bodyaim = false;
					}
					Checkbox__(xorstr_("Body Aim"), &vars::combat::bodyaim);
					if (vars::combat::bodyaim) {
						vars::combat::always_headshot = false;
					}
					KeyBind("##Target Lock Key", vars::keys::locktarget, ImVec2(50, 18));
					ImGui::SliderFloat(xorstr_("Fov Value"), &vars::combat::fov, 20.f, 2000.f, xorstr_("%.0f"));
					Checkbox__(xorstr_("Draw Fov"), &vars::combat::visualize_fov); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_(" ##Color"), vars::colors::fov_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Heli Aim"), &vars::combat::psilentheli);
					Checkbox__(xorstr_("Manipulator"), &vars::combat::manipulator); ImGui::SameLine(); KeyBind(xorstr_("##Manipulator Key"), vars::keys::manipulated_key, ImVec2(70, 18));
					if (vars::combat::manipulator) {
						Checkbox__(xorstr_("View All Sphere Angle"), &vars::combat::manipulate_angle); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("  ##Color"), (float*)&vars::colors::angle, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						Checkbox__(xorstr_("Eye Position Arrow Angle"), &vars::combat::manipulate_angle_arrow); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("   ##Color"), (float*)&vars::colors::angle_arrow, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					}
					Checkbox__(xorstr_("Auto Fire"), &vars::combat::autoshoot);
					if (vars::combat::autoshoot) {
						Retake::combo(xorstr_("Auto Fire Mode"), &vars::combat::autoshoot_type, autoshoot_type, IM_ARRAYSIZE(autoshoot_type));
						Retake::combo(xorstr_("Fire Type"), &vars::combat::desync_autoshoot_type, desync_autoshoot_type, IM_ARRAYSIZE(desync_autoshoot_type));
					}
					Checkbox__(xorstr_("Time Shot"), &vars::combat::instakill); ImGui::SameLine(); KeyBind(xorstr_("##Time Shot Key"), vars::keys::instakill, ImVec2(70, 18));
					if (vars::combat::instakill) {
						Retake::combo(xorstr_("Shot Type"), &vars::combat::instakill_type, timeshoot_type, IM_ARRAYSIZE(timeshoot_type));
					}
				}
				ImGui::EndChild();
				ImGui::SameLine(0, 20);
				MenuChild(xorstr_("Weapon  "), ImVec2(278, 420), true, 0);
				{
					Checkbox_(xorstr_("Bullet Teleport"), &vars::combat::bullet_tp);
					Checkbox__(xorstr_("Magic Heli"), &vars::combat::always_heli_rotor);
					Checkbox__(xorstr_("Long Neck"), &vars::misc::long_neck); ImGui::SameLine(); KeyBind(xorstr_("##Long Neck Key"), vars::keys::longneck, ImVec2(70, 18));
					Checkbox__(xorstr_("Desync"), &vars::combat::desync); ImGui::SameLine(); KeyBind(xorstr_("##Desync Key"), vars::keys::desync, ImVec2(70, 18));
					Checkbox__(xorstr_("Ricochet"), &vars::combat::tree_reflect);
					Checkbox__(xorstr_("Pierce Materials"), &vars::weapons::penetrate);
					Checkbox__(xorstr_("Visible Check"), &vars::combat::ignore_invisible);
					Checkbox__(xorstr_("Ignore NPC"), &vars::combat::ignore_npc);
					Checkbox__(xorstr_("Ignore Teammates"), &vars::combat::ignore_team);
					Checkbox__(xorstr_("Ignore Sleeping"), &vars::combat::ignore_sleepers);
				}
				ImGui::EndChild();
			}
			if (pSubTabs == 1) {

				MenuChild(xorstr_("Weapon"), ImVec2(278, 420), true, 0);
				{

					Checkbox__(xorstr_("Recoil Control"), &vars::weapons::no_recoil);
					if (vars::weapons::no_recoil) {
						ImGui::SliderFloat(xorstr_("Recoil"), &vars::weapons::recoil_control, 0.f, 100.f, xorstr_("%.0f"));
					}
					Checkbox__(xorstr_("Anti Spread"), &vars::weapons::no_spread);
					Checkbox__(xorstr_("Remove Sway"), &vars::weapons::no_sway);
					Checkbox__(xorstr_("Fast Bullets"), &vars::weapons::fast_bullets);
					//Checkbox__(xorstr_("Thick Bullets"), &vars::weapons::thick_bullet);
					Checkbox__(xorstr_("Thick Bullets"), &vars::weapons::thick_bullet);
					if (vars::weapons::thick_bullet) {
						ImGui::SliderFloat(xorstr_("Thick"), &vars::weapons::thickness, 0.1f, 1.1f);
					}
					Checkbox__(xorstr_("Automatic"), &vars::weapons::automatic);
					Checkbox__(xorstr_("Can Hold Items"), &vars::weapons::minicopter_aim);
					Checkbox__(xorstr_("Jump Shoot"), &vars::misc::can_attack);
					Checkbox__(xorstr_("Fake Distance"), &vars::weapons::spoof_hitdistance);
					if (vars::weapons::spoof_hitdistance) {
						ImGui::SliderFloat(xorstr_("Distance Value"), &vars::weapons::hitdistance, 0.f, 99999.f, xorstr_("%.0f"));
					}
				}
				ImGui::EndChild();
				ImGui::SameLine(0, 20);
				MenuChild(xorstr_("Weapon "), ImVec2(278, 420), true, 0);
				{
					Checkbox__(xorstr_("Instant Eoka"), &vars::weapons::eokatap);
					Checkbox__(xorstr_("Fast Bow"), &vars::weapons::fastbow);
					Checkbox__(xorstr_("Rapid Fire"), &vars::weapons::rapid_fire);
					Checkbox__(xorstr_("Auto Reload(maybe crash)"), &vars::combat::autoreload);
					Checkbox__(xorstr_("No Attack Animation"), &vars::weapons::remove_attack_anim);
					Checkbox__(xorstr_("Insta Charge Compound"), &vars::weapons::compound);
				}
				ImGui::EndChild();
			}
		}
	}

	void esp() {
		if (pTabs == 1) {
			if (pSubTabs2 == 0) {
				MenuChild("Players", ImVec2(278, 420), true, 0);
				{
					Retake::combo(xorstr_("Box Style"), &vars::players::boxstyle, box_style, IM_ARRAYSIZE(box_style));
					Retake::combo(xorstr_("Healthbar Style"), &vars::players::healthbarscolortyle, healthbar_color_style, IM_ARRAYSIZE(healthbar_color_style));
					Retake::combo(xorstr_("Healthbar Style Color"), &vars::players::healthbarscolor, healthbar_color, IM_ARRAYSIZE(healthbar_color));
					Checkbox__(xorstr_("Name"), &vars::players::name);
					Checkbox__(xorstr_("Distance"), &vars::players::distance);
					Checkbox__(xorstr_("Fill Box"), &vars::players::fillbox);
					Checkbox__(xorstr_("Health Bar"), &vars::players::healthbar);
					Checkbox__(xorstr_("Weapon"), &vars::players::weapon);
					Checkbox__(xorstr_("Skeleton"), &vars::players::skeleton);
					Checkbox__(xorstr_("Chams"), &vars::players::chams);
					if (vars::players::chams)
						Retake::combo(xorstr_("Chams Style"), &vars::players::chams_type, chams_type, IM_ARRAYSIZE(chams_type));
					Checkbox__(xorstr_("Target Tracers"), &vars::players::targetline);
					if (vars::players::targetline) {
						Retake::combo(xorstr_("Target Tracer Position "), &vars::players::targetline_pos, target_tracer_pos, IM_ARRAYSIZE(target_tracer_pos));
					}
					Checkbox__(xorstr_("Out Of Arrows"), &vars::players::oof_arrows);
		/*			Checkbox__(xorstr_("Target Player Belt"), &vars::players::belt);
					Checkbox__(xorstr_("Target Player Clothes"), &vars::players::clothes);*/
					Checkbox__(xorstr_("Ignore Sleepers"), &vars::players::sleeperignore);//size_name
					//ImGui::SliderFloat(xorstr_("Value"), &size_name, 0.f, 50.f, xorstr_("%.0f"));
				}

				ImGui::EndChild();
				ImGui::SameLine(0, 20);
				MenuChild("Npcs", ImVec2(278, 420), true, 0);
				{
					ImGui::ColorEdit4(xorstr_("Chams##Color"), (float*)&vars::colors::chams, ImGuiColorEditFlags_NoInputs); 
				
					ImGui::ColorEdit4(xorstr_("Skeleton Visible Color##Color"), vars::visible::skeleton_color, ImGuiColorEditFlags_NoInputs); ImGui::ColorEdit4(xorstr_("Skeleton InVisible Color##Color"), vars::invisible::skeleton_color, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Visible Color##Color"), vars::visible::box_color, ImGuiColorEditFlags_NoInputs); ImGui::ColorEdit4(xorstr_("InVisible Color##Color"), vars::invisible::box_color, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Teammate Color##Color"), vars::colors::team_color, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Sleepers##Color"), vars::colors::sleep_color, ImGuiColorEditFlags_NoInputs);
					if (vars::players::healthbarscolor == 1)
						ImGui::ColorEdit4(xorstr_("Custom Health Color##Color"), vars::colors::Player_custom_healthColor, ImGuiColorEditFlags_NoInputs);
					if (vars::players::healthbarscolortyle == 1) {
						ImGui::ColorEdit4(xorstr_("Gradient Two##Color"), vars::colors::gradient_2, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4(xorstr_("Gradient One##Color"), vars::colors::gradient_1, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					}
				}
				ImGui::EndChild();
			}
			if (pSubTabs2 == 1) {

				MenuChild("Npcs", ImVec2(278, 420), true, 0);
				{
					Retake::combo(xorstr_("Box Style "), &vars::npc::boxstyle, npc_box_style, IM_ARRAYSIZE(npc_box_style));
					Retake::combo(xorstr_("Healthbar Style"), &vars::npc::healthbarscolortyle, npc_healthbar_color_style, IM_ARRAYSIZE(npc_healthbar_color_style));
					Retake::combo(xorstr_("Healthbar Style Color"), &vars::npc::healthbarscolor, npc_healthbar_color, IM_ARRAYSIZE(npc_healthbar_color));
					Checkbox__(xorstr_("Name"), &vars::npc::name);
					Checkbox__(xorstr_("Health Bar"), &vars::npc::healthbar);
					Checkbox__(xorstr_("Distance"), &vars::npc::distance);
					Checkbox__(xorstr_("Fill Box "), &vars::npc::fillbox);
					Checkbox__(xorstr_("Skeleton "), &vars::npc::skeleton);
					Checkbox__(xorstr_("Weapon "), &vars::npc::weapon);

				}
				ImGui::EndChild();
				ImGui::SameLine(0, 20);
				MenuChild("Npcs Col", ImVec2(278, 420), true, 0);
				{
					ImGui::ColorEdit4(xorstr_("Box##Color"), vars::colors::npc_box_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Name##Color"), vars::colors::npc_name_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Skeleton##Color"), vars::colors::npc_skeleton_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit4(xorstr_("Weapon##Color"), vars::colors::npc_weapons_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					if (vars::npc::healthbarscolor == 1)
						ImGui::ColorEdit4(xorstr_("Custom Health Color##Color"), vars::colors::npc_custom_healthColor, ImGuiColorEditFlags_NoInputs);
					if (vars::npc::healthbarscolortyle == 1) {
						ImGui::ColorEdit4(xorstr_("Gradient Two##Color"), vars::colors::gradient_2, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						ImGui::ColorEdit4(xorstr_("Gradient One##Color"), vars::colors::gradient_1, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					}
				}
				ImGui::EndChild();
			}
		}
	}

	void visuals() {
		if (pTabs == 2) {
			if (pSubTabs3 == 0) {
				MenuChild(xorstr_("Main"), ImVec2(278, 420), true, 0);
				{
					ImGui::SliderFloat("Player Fov", &vars::misc::fov, 30.f, 120.f, "%.0f");
					Checkbox__(xorstr_("Zoom"), &vars::visuals::zoom); ImGui::SameLine(); KeyBind("##Zoom Key", vars::keys::zoom, ImVec2(70, 18));
					Checkbox__(xorstr_("Noclip Bar"), &vars::misc::flyhack_indicator); /*ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("##Color"), vars::colors::flyhack_color);*/
					Checkbox__(xorstr_("Reload Coldown"), &vars::misc::reload_coldown);
					Checkbox__(xorstr_("Desync Indicator"), &vars::combat::instakill_indicator);
					Checkbox__(xorstr_("Show Target Name"), &vars::visuals::target_name); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("            ##Color"), (float*)vars::colors::target_name_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Hit Logs"), &vars::misc::hit_logs);
					Checkbox__(xorstr_("Keybinds"), &vars::visuals::keybinds);
					Checkbox__(xorstr_("Side Indicator"), &vars::visuals::GameSense);
					Retake::combo(xorstr_("Hit Effect"), &vars::misc::hitmaterial, hitmaterial, IM_ARRAYSIZE(hitmaterial));
					Checkbox__(xorstr_("Bullet Tracers"), &vars::misc::bullet_tracers);
					Checkbox__(xorstr_("Hitmarker"), &vars::misc::hitmarker);
					Checkbox__(xorstr_("Movement Line"), &vars::misc::movement_line);
					Checkbox__(xorstr_("Vis. Predict"), &vars::combat::visualize_prediction);  ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("                 ##Color"), vars::colors::prediction_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Bright Ambient"), &vars::misc::bright_ambient); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("                  ##Color"), (float*)&vars::colors::ambient_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Local Bones"), &vars::misc::local_bones); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("                   ##Color"), (float*)&vars::colors::local_bones, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Custom Time"), &vars::misc::custom_time);
					if (vars::misc::custom_time) {
						ImGui::SliderFloat(xorstr_("Time"), &vars::misc::time, 0.f, 12.f, "%.0f");
					}
					Checkbox__(xorstr_("Hand Chams"), &vars::visuals::hand_chams);
					ImGui::SameLine();
					ImGui::ColorEdit4(xorstr_(""), (float*)&vars::colors::hand_chams, ImGuiColorEditFlags_NoInputs);
					if (vars::visuals::hand_chams)
						Retake::combo(xorstr_("Chams Style"), &vars::visuals::hand_chams_type, chams_type, IM_ARRAYSIZE(chams_type));
					ImGui::EndChild();
				}
				ImGui::SameLine(0, 20);
				MenuChild("Other", ImVec2(278, 420), true, 0);
				{
					Checkbox__(xorstr_("Cadicall Cross"), &vars::crosshair::cadicall); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("    ##Color"), vars::colors::cadicall_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Evil Cross"), &vars::crosshair::default); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_(" ##Color"), vars::colors::default_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Dot Cross"), &vars::crosshair::dot); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("##Color"), vars::colors::dot_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
					Checkbox__(xorstr_("Swastika Cross"), &vars::crosshair::swastika); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("  ##Color"), vars::colors::swaston_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						if (vars::crosshair::swastika) {
							ImGui::SliderFloat("Size ", &vars::crosshair::razmer, 1.f, 10.f, "%.0f");
							ImGui::SliderFloat("Speed", &vars::crosshair::speed, 0.f, 5.f, "%.0f");
						}
						Checkbox__(xorstr_("Custom Cross"), &vars::crosshair::custom); ImGui::SameLine(); ImGui::ColorEdit4(xorstr_("   ##Color"), vars::colors::custom_color, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						if (vars::crosshair::custom) {
							ImGui::SliderFloat(xorstr_("Gap"), &vars::crosshair::gap, 0.f, 50.f, "%.0f");
							ImGui::SliderFloat(xorstr_("Length"), &vars::crosshair::length, 0.f, 150.f, "%.0f");
						}
						Checkbox__(xorstr_("Night Stars"), &vars::misc::night_stars);
					if (vars::misc::night_stars) {
						ImGui::SliderFloat(xorstr_("Stars Amount"), &vars::misc::stars, 0.f, 40000.f, "%.0f");
					}
					Checkbox__(xorstr_("Mie Changer"), &vars::misc::mie_changer);
					if (vars::misc::mie_changer) {
						ImGui::SliderFloat(xorstr_("Mie Amount"), &vars::misc::mie, 1.f, 100.f, "%.0f");
					}
					Checkbox__(xorstr_("Rayleigh Changer"), &vars::misc::rayleigh_changer);
					if (vars::misc::rayleigh_changer) {
						ImGui::SliderFloat(xorstr_("Rayleigh Amount"), &vars::misc::rayleigh, 1.f, 100.f, "%.0f");
					}
					Checkbox__(xorstr_("Brightness Changer"), &vars::misc::brightness_changer);
					if (vars::misc::brightness_changer) {
						ImGui::SliderFloat(xorstr_("Brightness Amount"), &vars::misc::brightness, 1.f, 50.f, "%.0f");
					}
				}
				ImGui::EndChild();
			}
			if (pSubTabs3 == 1) {
				MenuChild(xorstr_("Main"), ImVec2(278, 420), true, 0);
				{
					if (ImGui::CollapsingHeader(xorstr_("Important"))) {
						Checkbox__(xorstr_("Raid Esp"), &vars::visuals::raid_esp);
						Checkbox__(xorstr_("Dropped Items"), &vars::visuals::other::dropped_items);
						Checkbox__(xorstr_("Hemp"), &vars::visuals::other::hemp);
						Checkbox__(xorstr_("Corpses"), &vars::visuals::other::corpse);
						Checkbox__(xorstr_("Bodybags"), &vars::visuals::other::bodybag);
						Checkbox__(xorstr_("Stashes"), &vars::visuals::other::stash);
						if (vars::visuals::other::corpse || vars::visuals::other::stash || vars::visuals::other::hemp || vars::visuals::other::dropped_items) {
							ImGui::SliderFloat(xorstr_("Important ESP Distance"), &vars::visuals::other::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(xorstr_("Show Distance    "), &vars::visuals::other::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr_("Ores"))) {
						Checkbox__(xorstr_("Ore Path"), &vars::ores::closest_ore);
						Checkbox__(xorstr_("Stone"), &vars::ores::stone);
						Checkbox__(xorstr_("Sulfur"), &vars::ores::sulfur);
						Checkbox__(xorstr_("Metal"), &vars::ores::metal);
						if (vars::ores::sulfur || vars::ores::stone || vars::ores::metal) {
							ImGui::SliderFloat(xorstr_("Ores ESP Distance"), &vars::ores::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(xorstr_("Show Collectables"), &vars::ores::show_collectables);
							Checkbox__(xorstr_("Show Distance"), &vars::ores::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr_("Crates"))) {
						Checkbox__(xorstr_("Chinook Crates"), &vars::visuals::crates::chinook);
						Checkbox__(xorstr_("Airdrops"), &vars::visuals::crates::supply);
						Checkbox__(xorstr_("Heli Box"), &vars::visuals::crates::heli);
						Checkbox__(xorstr_("Bradley Box"), &vars::visuals::crates::bradley);
						Checkbox__(xorstr_("Military Box"), &vars::visuals::crates::military);
						Checkbox__(xorstr_("Elite Box"), &vars::visuals::crates::elite);
						if (vars::visuals::crates::supply || vars::visuals::crates::bradley || vars::visuals::crates::heli || vars::visuals::crates::military || vars::visuals::crates::elite) {
							ImGui::SliderFloat(xorstr_("Crates ESP Distance"), &vars::visuals::crates::draw_distance, 5.f, 3000.f, "%.0f");
							Checkbox__(xorstr_("Show Distance "), &vars::visuals::crates::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr_("Animals"))) {
						Checkbox__(xorstr_("Bears"), &vars::visuals::animals::bear);
						Checkbox__(xorstr_("Boars"), &vars::visuals::animals::pig);
						Checkbox__(xorstr_("Wolfs"), &vars::visuals::animals::wolf);
						Checkbox__(xorstr_("Horses"), &vars::visuals::animals::deer);
						Checkbox__(xorstr_("Chickens"), &vars::visuals::animals::chicken);
						if (vars::visuals::animals::bear || vars::visuals::animals::pig || vars::visuals::animals::wolf || vars::visuals::animals::deer || vars::visuals::animals::chicken) {
							ImGui::SliderFloat("Animals ESP Distance", &vars::visuals::animals::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(xorstr_("Show Distance      "), &vars::visuals::animals::show_distance);
						}
					}

					ImGui::EndChild();
				}
				ImGui::SameLine(0, 20);
				MenuChild(xorstr_("Other"), ImVec2(278, 420), true, 0);
				{
					if (ImGui::CollapsingHeader(xorstr_("Vehicles"))) {
						Checkbox__(xorstr_("Patrol Heli"), &vars::visuals::patrol_heli);
						Checkbox__(xorstr_("Bradley APC"), &vars::visuals::bradley_apc);
						Checkbox__(xorstr_("Minicopters"), &vars::visuals::vehicles::minicopter);
						Checkbox__(xorstr_("Scrap Helis"), &vars::visuals::vehicles::scrapheli);
						Checkbox__(xorstr_("Boats"), &vars::visuals::vehicles::boat);
						Checkbox__(xorstr_("RHIB's"), &vars::visuals::vehicles::rhib);
						if (vars::visuals::vehicles::minicopter || vars::visuals::vehicles::scrapheli || vars::visuals::vehicles::boat || vars::visuals::vehicles::rhib) {
							ImGui::SliderFloat(xorstr_("Vehicles ESP Distance"), &vars::visuals::vehicles::draw_distance, 5.f, 3000.f, "%.0f");
							Checkbox__(xorstr_("Show Distance  "), &vars::visuals::vehicles::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr_("Traps"))) {
						Checkbox__(xorstr_("Auto Turrets"), &vars::visuals::turrets::auto_turret);
						Checkbox__(xorstr_("Flame Turrets"), &vars::visuals::turrets::flame_turret);
						Checkbox__(xorstr_("Shotgun Traps"), &vars::visuals::turrets::shotgun_turret);
						Checkbox__(xorstr_("SAM Sites"), &vars::visuals::turrets::sam_site);
						Checkbox__(xorstr_("Landmines"), &vars::visuals::turrets::landmine);
						Checkbox__(xorstr_("Beartraps"), &vars::visuals::turrets::bear_trap);
						if (vars::visuals::turrets::auto_turret || vars::visuals::turrets::flame_turret || vars::visuals::turrets::shotgun_turret || vars::visuals::turrets::landmine || vars::visuals::turrets::bear_trap) {
							ImGui::SliderFloat(xorstr_("Traps ESP Distance"), &vars::visuals::turrets::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(xorstr_("Show Distance   "), &vars::visuals::turrets::show_distance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr_("Base"))) {
						Checkbox__(xorstr_("Tool Cupboards"), &vars::visuals::base::tc);
						Checkbox__(xorstr_("Sleeping Bags"), &vars::visuals::base::sleeping_bag);
						Checkbox__(xorstr_("Beds"), &vars::visuals::base::bed);
						Checkbox__(xorstr_("Boxes"), &vars::visuals::base::boxes);
						if (vars::visuals::base::tc || vars::visuals::base::sleeping_bag || vars::visuals::base::bed || vars::visuals::base::boxes) {
							ImGui::SliderFloat(xorstr_("Base ESP Distance"), &vars::visuals::base::draw_distance, 5.f, 400.f, "%.0f");
							Checkbox__(xorstr_("Show Distance     "), &vars::visuals::base::show_distance);
						}
					}
				}
				ImGui::EndChild();
			}
		}
	}

	void misc() {
		if (pTabs == 3) {
			//if (pSubTabs == 3) {
			MenuChild("Main", ImVec2(278, 420), true, 0);
			{
				Checkbox__(xorstr_("Fake Admin"), &vars::misc::fakeadmin);
				Checkbox__(xorstr_("Fast Loot"), &vars::misc::fast_loot);
				Checkbox__(xorstr_("No Collision"), &vars::misc::walker);
				Retake::combo(xorstr_("Model State"), &vars::misc::modelstate, modelstate_pos, IM_ARRAYSIZE(modelstate_pos));
				Checkbox__(xorstr_("Omni-Sprint"), &vars::misc::omnidirectional_sprinting);
				Checkbox__(xorstr_("Interactive Debug"), &vars::misc::interactive_debug); ImGui::SameLine(); KeyBind(xorstr_("##Debug Key"), vars::keys::debugging, ImVec2(70, 18));
				Checkbox__(xorstr_("Hitsound"), &vars::misc::custom_hitsound);
				if (vars::misc::custom_hitsound)
					Retake::combo(xorstr_("Sound"), &vars::misc::hitsound_rejim, hitsound_type, IM_ARRAYSIZE(hitsound_type));
				Checkbox__(xorstr_("Suicide"), &vars::misc::mass_suicide);
				Checkbox__(xorstr_("Spiderman"), &vars::misc::spiderman);
				Checkbox__(xorstr_("Fly Auto Stopper"), &vars::misc::fly_auto_stopper);
				Checkbox__(xorstr_("No Fall Damage"), &vars::misc::no_fall);
				Checkbox__(xorstr_("Infinity Jump"), &vars::misc::inf_jump);
				Checkbox__(xorstr_("Fake Shots"), &vars::misc::weapon_spam); ImGui::SameLine(); KeyBind(xorstr_("##Shots Key"), vars::keys::weaponspam, ImVec2(70, 18));
			}
			ImGui::EndChild();
			ImGui::SameLine(0, 20);
			MenuChild("Other", ImVec2(278, 420), true, 0);
			{
				Checkbox__(xorstr_("Silent Melee"), &vars::combat::silent_melee);
				Checkbox__(xorstr_("Insta Revive"), &vars::misc::auto_revive);
				/*Checkbox_(xorstr_("Recycler Exploit"), &vars::misc::recycler);*/
				Checkbox__(xorstr_("Auto Pick Up"), &vars::misc::auto_pickup);
				//Checkbox_(xorstr_("Farm Assist"), &vars::misc::farm_assist);
				Checkbox__(xorstr_("Auto Healing"), &vars::misc::faster_healing);
				Checkbox__(xorstr_("Speed Hack"), &vars::misc::speedhack); ImGui::SameLine(); KeyBind(xorstr_("##Speed Hack Key"), vars::keys::speedkey, ImVec2(70, 18));
				Checkbox__(xorstr_("Anti-Aim"), &vars::misc::anti_aim);
				if (vars::misc::anti_aim) {
					Retake::combo(xorstr_("AA Yaw"), &vars::misc::anti_aim_yaw, anti_aim_yaw, IM_ARRAYSIZE(anti_aim_yaw));
					if (vars::misc::anti_aim_yaw == 13 || vars::misc::anti_aim_yaw == 14 || vars::misc::anti_aim_yaw == 15) {
						ImGui::SliderInt(xorstr_("Spin Speed"), &spin_speed, 1, 200, xorstr_("%.0f"));
					}
					if (vars::misc::anti_aim_yaw == 10 || vars::misc::anti_aim_yaw == 11 || vars::misc::anti_aim_yaw == 12) {
						ImGui::SliderInt(xorstr_("Jitter Speed"), &jitter_speed, 1, 100, xorstr_("%.0f"));
					}
					//Retake::checkbox(xorstr("Indicator"), &vars::misc::anti_aim_indicator);
				}
				Checkbox__(xorstr_("Auto Farm"), &vars::misc::auto_farm);
				if (vars::misc::auto_farm) {
					Checkbox__(xorstr_("Auto Farm Trees"), &vars::misc::auto_farm_tree);
					Checkbox__(xorstr_("Auto Farm Ores"), &vars::misc::auto_farm_ore);
					Checkbox__(xorstr_("Auto Farm Barrels"), &vars::misc::auto_farm_barrel);
				}
				Checkbox__(xorstr_("Farm Bot"), &vars::misc::farmbot);
				if (vars::misc::farmbot) {
					//Checkbox_(xorstr("Jump Farm Bot"), &vars::misc::jumpfarm);
					Checkbox__(xorstr_("Farm Bot Ores"), &vars::misc::farmbot_ore);
					Checkbox__(xorstr_("Farm Bot Barrels"), &vars::misc::farmbot_barrels);
				}
				/*Checkbox_(xorstr_("Bhop"), &vars::misc::bhop); ImGui::SameLine(); KeyBind(xorstr_("##Bhoping Key"), vars::keys::bhop, ImVec2(70, 18));*/
				Checkbox__(xorstr_("Auto Upgrade"), &vars::misc::auto_grade);
				if (vars::misc::auto_grade) {
					Retake::combo(xorstr_("Building Grade"), &vars::misc::grade_, building_grade, IM_ARRAYSIZE(building_grade));
				}
				/*Checkbox_(xorstr_("Door Spammer"), &vars::misc::annoyer);*/
				ImGui::EndChild();
			}
			//}
		}
	}

	std::string get_random_string(size_t length)
	{
		std::string str(("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"));
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(str.begin(), str.end(), generator);
		return str.substr(0, length);
	}

	static bool menu_added = false;

	struct Configs
	{
		std::string name;
		std::string fullname;
		bool loaded;
	};
	std::vector<Configs> configs;
	std::vector<Configs> luas;

	/*void settings()
	{
		if (pTabs == 4) {
			if (pSubTabs1 == 0)
			{
				MenuChild("Main", ImVec2(-1 - 5, 420), true, 0);
				{
					Discord* g_Discord1;
					ImGui::InputText("", vars::stuff::ConfigName, 0x100);
					if (ImGui::Button2(xorstr_("Save"), ImVec2(0, 0))) {
						config.Save();
						sh_save_cfg = true;
					}
					ImGui::SameLine();
					if (ImGui::Button2(xorstr_("Load"), ImVec2(0, 0))) {
						config.Load();
						sh_load_cfg = true;
					}
					if (ImGui::Button2(xorstr_("Open Folder"), ImVec2(0, 0))) {
						system(xorstr_("start C:\SNUS.solution"));
					}
					if (ImGui::Button(xorstr_("Discord Active Start"), ImVec2(0, 0))) {
						g_Discord1->Initialize();
						g_Discord1->Update();
					}
					if (ImGui::Button(xorstr_("Discord Active Stop"), ImVec2(0, 0))) {
						g_Discord1->Stop();
					}
					if (ImGui::Button2(xorstr_("Discord Server"), ImVec2(0, 0))) {
						system(xorstr_("start https://discord.gg/MTM9Qrv6rF"));
					}
					if (ImGui::Button2(xorstr_("Unload Cheat"), ImVec2(0, 0))) {
						vars::stuff::Panic = true;
					}
					static float color[4] = { 138 / 138.f, 41 / 168.f, 53 / 248.f, 1.f };
					if (ImGui::ColorEdit4("UI color", color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip))
					{
						accent_color[0] = color[0] * 138.f;
						accent_color[1] = color[1] * 168.f;
						accent_color[2] = color[2] * 248.f;
					}
				}

				ImGui::EndChild();
			}
		}
	}*/

	void Components()
	{
		ImGui::SetCursorPos(ImVec2(165, 45));
		ImGui::BeginGroup();
		{
			switch (pTabs)
			{
			case 0: combat();  break;
			case 1: esp();  break;
			case 2: visuals(); break;
			case 3: misc();  break;
			}
		}
		ImGui::EndGroup();
	}

	void DrawMenu()
	{
		auto& s = ImGui::GetStyle();
		s.FrameRounding = 0.f;
		s.FramePadding = ImVec2(2.5f, 1.5f);
		s.WindowBorderSize = 0;
		s.ScrollbarSize = 6.f;
		auto c = s.Colors;
		c[ImGuiCol_Border] = ImColor();
		c[ImGuiCol_ScrollbarBg] = ImColor(25, 25, 25);
		c[ImGuiCol_ScrollbarGrab] = ImColor(100, 100, 100);
		c[ImGuiCol_ScrollbarGrabHovered] = ImColor(accent_color[0], accent_color[1], accent_color[2], 200);
		c[ImGuiCol_ScrollbarGrabActive] = ImColor(accent_color[0], accent_color[1],accent_color[2]);
		ImGui::SetNextWindowSize(menu_size);
		ImVec2 menu_pos;
		ImDrawList* drawList_test;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin(xorstr_("Menu"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings);
		{
			auto p = ImGui::GetWindowPos();
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			drawList_test = drawList;
			const ImVec2 origin(ImGui::GetCursorScreenPos());
			menu_pos = ImGui::GetWindowPos();
			//if (showRectangles)
			//	drawList->AddRectFilled(origin + shadowSettings.rectPos, origin + shadowSettings.rectPos + shadowSettings.rectSize, ImColor(accent_color));
		//	drawList->AddRect(origin, origin + shadowSettings.shadowSize, ImColor(255, 0, 0, 255));
			Decoration();
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 5));
			ImGui::PushFont(fMain);
			Tabs();
			SubTabs();
			Components();
			ImGui::PopFont();
			ImGui::PopStyleVar();
		}
		ImGui::End();
		//drawRectangleShadowVerticesAdaptive(drawList_test, menu_pos, menu_size, ImColor(accent_color[0], accent_color[1], accent_color[2], accent_color[3]), ImVec2(0, 0), shadowSettings);
		ImGui::PopStyleVar();
	}
}


