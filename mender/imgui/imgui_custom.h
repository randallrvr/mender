

#include "imgui.h"

namespace ImGui
{

IMGUI_API bool SliderFloatCustom(const char *label, float *v, float v_min, float v_max,
								 const char *display_format = "%.3f",
								 float power = 1.0f);     // adjust display_format to decorate the value with a prefix or a suffix. Use power!=1.0 for logarithmic sliders

IMGUI_API void LabelValue(const char* prefix, bool b);
IMGUI_API void LabelValue(const char* prefix, int v);
IMGUI_API void LabelValue(const char* prefix, unsigned int v);
IMGUI_API void LabelValue(const char* prefix, float v, const char* float_format = NULL);

IMGUI_API bool DragMat33(const char* label, float v[9],  float v_speed = 1.f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.f);
IMGUI_API bool DragMat44(const char* label, float v[16], float v_speed = 1.f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.f);

};