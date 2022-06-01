#include "Dissasembler.h"
#include "..\PCSPCommon.h"
#include "..\Memory.h"
#include "..\MemoryMap.h"

void debug::Dissasembler::draw() {
    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Dissasembler", &m_show)) {
        ImGui::End();
        return;
    }

    ImGui::BeginChild("##ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    ImGuiListClipper clipper;
    clipper.Begin(32*1024 *1024/4);
    u32 baseaddr = MemoryMap::START_RAM;
    while (clipper.Step()) {
        for (int x= clipper.DisplayStart; x< clipper.DisplayEnd; x++) {
            u32 addr = baseaddr + x * 4;
            ImGui::Text(" %8.8x", addr);
        }
        
    }
    ImGui::EndChild();//end scrolling region

    ImGui::End();
}
