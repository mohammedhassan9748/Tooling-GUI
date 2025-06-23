#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "04_send_button.hpp"
#include "AppController.hpp"

HWND hSendButton = NULL; // Global handle for the Connect Button

void create_send_button(HWND hwnd)
{
    // Create the Connect Button
    hSendButton = CreateWindowW(L"Button", L"Send", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                   LOC_X_BUTTON_SEND, LOC_Y_BUTTON_SEND,
                                   WIDTH_BUTTON_SEND, HEIGHT_BUTTON_SEND,
                                   hwnd, (HMENU)ID_BUTTON_SEND, NULL, NULL);

    // Set the font for the Connect Button
    HFONT refFont = get_jig_main_menu_font();
    SendMessage(hSendButton, WM_SETFONT, (WPARAM)refFont, TRUE);
}

void handle_send_button_click(HWND hwnd)
{
    // Handle the Connect Button logic will be implemented here
    AppController::getInstance().on_send_button_pressed();
}