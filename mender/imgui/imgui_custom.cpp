

#include "imgui_custom.h"

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include <ctype.h>      // toupper, isprint
#include <math.h>       // sqrtf, fabsf, fmodf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>      // vsnprintf, sscanf, printf
#include <new>          // new (ptr)
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>     // intptr_t
#else
#include <stdint.h>     // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4127) // condition expression is constant
#pragma warning (disable: 4505) // unreferenced local function has been removed (stb stuff)
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif

// Clang warnings with -Weverything
#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"         // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wfloat-equal"            // warning : comparing floating point with == or != is unsafe   // storing and comparing against same constants ok.
#pragma clang diagnostic ignored "-Wformat-nonliteral"      // warning : format string is not a string literal              // passing non-literal to vsnformat(). yes, user passing incorrect format strings can crash the code.
#pragma clang diagnostic ignored "-Wexit-time-destructors"  // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wglobal-constructors"    // warning : declaration requires a global destructor           // similar to above, not sure what the exact difference it.
#pragma clang diagnostic ignored "-Wsign-conversion"        // warning : implicit conversion changes signedness             //
#pragma clang diagnostic ignored "-Wmissing-noreturn"       // warning : function xx could be declared with attribute 'noreturn' warning    // GetDefaultFontData() asserts which some implementation makes it never return.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"// warning : 'xx' is deprecated: The POSIX name for this item.. // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast" // warning : cast to 'void *' from smaller integer type 'int'
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-function"          // warning: 'xxxx' defined but not used
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"      // warning: cast to pointer from integer of different size
#endif

#include <iostream>

using namespace std;


// ImGuiStyle& style = imgui::GetStyle();
// ImVec2 winMax = imgui::GetContentRegionMax();
// float w = winMax.x-style.WindowPadding.x;		// Useful column width



bool ImGui::SliderFloatCustom(const char *label, float *v, float v_min, float v_max, const char *display_format, float power)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiState& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = ImGui::CalcItemWidth();

	ImVec2 winMax = ImGui::GetContentRegionMax();

	float x1 = window->Pos.x;
	float x2 = window->Pos.x + winMax.x;
	if (!window->DC.GroupStack.empty())
		x1 += window->DC.ColumnsStartX;

	float dStartX = window->DC.CursorPos.x - window->Pos.x;

	float dx = x2-x1-dStartX;

	static const int SLIDER_HEIGHT = 20;

//	cerr << window->DC.CursorPos.x << endl;
//	cerr << dStartX << endl;

//	const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y + SLIDER_HEIGHT + style.FramePadding.y*2.0f));
	const ImRect bb(window->DC.CursorPos, ImVec2(window->DC.CursorPos.x+dx, window->DC.CursorPos.y + SLIDER_HEIGHT + style.FramePadding.y*2.0f));
//	ItemSize(ImVec2(0.0f, bb.GetSize().y)); // NB: we don't provide our width so that it doesn't get feed back into AutoFit

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, SLIDER_HEIGHT) + style.FramePadding*2.0f);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max);

	// NB- we don't call ItemSize() yet because we may turn into a text edit box below
	if (!ItemAdd(total_bb, &id))
	{
		ItemSize(bb, style.FramePadding.y);
		return false;
	}

	const bool hovered = IsHovered(bb, id);
	if (hovered)
		g.HoveredId = id;

	if (!display_format)
		display_format = "%.3f";
	int decimal_precision = ParseFormatPrecision(display_format, 3);

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	bool start_text_input = false;
	const bool tab_focus_requested = FocusableItemRegister(window, g.ActiveId == id);
	if (tab_focus_requested || (hovered && g.IO.MouseClicked[0]))
	{
		SetActiveID(id, window);
		FocusWindow(window);

		if (tab_focus_requested || g.IO.KeyCtrl)
		{
			start_text_input = true;
			g.ScalarAsInputTextId = 0;
		}
	}
	if (start_text_input || (g.ActiveId == id && g.ScalarAsInputTextId == id))
		return InputScalarAsWidgetReplacement(bb, label, ImGuiDataType_Float, v, id, decimal_precision);

	ItemSize(total_bb, style.FramePadding.y);

	// Actual slider behavior + render grab
	const bool value_changed = SliderBehavior(bb, id, v, v_min, v_max, power, decimal_precision, true);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), display_format, *v);

	ImVec2 end = bb.Max;
	end.x -= style.ItemInnerSpacing.x;
	// Value text
	RenderTextClipped(frame_bb.Min, end, value_buf, value_buf_end, NULL, ImGuiAlign_Right|ImGuiAlign_VCenter);


	if (label_size.x > 0.0f)
	{
		ImVec2 minPos = ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x, frame_bb.Min.y);
		//label text
