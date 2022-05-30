#pragma once
#include "imgui.h"
#include "imgui_memory_editor.h"

namespace debug {
	namespace memoryViewer {
		static void debug_window_memory()
		{
            static MemoryEditor mem_edit;
            mem_edit.Cols = 24;
            mem_edit.OptShowDataPreview = true;
            ImGui::SetNextWindowPos(ImVec2(467, 318), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(810, 399), ImGuiCond_FirstUseEver);

			ImGui::Begin("Memory Editor");

            if (ImGui::BeginTabBar("##memory_tabs", ImGuiTabBarFlags_None)) {
                if (ImGui::BeginTabItem("Ram")) {
                    mem_edit.DrawContents(Memory::mainMemory, MemoryMap::SIZE_RAM,MemoryMap::START_RAM);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("ScratchPad")) {
                    mem_edit.DrawContents(Memory::scratchPad, MemoryMap::SIZE_SCRATCHPAD, MemoryMap::START_SCRATCHPAD);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("VideoRam")) {
                    mem_edit.DrawContents(Memory::videoMemory, MemoryMap::SIZE_VRAM, MemoryMap::START_VRAM);
                    ImGui::EndTabItem();
                }
               ImGui::EndTabBar();
            }

            ImGui::End();

		}
	}
}
