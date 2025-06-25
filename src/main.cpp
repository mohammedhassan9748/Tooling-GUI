#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <iostream>

#include "00_main_window.hpp"
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "03_jig_id.hpp"
#include "04_server.hpp"
#include "05_connect_button.hpp"
#include "06_connection_status.hpp"

#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "03_request_gui.hpp"
#include "04_send_button.hpp"
#include "05_req_output_terminal.hpp"
#include "06_jig_wifi.hpp"
#include "07_debug_output_terminal.hpp"


extern HWND hChoosenJigLabel;

BOOL CALLBACK DestroyChildProc(HWND hwnd, LPARAM lParam) {
    DestroyWindow(hwnd);
    return TRUE;
}

// Main Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        create_start_menu_views(hwnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            case ID_COMBOBOX_JIG_ID:
                update_selected_jig_id(hwnd);
                break;
            case ID_BUTTON_CONNECT:
                handle_connect_button_click(hwnd);
                break;
            case ID_CONNECTION_ESTABLISHED:
                EnumChildWindows(hwnd, DestroyChildProc, 0);    // destroy the old window
                create_main_menu_views(hwnd);   // create the new window
                break;
            case ID_BUTTON_SEND:
                handle_send_button_click(hwnd);
                break;
        }
        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        break;
        
    case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC)wParam;
            HWND hStatic = (HWND)lParam;
            if(hStatic == getInstance_choosen_jig_id() || hStatic ==  getInstance_connection_status_box())
            {
                SetBkMode(hdcStatic, TRANSPARENT);
                return (INT_PTR)(GetSysColorBrush(COLOR_WINDOW));
            }
            else if (hStatic == getInstance_wifi_connection_status_box() ||
                hStatic == getInstance_wifi_network_status_box() ||
                hStatic == getInstance_mac_address_status_box()) 
            { 
                SetBkMode(hdcStatic, TRANSPARENT);
                SetTextColor(hdcStatic, get_status_color_brush()); // Set text color based on status
                return (INT_PTR)GetSysColorBrush(COLOR_WINDOW); // Use button face color
            }
            else if(hStatic == getInstance_debug_output_terminal() ||
                    hStatic == getInstance_req_output_terminal()) {
                SetBkMode(hdcStatic, TRANSPARENT);
                SetTextColor(hdcStatic, RGB(0,0,0)); // Set text color to black
                SetBkColor(hdcStatic, RGB(255,255,255)); // Set background color to white
                return (INT_PTR)GetSysColorBrush(COLOR_WINDOW); // Use button face color
            }
            break;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    // بعد كده تكمل عادي على الكود بتاعك
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    // wc.hbrBackground = (HBRUSH)(1); // System grey

    RegisterClass(&wc);

    // Create the window
    HWND& hwnd = getInstance_main_window(); // Use the global handle for the main window
    hwnd = CreateWindowEx(0, CLASS_NAME, L"Jig Control",
        WS_OVERLAPPEDWINDOW, 100, 100, 1080, 720, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    // Make the window full screen
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style |= (WS_OVERLAPPEDWINDOW); // Remove window decorations
    // style |= WS_POPUP;               // Make it a popup window (no border, no title)
    SetWindowLong(hwnd, GWL_STYLE, style);

    // Get screen size
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Resize and move the window to cover the whole screen
    SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);

    ShowWindow(hwnd, SW_MAXIMIZE);
    
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}