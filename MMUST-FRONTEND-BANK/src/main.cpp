#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "ui/signin_authui.h"

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // 1. Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    // GL 3.3 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Create Window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MMUST Bank System", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync (prevents high CPU/GPU cooking)

    // 3. Setup Dear ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // --- ADVANCED TYPOGRAPHY CONFIGURATION ---
    const char* fontPath = "assets/fonts/ElmsSans-VariableFont_wght.ttf";
    ImFont* elmsSansFont = io.Fonts->AddFontFromFileTTF(fontPath, 28.0f);

    // Safety Fallback check if execution binary path shifts or files are missing
    if (elmsSansFont == nullptr) {
        std::cerr << "[WARNING] Custom typography asset not found at: " << fontPath
                  << " | Falling back to upscaled default layout settings." << std::endl;

        ImFontConfig config;
        config.SizePixels = 26.0f;
        io.Fonts->AddFontDefault(&config);
    }

    // 4. Global Styling Tweaks
    ImGui::StyleColorsDark();
    auto& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 6.0f;       // Clean smooth fields matching your design mockup
    style.ChildRounding = 12.0f;      // Smooth rounding for inner card panels
    style.WindowPadding = ImVec2(20.0f, 20.0f);

    // 5. Setup Platform/Renderer Backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 6. Main Application Loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- PROJECT CONTENT STARTS HERE ---

        ui::render_auth_signinpage();

        // --- PROJECT CONTENT ENDS HERE ---

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.08f, 0.08f, 0.09f, 1.0f); // Sleek charcoal background canvas
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 7. Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
