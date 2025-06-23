#ifndef JIG_WIFI_HPP
#define JIG_WIFI_HPP

#include <windows.h>
#include <string>

// Function to create the connection status box in the GUI
void create_jig_wifi_boxes(HWND hwnd);

// Function to update the wifi connection status of the jig
void update_jig_wifi_connection_box(HWND hwnd, const std::string& status);

// Function to update the wifi network name box of the jig
void update_jig_wifi_network_box(HWND hwnd, const std::string& status);

// Function to update the mac address of the jig
void update_jig_mac_address_box(HWND hwnd, const std::string& status);

HWND& getInstance_wifi_connection_status_box(void);

HWND& getInstance_wifi_network_status_box(void);

HWND& getInstance_mac_address_status_box(void);

void update_status_color(bool status);

COLORREF& get_status_color_brush(void);

#endif /* JIG_WIFI_HPP */
