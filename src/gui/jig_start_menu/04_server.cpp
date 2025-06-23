#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif


#include <windows.h>
#include <string>
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "04_server.hpp"

std::string currentServerName = ""; // Global variable to store the current server name
std::string currentPortNumber = ""; // Global variable to store the current port number

HWND hEditBoxServerName = NULL; // Global handle for the Server Name edit box
HWND hEditBoxPortNumber = NULL; // Global handle for the Port Number edit box

HWND hLabelServerName = NULL; // Global handle for the Server Name label
HWND hLabelPortNumber = NULL; // Global handle for the Port Number label

// Function to create the Server GUI component
void create_server_gui(HWND hwnd) {
    // Create the Server Name label
    hLabelServerName = CreateWindowW(L"Static", L"Server Name:", WS_VISIBLE | WS_CHILD,
    LOC_X_LABEL_SERVER_NAME, LOC_Y_LABEL_SERVER_NAME, 
    WIDTH_LABEL_SERVER_NAME, HEIGHT_LABEL_SERVER_NAME, 
    hwnd, NULL, NULL, NULL);
    
    // Create the Server Name edit box
    hEditBoxServerName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
    LOC_X_TEXT_BOX_SERVER_NAME, LOC_Y_TEXT_BOX_SERVER_NAME, WIDTH_TEXT_BOX_SERVER_NAME, HEIGHT_TEXT_BOX_SERVER_NAME, hwnd, NULL, NULL, NULL);

    // Set default value for the Server Name edit box
    SetWindowTextW(hEditBoxServerName, L"broker.hivemq.com");
    
    // Create the Port Number label
    hLabelPortNumber = CreateWindowW(L"Static", L"Port Number:", WS_VISIBLE | WS_CHILD,
    LOC_X_LABEL_PORT_NUMBER, LOC_Y_LABEL_PORT_NUMBER, WIDTH_LABEL_PORT_NUMBER, HEIGHT_LABEL_PORT_NUMBER, hwnd, NULL, NULL, NULL);
    
    // Create the Port Number edit box
    hEditBoxPortNumber = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
    LOC_X_TEXT_BOX_PORT_NUMBER, LOC_Y_TEXT_BOX_PORT_NUMBER, WIDTH_TEXT_BOX_PORT_NUMBER, HEIGHT_TEXT_BOX_PORT_NUMBER, hwnd, NULL, NULL, NULL);
    
    // Set default value for the Server Name edit box
    SetWindowTextW(hEditBoxPortNumber, L"1883");
    
    // Set the font for the controls
    HFONT refFont = get_jig_start_menu_font();
    SendMessage(hLabelServerName, WM_SETFONT, (WPARAM)refFont, TRUE);
    SendMessage(hEditBoxServerName, WM_SETFONT, (WPARAM)refFont, TRUE);
    SendMessage(hLabelPortNumber, WM_SETFONT, (WPARAM)refFont, TRUE);
    SendMessage(hEditBoxPortNumber, WM_SETFONT, (WPARAM)refFont, TRUE);
}

// Function to get the current server name
const std::string& get_current_server_name() {

    // Retrieve the text from the Server Name edit box
    int length = GetWindowTextLength(hEditBoxServerName);

    if (length == 0) {
        currentServerName = "";
        return currentServerName;
    }

    std::wstring buffer(length, L'\0');
    GetWindowTextW(hEditBoxServerName, &buffer[0], length + 1);
    currentServerName = std::string(buffer.begin(), buffer.end());

    return currentServerName;
}

// Function to get the current port number
const std::string& get_current_port_number() {
    // Retrieve the text from the Port Number edit box
    int length = GetWindowTextLength(hEditBoxPortNumber);

    if (length == 0) {
        currentPortNumber = "";
        return currentPortNumber;
    }

    std::wstring buffer(length, L'\0');
    GetWindowTextW(hEditBoxPortNumber, &buffer[0], length + 1);
    currentPortNumber = std::string(buffer.begin(), buffer.end());

    return currentPortNumber;
}
