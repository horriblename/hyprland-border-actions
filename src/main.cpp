#include <hyprland/src/managers/KeybindManager.hpp>
#define WLR_USE_UNSTABLE

#include "globals.hpp"

#include <hyprland/src/Window.hpp>
#include <hyprland/src/Compositor.hpp>

#include <unistd.h>
#include <thread>

// Methods
inline CFunctionHook* g_pResizeWithBorderHook = nullptr;
typedef void (*origResizeWithBorder)(void*, wlr_pointer_button_event*);

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

void hkMouseBindDummy(void* thisptr, std::string) {}

void hkResizeWithBorder(void* thisptr, wlr_pointer_button_event* e) {
    switch (e->button) {
        case 273: // right click
            g_pKeybindManager->m_mDispatchers["mouse"]((e->state == WLR_BUTTON_PRESSED ? "1" : "0") + std::string("movewindow"));
            break;
        case 274: // middle click
            if (e->state == WLR_BUTTON_PRESSED)
                g_pKeybindManager->m_mDispatchers["killactive"]("");
            break;
        default: (*(origResizeWithBorder)g_pResizeWithBorderHook->m_pOriginal)(thisptr, e); break;
    }
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // Hook a public member
    g_pResizeWithBorderHook = HyprlandAPI::createFunctionHook(PHANDLE, (void*)&CKeybindManager::resizeWithBorder, (void*)&hkResizeWithBorder);
    // Hook a private member
    static const auto METHODS = HyprlandAPI::findFunctionsByName(PHANDLE, "mouse");

    // Enable our hooks
    g_pResizeWithBorderHook->hook();

    HyprlandAPI::reloadConfig();

    return {"border-actions", "Make borders great again", "horriblename", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    HyprlandAPI::invokeHyprctlCommand("seterror", "disable");
}
