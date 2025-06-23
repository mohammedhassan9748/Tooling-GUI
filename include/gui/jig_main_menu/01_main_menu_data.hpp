#ifndef MAIN_MENU_GUI_DRAW_HPP
#define MAIN_MENU_GUI_DRAW_HPP
/**
 * @brief This file contains the drawing data of the jig config menu.  
 * @file gui_draw.hpp
 * @version 0.1
 * @date 2025-05-26
 */

#include <windows.h>

// IDs for controls in the Jig Control Menu

#define ID_LABEL_REQUEST                    8
#define ID_TEXT_BOX_REQUEST                 9
#define ID_BUTTON_SEND                      10
#define ID_TERMINAL_OUTPUT                  11

/*
 * Layout:
 * ----------------Request---------------------------------------------------------------
 * |     [Request: Label] [          Text Box to enter the Request needed       ]       |
 * |                                                                [Send Button]       |
 * |                                                                                    |
 * |    [                                                                           ]   |
 * |    [                                                                           ]   |
 * |    [                   Large Terminal with scroll on the right                 ]   |                                                      ]   |
 * |    [                                                                           ]   |
 * |    [                                                                           ]   |
 * |                                                                                    |
 * --------------------------------------------------------------------------------------
 */

// 00_ Screen Dimensions
#define SCREEN_WIDTH_MAIN_WINDOW            GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT_MAIN_WINDOW           GetSystemMetrics(SM_CYSCREEN)

#define WIDTH_LABEL_CHOOSEN_JIG_ID          400
#define HEIGHT_LABEL_CHOOSEN_JIG_ID         30
#define LOC_X_LABEL_CHOOSEN_JIG_ID          ((SCREEN_WIDTH_MAIN_WINDOW - WIDTH_LABEL_CHOOSEN_JIG_ID) / 2)
#define LOC_Y_LABEL_CHOOSEN_JIG_ID          10

//  GUI Data for the Request Menu Group Box
#define WIDTH_GROUP_BOX_REQUEST             700
#define HEIGHT_GROUP_BOX_REQUEST            400
#define LOC_X_GROUP_BOX_REQUEST             ((SCREEN_WIDTH_MAIN_WINDOW - WIDTH_GROUP_BOX_REQUEST) - 50)
#define LOC_Y_GROUP_BOX_REQUEST             ((SCREEN_HEIGHT_MAIN_WINDOW - HEIGHT_GROUP_BOX_REQUEST) / 2 + 150)

//  GUI Data for the Request label
#define WIDTH_LABEL_REQUEST                 120
#define HEIGHT_LABEL_REQUEST                25
#define LOC_X_LABEL_REQUEST                 (LOC_X_GROUP_BOX_REQUEST + 20)
#define LOC_Y_LABEL_REQUEST                 (LOC_Y_GROUP_BOX_REQUEST + 30)

//  GUI Data for the Request Text Box
#define WIDTH_TEXT_BOX_REQUEST              (WIDTH_GROUP_BOX_REQUEST - WIDTH_LABEL_REQUEST - 150)
#define HEIGHT_TEXT_BOX_REQUEST             25
#define LOC_X_TEXT_BOX_REQUEST              (LOC_X_LABEL_REQUEST + WIDTH_LABEL_REQUEST + 10)
#define LOC_Y_TEXT_BOX_REQUEST              (LOC_Y_LABEL_REQUEST)

//  GUI Data for the Send Button
#define WIDTH_BUTTON_SEND                   100
#define HEIGHT_BUTTON_SEND                  25
#define LOC_X_BUTTON_SEND                   (LOC_X_TEXT_BOX_REQUEST + WIDTH_TEXT_BOX_REQUEST + 10)
#define LOC_Y_BUTTON_SEND                   (LOC_Y_TEXT_BOX_REQUEST)

//  GUI Data for the request output Terminal
#define WIDTH_REQ_TERMINAL_OUTPUT           (WIDTH_GROUP_BOX_REQUEST - 40)
#define HEIGHT_REQ_TERMINAL_OUTPUT          (HEIGHT_GROUP_BOX_REQUEST - 100)
#define LOC_X_REQ_TERMINAL_OUTPUT           (LOC_X_GROUP_BOX_REQUEST + 20)
#define LOC_Y_REQ_TERMINAL_OUTPUT           (LOC_Y_LABEL_REQUEST + HEIGHT_LABEL_REQUEST + 30)

// GUI Data for the debug output Group Box
#define WIDTH_GROUP_BOX_DEBUG_OUTPUT        700
#define HEIGHT_GROUP_BOX_DEBUG_OUTPUT       400
#define LOC_X_GROUP_BOX_DEBUG_OUTPUT        50
#define LOC_Y_GROUP_BOX_DEBUG_OUTPUT        LOC_Y_GROUP_BOX_REQUEST

