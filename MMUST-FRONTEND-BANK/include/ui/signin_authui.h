#pragma once
namespace ui {
    void render_auth_siginpage();
    void render_left_panel(float with, float height);
    void render_right_panel(float with, float height);

    inline char emailBuffer[256];
    inline char passwordBuffer[256];
    inline bool isSignUpMode = false;
    }
