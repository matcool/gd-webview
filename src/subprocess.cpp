#include <include/cef_app.h>

int main(int argc, char** argv) {
    CefMainArgs args;
    if (int value = CefExecuteProcess(args, nullptr, nullptr); value >= 0) {
        return value;
    }

    CefSettings settings;
    settings.windowless_rendering_enabled = true;
    settings.no_sandbox = true;

    if (!CefInitialize(args, settings, nullptr, nullptr)) {
        return 1;
    }
}