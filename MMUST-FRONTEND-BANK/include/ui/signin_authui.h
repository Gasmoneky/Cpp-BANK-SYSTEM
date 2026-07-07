#pragma once
#ifndef AUTH_H
#define AUTH_H

namespace ui {
    void render_auth_signinpage();
    void render_left_panel(float width, float height);
    void render_right_panel(float width, float height);

    extern char emailBuffer[256];
    extern char passwordBuffer[256];
    extern bool isSignUpMode;


    extern bool showLoginWindow;
    extern bool showDashboard;

}
#endif
