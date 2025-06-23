#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


#include <windows.h>
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "03_request_gui.hpp"
#include <iostream>

HWND hEditBoxRequest = NULL; // Global handle for the Request edit box
HWND hLabelRequest = NULL; // Global handle for the Request label

std::string typed_request = "";

void create_request_gui(HWND hwnd)
{
    // Create the Server Name label
    hLabelRequest = CreateWindowW(L"Static", L"Request: ", WS_VISIBLE | WS_CHILD | SS_CENTER,
    LOC_X_LABEL_REQUEST, LOC_Y_LABEL_REQUEST, 
    WIDTH_LABEL_REQUEST, HEIGHT_LABEL_REQUEST, 
    hwnd, NULL, NULL, NULL);

    // Create the Server Name edit box
    hEditBoxRequest = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
    LOC_X_TEXT_BOX_REQUEST, LOC_Y_TEXT_BOX_REQUEST, WIDTH_TEXT_BOX_REQUEST, HEIGHT_TEXT_BOX_REQUEST, 
    hwnd, NULL, NULL, NULL);
    
    // Set the font for the controls
    HFONT& refFont = get_jig_main_menu_font();
    SendMessage(hLabelRequest, WM_SETFONT, (WPARAM)refFont, TRUE);
    SendMessage(hEditBoxRequest, WM_SETFONT, (WPARAM)refFont, TRUE);
}

const std::string& get_typed_request(HWND hwnd)
{

    // Retrieve the text from the Server Name edit box
    int length = GetWindowTextLength(hEditBoxRequest);

    if (length == 0) {
        typed_request = "";
        return typed_request;
    }

    std::wstring buffer(length, L'\0');

    GetWindowTextW(hEditBoxRequest, &buffer[0], length + 1);

    typed_request = std::string(buffer.begin(), buffer.end());

    return typed_request;
}