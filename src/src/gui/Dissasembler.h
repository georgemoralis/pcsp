#pragma once
#include "imgui.h"
#include "imgui_memory_editor.h"

namespace debug {
    class Dissasembler {
        public:
          void draw();
          bool m_show = true;
};
}  // namespace debug