//		RenderText(pos, label);
		RenderTextClipped(minPos, frame_bb.Max, label, NULL, NULL, ImGuiAlign_VCenter);
	}
	return value_changed;

	return false;
}


void ImGui::LabelValue(const char* label, bool b)
{
	ImGui::Text("%s:", label);

//	RenderTextClipped()

//	ImGui::Text("%s: %s", prefix, (b ? "true" : "false"));

}

void ImGui::LabelValue(const char* prefix, int v)
{
	ImGui::Text("%s: %d", prefix, v);
}

void ImGui::LabelValue(const char* prefix, unsigned int v)
{
	ImGui::Text("%s: %d", prefix, v);
}

void ImGui::LabelValue(const char* prefix, float v, const char* float_format)
{
	if (float_format)
	{
		char fmt[64];
		ImFormatString(fmt, IM_ARRAYSIZE(fmt), "%%s: %s", float_format);
		ImGui::Text(fmt, prefix, v);
	}
	else
	{
		ImGui::Text("%s: %.3f", prefix, v);
	}
}

bool ImGui::DragMat33(const char* label, float v[9], float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	bool result = false;
	if(ImGui::CollapsingHeader(label))
	{
		ImGui::Indent();

		char label_0_2[64];
		char label_3_5[64];
		char label_6_8[64];
		ImFormatString(label_0_2, 64, "%s 0-2", label);
		ImFormatString(label_3_5, 64, "%s 3-5", label);
		ImFormatString(label_6_8, 64, "%s 6-8", label);

		result = DragFloatN(label_0_2,  &v[ 0], 3, v_speed, v_min, v_max, display_format, power) || result;
		result = DragFloatN(label_3_5,  &v[ 3], 3, v_speed, v_min, v_max, display_format, power) || result;
		result = DragFloatN(label_6_8,  &v[ 6], 3, v_speed, v_min, v_max, display_format, power) || result;

		ImGui::Unindent();
	}
	return result;
}


bool ImGui::DragMat44(const char* label, float v[16], float v_speed, float v_min, float v_max, const char* display_format, float power)
{
	bool result = false;
	if(ImGui::CollapsingHeader(label))
	{
		ImGui::Indent();

		char label_0_3[64];
		char label_4_7[64];
		char label_8_11[64];
		char label_12_15[64];
		ImFormatString(label_0_3,   64, "%s 0-3", label);
		ImFormatString(label_4_7,   64, "%s 4-7", label);
		ImFormatString(label_8_11,  64, "%s 8-11", label);
		ImFormatString(label_12_15, 64, "%s 12-15", label);

		result = DragFloatN(label_0_3,   &v[ 0], 4, v_speed, v_min, v_max, display_format, power) || result;
		result = DragFloatN(label_4_7,   &v[ 4], 4, v_speed, v_min, v_max, display_format, power) || result;
		result = DragFloatN(label_8_11,  &v[ 8], 4, v_speed, v_min, v_max, display_format, power) || result;
		result = DragFloatN(label_12_15, &v[12], 4, v_speed, v_min, v_max, display_format, power) || result;

		ImGui::Unindent();
	}
	return result;
}
