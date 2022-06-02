#include "Dissasembler.h"
#include "..\PCSPCommon.h"
#include "..\Memory.h"
#include "..\MemoryMap.h"
#include "..\Memory.h"
#include "..\allegrex\Decoder.h"

void debug::Dissasembler::draw() {
    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Dissasembler", &m_show)) {
        ImGui::End();
        return;
    }
    u32 pc = 0x08900050;//TEMP value based on minifire demo
    ImGui::Checkbox("Follow PC", &m_followPC);
    ImGui::BeginChild("##ScrollingRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    ImGuiListClipper clipper;
    clipper.Begin(32*1024 *1024/4);
    u32 baseaddr = MemoryMap::START_RAM;
    while (clipper.Step()) {
        for (int x= clipper.DisplayStart; x< clipper.DisplayEnd; x++) {
            u32 addr = baseaddr + x * 4;
            u32 opcode = Memory::read32(addr);
            Allegrex::Instruction* insn = Allegrex::instruction(opcode);
            std::string disasm = insn->disasm(addr, opcode);
            ImGui::Text("0x%08X:[0x%08X] %s", addr, opcode,disasm.c_str());
        }
        
    }
    if (m_followPC) {
        uint64_t pctopx = (pc & 0x9fffff)/ 4;
        uint64_t scroll_to_px = pctopx * static_cast<uint64_t>(ImGui::GetTextLineHeightWithSpacing());
        ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_to_px, 0.5f);
    }
    ImGui::EndChild();//end scrolling region

    ImGui::End();
}
