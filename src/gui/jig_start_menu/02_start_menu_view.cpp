#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "03_jig_id.hpp"
#include "04_server.hpp"
#include "05_connect_button.hpp"
#include "06_connection_status.hpp"

static HWND  hGroupBox = NULL; // Global handle for the group box
static HFONT hFont = NULL;     // Global handle for the font

bool StartMenuTurn = true; // Global variable to determine whether the start menu is it's turn to be displayed or not

// Function to create the Jig Controls menu
void create_jig_id_group_box(HWND hwnd) {
    // Create a font for the controls
    hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                       CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                       DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

    // Create the group box
    hGroupBox = CreateWindow(L"BUTTON", L"Choose Jig",
                             WS_VISIBLE | WS_CHILD | BS_GROUPBOX | ES_CENTER,
                             LOC_X_GROUP_BOX_JIG_ID, LOC_Y_GROUP_BOX_JIG_ID,
                             WIDTH_GROUP_BOX_JIG_ID, HEIGHT_GROUP_BOX_JIG_ID,
                             hwnd, NULL, NULL, NULL);
    SendMessage(hGroupBox, WM_SETFONT, (WPARAM)hFont, TRUE);
}

HFONT& get_jig_start_menu_font(void)
{
    return hFont; // Return the global font handle
}

// Function to create the start menu views
void create_start_menu_views(HWND hwnd)
{
    // Create the Jig Controls menu
    create_jig_id_group_box(hwnd);

    // Create the Jig ID combo box
    create_jig_id_combo_box(hwnd);

    // Create the Server GUI component
    create_server_gui(hwnd);

    // Create the Connect Button
    create_connect_button_gui(hwnd);

    // Create the Connection Status box
    create_connection_status_box(hwnd);
}

void destroy_start_menu_views(HWND hwnd)
{
    // Destroy the group box
    if (hGroupBox) {
        DestroyWindow(hGroupBox);
        hGroupBox = NULL;
    }

    // Destroy the font
    if (hFont) {
        DeleteObject(hFont);
        hFont = NULL;
    }

    // Destroy the Jig ID combo box
    HWND hComboBoxJigID = GetDlgItem(hwnd, ID_COMBOBOX_JIG_ID);
    if (hComboBoxJigID) {
        DestroyWindow(hComboBoxJigID);
    }

    // Destroy the Server GUI components
    HWND hEditBoxServerName = GetDlgItem(hwnd, ID_TEXT_BOX_SERVER_NAME);
    if (hEditBoxServerName) {
        DestroyWindow(hEditBoxServerName);
    }

    HWND hEditBoxPortNumber = GetDlgItem(hwnd, ID_TEXT_BOX_PORT_NUMBER);
    if (hEditBoxPortNumber) {
        DestroyWindow(hEditBoxPortNumber);
    }

    // Destroy the Connect Button
    HWND hConnectButton = GetDlgItem(hwnd, ID_BUTTON_CONNECT);
    if (hConnectButton) {
        DestroyWindow(hConnectButton);
    }

    // Destroy the Connection Status box
    HWND hConnectionStatusBox = GetDlgItem(hwnd, ID_CONNECTION_STATUS_BOX);
    if (hConnectionStatusBox) {
        DestroyWindow(hConnectionStatusBox);
    }
}

void setStartMenuTurn(bool turn)
{
    StartMenuTurn = true; // Set the global variable indicating it's the start menu's turn
}

void clearStartMenuTurn(void)
{
    StartMenuTurn = false; // Clear the global variable indicating it's not the start menu's turn
}

bool isStartMenuTurn(void)
{
    return StartMenuTurn; // Return the global variable indicating if it's the start menu's turn
}
