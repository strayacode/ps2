#include "otterstation-imgui/debugger/iop.h"
#include "core/iop/disassembler.h"

void IOPDebugger::RegistersWindow(IOPCore& iop_core) {
    ImGui::Begin("IOP Registers");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("IOPTabs", tab_bar_flags)) {
        if (ImGui::BeginTabItem("GPR")) {
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

            for (int i = 0; i < 32; i++) {
                ImGui::Text("%s", IOPGetRegisterName(i).c_str());
                ImGui::SameLine(90);
                ImGui::Text("%08x", iop_core.GetReg(i));
            }

            ImGui::Text("pc");
            ImGui::SameLine(90);
            ImGui::Text("%08x", iop_core.regs.pc);

            ImGui::Text("npc");
            ImGui::SameLine(90);
            ImGui::Text("%08x", iop_core.regs.next_pc);

            ImGui::PopFont();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("COP0")) {
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

            for (int i = 0; i < 32; i++) {
                if (IOPCOP0GetRegisterName(i).compare("") == 0) {
                    continue;
                }

                ImGui::Text("%s", IOPCOP0GetRegisterName(i).c_str());
                ImGui::SameLine(90);
                ImGui::Text("%08x", iop_core.cop0.gpr[i]);
            }

            ImGui::PopFont();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void IOPDebugger::DisassemblyWindow(Core& core) {
    ImGui::Begin("IOP Disassembly");
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

    if (core.GetState() != CoreState::Idle) {
        u32 pc = core.system.iop_core->regs.pc;
        u32 addr = pc - ((disassembly_size - 1) / 2) * 4;

        if (core.system.memory.ValidIOPCodeRegion(addr)) {
            for (int i = 0; i < disassembly_size; i++) {
                CPUInstruction inst = core.system.iop_core->ReadWord(addr);

                if (addr == pc) {
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "%08x: %08x %s", addr, inst.data, IOPDisassembleInstruction(inst, addr).c_str());
                } else {
                    ImGui::Text("%08x: %08x %s", addr, inst.data, IOPDisassembleInstruction(inst, addr).c_str());
                }

                addr += 4;
            }
        } else {
            // ignore invalid addresses
            ImGui::Text("");
        }
    }

    ImGui::PopFont();
    ImGui::End();
}