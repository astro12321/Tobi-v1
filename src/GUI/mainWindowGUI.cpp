#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


//Should implement MVC model here !

std::vector<std::string> items;


void addSelectable(std::string item) {
	items.push_back(item);
}


void showMainWindow() {
	if (!items.empty())
		for (std::string item : items){
	    	ImGui::Selectable(item.c_str(), 1);
		}
}