//  GUI Data for the debug output Terminal
#define WIDTH_DEBUG_TERMINAL_OUTPUT         (WIDTH_GROUP_BOX_DEBUG_OUTPUT - 40)
#define HEIGHT_DEBUG_TERMINAL_OUTPUT        (HEIGHT_GROUP_BOX_DEBUG_OUTPUT - 40)
#define LOC_X_DEBUG_TERMINAL_OUTPUT         (LOC_X_GROUP_BOX_DEBUG_OUTPUT + 20)
#define LOC_Y_DEBUG_TERMINAL_OUTPUT         (LOC_Y_GROUP_BOX_DEBUG_OUTPUT + 30)

//  GUI Data for the Wifi Group Box
#define WIDTH_GROUP_BOX_WIFI_CONNECTION     300
#define HEIGHT_GROUP_BOX_WIFI_CONNECTION    70
#define LOC_X_GROUP_BOX_WIFI_CONNECTION     20
#define LOC_Y_GROUP_BOX_WIFI_CONNECTION     60

//  GUI Data for the Wifi Connection Status Box (inside the Wifi Group Box)
#define WIDTH_STATUS_BOX_WIFI_CONNECTION    200
#define HEIGHT_STATUS_BOX_WIFI_CONNECTION   30
#define LOC_X_STATUS_BOX_WIFI_CONNECTION    (LOC_X_GROUP_BOX_WIFI_CONNECTION + (WIDTH_GROUP_BOX_WIFI_CONNECTION - WIDTH_STATUS_BOX_WIFI_CONNECTION) / 2)
#define LOC_Y_STATUS_BOX_WIFI_CONNECTION    (LOC_Y_GROUP_BOX_WIFI_CONNECTION + (HEIGHT_GROUP_BOX_WIFI_CONNECTION - HEIGHT_STATUS_BOX_WIFI_CONNECTION) / 2 + 10)

//  GUI Data for the Wifi Network Name Group Box (inside the Wifi Group Box)
#define WIDTH_GROUP_BOX_WIFI_NETWORK        300
#define HEIGHT_GROUP_BOX_WIFI_NETWORK       70
#define LOC_X_GROUP_BOX_WIFI_NETWORK        (LOC_X_GROUP_BOX_WIFI_CONNECTION + WIDTH_GROUP_BOX_WIFI_CONNECTION + 20) 
#define LOC_Y_GROUP_BOX_WIFI_NETWORK        (LOC_Y_GROUP_BOX_WIFI_CONNECTION)

//  GUI Data for the Wifi Network Name Status Box (inside the Wifi Group Box)
#define WIDTH_STATUS_BOX_WIFI_NETWORK        200
#define HEIGHT_STATUS_BOX_WIFI_NETWORK       30
#define LOC_X_STATUS_BOX_WIFI_NETWORK        (LOC_X_GROUP_BOX_WIFI_NETWORK + (WIDTH_GROUP_BOX_WIFI_NETWORK - WIDTH_STATUS_BOX_WIFI_NETWORK) / 2)
#define LOC_Y_STATUS_BOX_WIFI_NETWORK        (LOC_Y_GROUP_BOX_WIFI_NETWORK + (HEIGHT_GROUP_BOX_WIFI_NETWORK - HEIGHT_STATUS_BOX_WIFI_NETWORK) / 2 + 10)

//  GUI Data for the Mac Address Group Box (inside the Wifi Group Box)
#define WIDTH_GROUP_BOX_MAC_ADDRESS         300
#define HEIGHT_GROUP_BOX_MAC_ADDRESS        70
#define LOC_X_GROUP_BOX_MAC_ADDRESS         (LOC_X_GROUP_BOX_WIFI_NETWORK + WIDTH_GROUP_BOX_WIFI_NETWORK + 20)
#define LOC_Y_GROUP_BOX_MAC_ADDRESS         (LOC_Y_GROUP_BOX_WIFI_NETWORK)

//  GUI Data for the Mac Address Status Box (inside the Wifi Group Box)
#define WIDTH_STATUS_BOX_MAC_ADDRESS        200
#define HEIGHT_STATUS_BOX_MAC_ADDRESS       30
#define LOC_X_STATUS_BOX_MAC_ADDRESS        (LOC_X_GROUP_BOX_MAC_ADDRESS + (WIDTH_GROUP_BOX_MAC_ADDRESS - WIDTH_STATUS_BOX_MAC_ADDRESS) / 2)
#define LOC_Y_STATUS_BOX_MAC_ADDRESS        (LOC_Y_GROUP_BOX_MAC_ADDRESS + (HEIGHT_GROUP_BOX_MAC_ADDRESS - HEIGHT_STATUS_BOX_MAC_ADDRESS) / 2 + 10)

#endif /* MAIN_MENU_GUI_DRAW_HPP */
