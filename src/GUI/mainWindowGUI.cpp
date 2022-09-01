#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


void showMainWindow()
{
	const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
    static int item_current_idx = 0; // Here we store our selection data as an index.

	ImGui::Text("PacketCapture");
    if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, -FLT_MIN - 30))) //5 * ImGui::GetTextLineHeightWithSpacing()
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
        	const bool is_selected = (item_current_idx == n);
        	if (ImGui::Selectable(items[n], is_selected))
        	    item_current_idx = n;

        	// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        	if (is_selected)
        	    ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
	}

}
