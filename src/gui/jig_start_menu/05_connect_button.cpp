#include <windows.h>
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "05_connect_button.hpp"
#include "06_connection_status.hpp"
 
#include "AppController.hpp"
#include "02_main_menu_view.hpp"


HWND hConnectButton = NULL; // Global handle for the Connect Button

void create_connect_button_gui(HWND hwnd)
{
    // Create the Connect Button
    hConnectButton = CreateWindowW(L"Button", L"Connect", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    LOC_X_BUTTON_CONNECT, LOC_Y_BUTTON_CONNECT,
                                   WIDTH_BUTTON_CONNECT, HEIGHT_BUTTON_CONNECT,
                                   hwnd, (HMENU)ID_BUTTON_CONNECT, NULL, NULL);

    // Set the font for the Connect Button
    HFONT refFont = get_jig_start_menu_font();
    SendMessage(hConnectButton, WM_SETFONT, (WPARAM)refFont, TRUE);
}

// Function to handle the Connect Button click event
void handle_connect_button_click(HWND hwnd)
{
    // Handle the Connect Button logic will be implemented here
    AppController::getInstance().on_connect_button_pressed();
}

void connection_established(HWND hwnd)
{
    std::cout << "Connection established successfully." << std::endl;
    PostMessage(hwnd, WM_COMMAND, ID_CONNECTION_ESTABLISHED, 0);
}