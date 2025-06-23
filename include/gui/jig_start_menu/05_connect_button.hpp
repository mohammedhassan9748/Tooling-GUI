#ifndef CONNECT_BUTTON_HPP
#define CONNECT_BUTTON_HPP
/**
 * @file connect_button.hpp
 * @brief Header file for the Connect Button in the Jig Control Menu.
 *
 * This file contains the declarations and function prototypes for the Connect Button,
 * which allows users to connect to a server or perform actions related to the Jig ID.
 *
 * @version 0.1
 * @date 2025-05-26
 */


#include <windows.h>

// Function to create the Connect Button in the GUI
void create_connect_button_gui(HWND hwnd);

// Function to handle the Connect Button click event
void handle_connect_button_click(HWND hwnd);

void connection_established(HWND hwnd);

#endif /* CONNECT_BUTTON_HPP */
