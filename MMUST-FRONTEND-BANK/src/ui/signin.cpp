#include "ui/signin_authui.h"
#include <imgui.h>
#include <iostream>
#include <cstring>

namespace ui {

// Allocate the global state memory blocks declared in the header
char emailBuffer[256] = "";
char passwordBuffer[256] = "";
bool isSignUpMode = false;
bool showLoginWindow = true;
bool showDashboard = false;

void render_auth_signinpage() {
    if (!showLoginWindow) return;

    // 1. Force the master window canvas to cover the whole screen
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoBringToFrontOnFocus;

    // Soft aesthetic background color matching your design inspiration
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.96f, 0.89f, 0.85f, 1.0f));
    ImGui::Begin("AuthMasterCanvas", nullptr, flags);

    // Calculate dynamic half-widths for our split panels
    float fullWidth = viewport->Size.x;
    float fullHeight = viewport->Size.y;
    float panelWidth = fullWidth * 0.5f;

    // 2. Render the structural left side
    render_left_panel(panelWidth, fullHeight);

    ImGui::SameLine(0.0f, 0.0f); // Lock panels perfectly flush against each other

    // 3. Render the structural right side
    render_right_panel(panelWidth, fullHeight);

    ImGui::End();
    ImGui::PopStyleColor(); // Clean up layout background style stack
}

void render_left_panel(float width, float height) {
    // Begin an invisible child group for the left pane layout
    ImGui::BeginChild("LeftPane", ImVec2(width, height), false, ImGuiWindowFlags_NoScrollbar);

    // Add vertical padding to push content down beautifully
    ImGui::SetCursorPosY(height * 0.35f);
    ImGui::Indent(width * 0.15f); // Push text away from the absolute left border boundary

    // Branding / Aesthetic typography display
    ImGui::TextColored(ImVec4(0.1f, 0.1f, 0.1f, 1.0f), "10 Years of Excellence In Systems");
    ImGui::Spacing();

    ImGui::Text("Net Banking");
    ImGui::Separator();
    ImGui::Spacing();
    if (ImGui::Button("Sign-up", ImVec2(120, 35))) {
        // Aesthetic anchor step
    }

    ImGui::Unindent(width * 0.15f);
    ImGui::EndChild();
}

void render_right_panel(float width, float height) {
    ImGui::BeginChild("RightPane", ImVec2(width, height), false, ImGuiWindowFlags_NoScrollbar);

    // Dynamic centering math matrices to place the input card cleanly in the middle of the right side
    float cardWidth = 400.0f;
    float cardHeight = 360.0f; // Increased slightly to comfortably fit labels and fields

    ImGui::SetCursorPosX((width - cardWidth) * 0.5f);
    ImGui::SetCursorPosY((height - cardHeight) * 0.5f);

    // Style Stack: Elevated white login panel card element
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Bright White card fill
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);                  // Rounded corners styling
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25.0f, 25.0f));   // Inner elements padding layout

    // Force all text inside the white card to be dark charcoal so it's fully visible!
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.12f, 0.12f, 0.14f, 1.0f));

    ImGui::BeginChild("LoginCard", ImVec2(cardWidth, cardHeight), true, ImGuiWindowFlags_None);

    // Card Header Title block
    ImGui::Text("Login Now");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Field 1: Explicit Email Label and Input
    ImGui::Text("Institutional Email Address");
    ImGui::Spacing();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f); // Give fields clean rounded edges
    ImGui::InputText("##emailField", emailBuffer, sizeof(emailBuffer));
    ImGui::PopStyleVar();
    ImGui::Spacing();

    // Field 2: Explicit Password Label and Input
    ImGui::Text("Secure Gateway Password");
    ImGui::Spacing();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::InputText("##passField", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password);
    ImGui::PopStyleVar();
    ImGui::Spacing();
    ImGui::Spacing();

    // Style modifications for action buttons so they stand out boldly
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.12f, 0.12f, 0.14f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.22f, 0.22f, 0.26f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

    if (ImGui::Button("Login Now", ImVec2(130, 40))) {
        if (strlen(emailBuffer) > 0 && strlen(passwordBuffer) > 0) {
            std::cout << "[NETWAY] Payload dispatched to core secure container node..." << std::endl;

            std::memset(passwordBuffer, 0, sizeof(passwordBuffer));
            std::memset(emailBuffer, 0, sizeof(emailBuffer));

            ui::showLoginWindow = false;
            ui::showDashboard = true;
        }
    }
    ImGui::PopStyleColor(3);

    ImGui::SameLine();

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
    if (ImGui::Selectable("Forgot Password", false, 0, ImVec2(0, 25))) {
        // Redirection state placeholder hook
    }

    ImGui::EndChild(); // End "LoginCard"

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor();

    ImGui::EndChild();
}

}
