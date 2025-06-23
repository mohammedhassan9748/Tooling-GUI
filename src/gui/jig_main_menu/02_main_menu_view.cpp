#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include "AppController.hpp"
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "03_request_gui.hpp"
#include "04_send_button.hpp"
#include "05_req_output_terminal.hpp"
#include "06_jig_wifi.hpp"
#include "07_debug_output_terminal.hpp"

#include "03_jig_id.hpp"

static HWND hGroupBoxRequest = NULL;
static HFONT hMainMenuFont = NULL;
static HFONT hLabelsFont = NULL;
static HWND hChoosenJigLabel = NULL;


void create_request_combo_box(HWND hwnd)
{
    // Example: Create a simple static control as a placeholder for the main menu
    // Create a font for the controls
    hMainMenuFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                       DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

    // Create the group box
    hGroupBoxRequest = CreateWindow(L"BUTTON", L"Request",
                             WS_VISIBLE | WS_CHILD | BS_GROUPBOX | ES_CENTER,
                             LOC_X_GROUP_BOX_REQUEST,LOC_Y_GROUP_BOX_REQUEST,
                             WIDTH_GROUP_BOX_REQUEST, HEIGHT_GROUP_BOX_REQUEST,
                             hwnd, NULL, NULL, NULL);

    // Create a large label at (x, y) with width w and height h
    std::string jigId = get_selected_jig_id(hwnd);
    std::wstring jigIdW(jigId.begin(), jigId.end());

    hChoosenJigLabel = CreateWindowW(
        L"STATIC",                        // Class name
        jigIdW.c_str(),                  // Window name (text)
        WS_VISIBLE | WS_CHILD | SS_CENTER, // Styles
        LOC_X_LABEL_CHOOSEN_JIG_ID,      // width
        LOC_Y_LABEL_CHOOSEN_JIG_ID,     // height
        WIDTH_LABEL_CHOOSEN_JIG_ID,       // x position
        HEIGHT_LABEL_CHOOSEN_JIG_ID,      // y position
        hwnd,                     // Parent window handle
        NULL,                     // No menu
        GetModuleHandle(NULL),    // App instance
        NULL                      // No extra data
    );

    hLabelsFont = CreateFontW(
    32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
    CLEARTYPE_QUALITY, VARIABLE_PITCH, L"Segoe UI");

    SendMessage(hGroupBoxRequest, WM_SETFONT, (WPARAM)hMainMenuFont, TRUE);
    SendMessage(hChoosenJigLabel, WM_SETFONT, (WPARAM)hLabelsFont, TRUE);
}

HFONT& get_jig_main_menu_font(void)
{
    return hMainMenuFont;
}

HWND& getInstance_choosen_jig_id(void)
{
    return hChoosenJigLabel;
}

void create_main_menu_views(HWND hwnd)
{
    create_request_combo_box(hwnd);
    create_request_gui(hwnd);
    create_send_button(hwnd);
    create_req_output_terminal(hwnd);
    create_jig_wifi_boxes(hwnd);
    create_debug_output_terminal(hwnd);
}

void etablish_main_menu_enviroment(HWND hwnd)
{
    AppController::getInstance().on_mqtt_connection();
}

void destroy_main_menu_views(HWND hwnd)
{

}