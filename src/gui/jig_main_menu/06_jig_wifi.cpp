#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <iostream>
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "06_jig_wifi.hpp"

HWND hWifiConnectionGroupBox = NULL;
HWND hWifiConnectionStatusBox = NULL;
HWND hWifiNetworkGroupBox = NULL;
HWND hWifiNetworkStatusBox = NULL;
HWND hMacAddressGroupBox = NULL;
HWND hMacAddressStatusBox = NULL;
COLORREF status_color = RGB(255, 0, 0); // Red default color for status boxes

void create_jig_wifi_boxes(HWND hwnd)
{
    // Create the group box
    hWifiConnectionGroupBox = CreateWindowW(
        L"BUTTON", L"Wifi Status",
        WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
        LOC_X_GROUP_BOX_WIFI_CONNECTION,  // X position
        LOC_Y_GROUP_BOX_WIFI_CONNECTION,  // Y position
        WIDTH_GROUP_BOX_WIFI_CONNECTION,  // Width
        HEIGHT_GROUP_BOX_WIFI_CONNECTION, // Height
        hwnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    // Create a static control to display the connection status
    hWifiConnectionStatusBox = CreateWindowW(
        L"Static", L"Disconnected",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        LOC_X_STATUS_BOX_WIFI_CONNECTION, LOC_Y_STATUS_BOX_WIFI_CONNECTION,
        WIDTH_STATUS_BOX_WIFI_CONNECTION, HEIGHT_STATUS_BOX_WIFI_CONNECTION,
        hwnd, NULL, NULL, NULL
    );

    // Create the group box for Wifi Network
    hWifiNetworkGroupBox = CreateWindowW(
        L"BUTTON", L"Wifi Network",
        WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
        LOC_X_GROUP_BOX_WIFI_NETWORK,  // X position
        LOC_Y_GROUP_BOX_WIFI_NETWORK,  // Y position
        WIDTH_GROUP_BOX_WIFI_NETWORK,  // Width
        HEIGHT_GROUP_BOX_WIFI_NETWORK, // Height
        hwnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    // Create a static control to display the network status
    hWifiNetworkStatusBox = CreateWindowW(
        L"Static", L"Network: N/A",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        LOC_X_STATUS_BOX_WIFI_NETWORK, LOC_Y_STATUS_BOX_WIFI_NETWORK,
        WIDTH_STATUS_BOX_WIFI_NETWORK, HEIGHT_STATUS_BOX_WIFI_NETWORK,
        hwnd, NULL, NULL, NULL
    );

    // Create the group box for MAC Address
    hMacAddressGroupBox = CreateWindowW(
        L"BUTTON", L"MAC Address",
        WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
        LOC_X_GROUP_BOX_MAC_ADDRESS,  // X position
        LOC_Y_GROUP_BOX_MAC_ADDRESS,  // Y position
        WIDTH_GROUP_BOX_MAC_ADDRESS,  // Width
        HEIGHT_GROUP_BOX_MAC_ADDRESS, // Height
        hwnd,
        NULL,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    // Create a static control to display the MAC address status
    hMacAddressStatusBox = CreateWindowW(
        L"Static", L"MAC: N/A",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        LOC_X_STATUS_BOX_MAC_ADDRESS, LOC_Y_STATUS_BOX_MAC_ADDRESS,
        WIDTH_STATUS_BOX_MAC_ADDRESS, HEIGHT_STATUS_BOX_MAC_ADDRESS,
        hwnd, NULL, NULL, NULL
    );

    // Set the font for the controls
    // Get the base font and make a bold version
    HFONT& refFont = get_jig_main_menu_font();
    LOGFONT lf = {0};
    GetObject(refFont, sizeof(LOGFONT), &lf);
    lf.lfWeight = FW_BOLD;
    HFONT first = CreateFontIndirect(&lf);
    lf.lfHeight = lf.lfHeight * 1.3; // Increase font size by 30%
    if (lf.lfHeight == 0) lf.lfHeight = -18; // fallback if original is 0
    HFONT hBoldFont = CreateFontIndirect(&lf);

    SendMessage(hWifiConnectionGroupBox, WM_SETFONT, (WPARAM)first, TRUE);
    SendMessage(hWifiConnectionStatusBox, WM_SETFONT, (WPARAM)hBoldFont, TRUE);
    SendMessage(hWifiNetworkGroupBox, WM_SETFONT, (WPARAM)first, TRUE);
    SendMessage(hWifiNetworkStatusBox, WM_SETFONT, (WPARAM)hBoldFont, TRUE);
    SendMessage(hMacAddressGroupBox, WM_SETFONT, (WPARAM)first, TRUE);
    SendMessage(hMacAddressStatusBox, WM_SETFONT, (WPARAM)hBoldFont, TRUE);
}

// Function to update the wifi connection status of the jig
void update_jig_wifi_connection_box(HWND hwnd, const std::string& status)
{
    std::wstring wstatus(status.begin(), status.end());
    SetWindowTextW(hWifiConnectionStatusBox, wstatus.c_str());
    InvalidateRect(hWifiConnectionStatusBox, NULL, TRUE); // ✅ force redraw
}

// Function to update the wifi network name box of the jig
void update_jig_wifi_network_box(HWND hwnd, const std::string& status)
{
    std::wstring wstatus(status.begin(), status.end());
    SetWindowTextW(hWifiNetworkStatusBox, wstatus.c_str());
    InvalidateRect(hWifiNetworkStatusBox, NULL, TRUE); // ✅ force redraw
}

// Function to update the mac address of the current jig
void update_jig_mac_address_box(HWND hwnd, const std::string& status)
{
    std::wstring wstatus(status.begin(), status.end());
    SetWindowTextW(hMacAddressStatusBox, wstatus.c_str());
    InvalidateRect(hMacAddressStatusBox, NULL, TRUE); // ✅ force redraw
}

HWND& getInstance_wifi_connection_status_box(void)
{
    return hWifiConnectionStatusBox;
}

HWND& getInstance_wifi_network_status_box(void)
{
    return hWifiNetworkStatusBox;
}

HWND& getInstance_mac_address_status_box(void)
{
    return hMacAddressStatusBox;
}

void update_status_color(bool status)
{
    // Update the background color of the Wifi Connection Status Box based on connection status
    if (status) {
        status_color = RGB(0, 128, 0); // Dark green for connected
    } else {
        status_color = RGB(255, 0, 0); // Red for disconnected
    }
}

COLORREF& get_status_color_brush(void)
{
    // Create a brush with the current status color
    return status_color;
}