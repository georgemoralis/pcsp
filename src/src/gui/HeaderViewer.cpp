#include "..\PCSPCommon.h"
#include "HeaderViewer.h"
#include "imgui.h"

namespace debug {
void HeaderViewer::draw() 
{
    ImGui::SetNextWindowPos(ImVec2(324, 155), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(250, 314), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Header Viewer", &m_show)) {
        ImGui::End();
        return;
    }
    if (ImGui::BeginTabBar("##header_tabs", ImGuiTabBarFlags_None)) {
        if (!pbpheader.empty()) {
            if (ImGui::BeginTabItem("PBP")) {
                ImGui::BeginChild("##ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::Text(pbpheader.c_str());
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
        }
        if (!psfheader.empty()) {
            if (ImGui::BeginTabItem("PSF")) {
                ImGui::BeginChild("##ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::Text(psfheader.c_str());
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
void HeaderViewer::setPbpHeader(std::string header) { pbpheader = header; }
void HeaderViewer::setPSFHeader(std::string header) { psfheader = header; }
}  // namespace debug
