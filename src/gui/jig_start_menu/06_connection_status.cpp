#include <windows.h>
#include <string>
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "06_connection_status.hpp"

// Function to create the connection status box in the GUI
void create_connection_status_box(HWND hwnd)
{
    // Create a static control to display the connection status
    HWND hConnectionStatusBox = CreateWindowW(L"Static", L"Disconnected",
                                              WS_VISIBLE | WS_CHILD | SS_CENTER,
                                              LOC_X_STATUS_BOX_SERVER_CONNECTION,
                                              LOC_Y_STATUS_BOX_SERVER_CONNECTION,
                                              WIDTH_STATUS_BOX_SERVER_CONNECTION,
                                              HEIGHT_STATUS_BOX_SERVER_CONNECTION,
                                              hwnd, (HMENU)ID_CONNECTION_STATUS_BOX,
                                              NULL, NULL);

    // Set the font for the connection status box
    HFONT refFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    SendMessage(hConnectionStatusBox, WM_SETFONT, (WPARAM)refFont, TRUE);
}

// Function to update the connection status box text
void update_connection_status_box(HWND hwnd, const std::string &status)
{
    HWND hConnectionStatusBox = GetDlgItem(hwnd, ID_CONNECTION_STATUS_BOX);
    SetWindowText(hConnectionStatusBox, status.c_str());
}