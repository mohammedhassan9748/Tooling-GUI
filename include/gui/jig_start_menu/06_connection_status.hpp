#ifndef CONNECTION_STATUS_HPP
#define CONNECTION_STATUS_HPP

#include <windows.h>
#include <string>

// Function to create the connection status box in the GUI
void create_connection_status_box(HWND hwnd);

// Function to update the connection status box text
void update_connection_status_box(HWND hwnd, const std::string& status);

// Function to get the handle of the connection status box
HWND& getInstance_connection_status_box(void);

#endif /* CONNECTION_STATUS_HPP */
