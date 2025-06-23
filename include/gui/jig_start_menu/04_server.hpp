#ifndef SERVER_HPP
#define SERVER_HPP

/**
 * @file Server.hpp
 * @brief Header file for the Server GUI component.
 *
 * This file contains the declarations and function prototypes for the Server GUI component,
 * which allows users to manage Jig IDs and communicate with the server.
 *
 * @version 0.1
 * @date 2025-05-26
 *
 */

#include <windows.h>
#include <string>

// Function to create the Server GUI component
void create_server_gui(HWND parent);

// Function to handle the server connection
const std::string& get_current_server_name();

// Function to get the current port number
const std::string& get_current_port_number();

#endif /* SERVER_HPP */
