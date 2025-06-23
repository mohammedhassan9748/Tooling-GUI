#ifndef START_MENU_GUI_DRAW_HPP
#define START_MENU_GUI_DRAW_HPP
/**
 * @brief This file contains the drawing data of the jig config menu.  
 * @file gui_draw.hpp
 * @version 0.1
 * @date 2025-05-26
 */

#include <windows.h>

// IDs for controls in the Jig Control Menu

#define ID_LABEL_JIG_ID                     1
#define ID_COMBOBOX_JIG_ID                  2

#define ID_TEXT_BOX_SERVER_NAME             3
#define ID_TEXT_BOX_PORT_NUMBER             4

#define ID_BUTTON_CONNECT                   5
#define ID_CONNECTION_STATUS_BOX            6

#define ID_CONNECTION_ESTABLISHED           7

/*
 * Layout:
 * ------------Jig Configuration----------------------------------------------
 * | [Jig ID Label] [Combo Box] | [Server Name Label] [Server Name Text Box] |
 * |                            | [Port Number Label] [Port Number Text Box] |
 * |                                                        [Connect Button] |
 * ----------------------------------------------------------------------------
 * [    The connection status will be displayed here in the future           ]
 */

//  00_ Screen Dimensions
#define SCREEN_WIDTH                        GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT                       GetSystemMetrics(SM_CYSCREEN)

// 01_ GUI Data for the Jig Control Menu Group Box
#define WIDTH_GROUP_BOX_JIG_ID              800
#define HEIGHT_GROUP_BOX_JIG_ID             200
#define LOC_X_GROUP_BOX_JIG_ID              ((SCREEN_WIDTH - WIDTH_GROUP_BOX_JIG_ID) / 2)
#define LOC_Y_GROUP_BOX_JIG_ID              ((SCREEN_HEIGHT - HEIGHT_GROUP_BOX_JIG_ID) / 2)


// 02_ Jig ID Label (top-left of group box)
#define LOC_X_LABEL_JIG_ID                  (LOC_X_GROUP_BOX_JIG_ID + 30)
#define LOC_Y_LABEL_JIG_ID                  (LOC_Y_GROUP_BOX_JIG_ID + 30)
#define WIDTH_LABEL_JIG_ID                  90
#define HEIGHT_LABEL_JIG_ID                 20

// 03_ Combo Box for Jig ID (right of label)
#define LOC_X_COMBO_BOX_JIG_ID              (LOC_X_LABEL_JIG_ID + WIDTH_LABEL_JIG_ID + 10)
#define LOC_Y_COMBO_BOX_JIG_ID              LOC_Y_LABEL_JIG_ID
#define WIDTH_COMBO_BOX_JIG_ID              150
#define HEIGHT_COMBO_BOX_JIG_ID             200

// 04_ Server Name Label (starts from middle column)
#define LOC_X_LABEL_SERVER_NAME             (LOC_X_GROUP_BOX_JIG_ID + WIDTH_GROUP_BOX_JIG_ID / 2 + 10)
#define LOC_Y_LABEL_SERVER_NAME             LOC_Y_LABEL_JIG_ID
#define WIDTH_LABEL_SERVER_NAME             100
#define HEIGHT_LABEL_SERVER_NAME            20

// 05_ Server Name Text Box (right of label)
#define LOC_X_TEXT_BOX_SERVER_NAME          (LOC_X_LABEL_SERVER_NAME + WIDTH_LABEL_SERVER_NAME + 10)
#define LOC_Y_TEXT_BOX_SERVER_NAME          LOC_Y_LABEL_SERVER_NAME
#define WIDTH_TEXT_BOX_SERVER_NAME          180
#define HEIGHT_TEXT_BOX_SERVER_NAME         20

// 06_ Port Number Label (below Server Name Label)
#define LOC_X_LABEL_PORT_NUMBER             LOC_X_LABEL_SERVER_NAME
#define LOC_Y_LABEL_PORT_NUMBER             (LOC_Y_LABEL_SERVER_NAME + HEIGHT_LABEL_SERVER_NAME + 15)
#define WIDTH_LABEL_PORT_NUMBER             100
#define HEIGHT_LABEL_PORT_NUMBER            20

// 07_ Port Number Text Box (right of Port Number Label)
#define LOC_X_TEXT_BOX_PORT_NUMBER          LOC_X_TEXT_BOX_SERVER_NAME
#define LOC_Y_TEXT_BOX_PORT_NUMBER          (LOC_Y_TEXT_BOX_SERVER_NAME + HEIGHT_TEXT_BOX_SERVER_NAME + 15)
#define WIDTH_TEXT_BOX_PORT_NUMBER          180
#define HEIGHT_TEXT_BOX_PORT_NUMBER         20

// 08_ Connect Button (below Port Number Text Box)
#define LOC_X_BUTTON_CONNECT                LOC_X_TEXT_BOX_PORT_NUMBER
#define LOC_Y_BUTTON_CONNECT                (LOC_Y_TEXT_BOX_PORT_NUMBER + HEIGHT_TEXT_BOX_PORT_NUMBER + 15)
#define WIDTH_BUTTON_CONNECT                100
#define HEIGHT_BUTTON_CONNECT               30

// 09_ Connection Status Box (below the group box)
#define LOC_X_STATUS_BOX_SERVER_CONNECTION         LOC_X_GROUP_BOX_JIG_ID
#define LOC_Y_STATUS_BOX_SERVER_CONNECTION         (LOC_Y_GROUP_BOX_JIG_ID + HEIGHT_GROUP_BOX_JIG_ID + 20)
#define WIDTH_STATUS_BOX_SERVER_CONNECTION         WIDTH_GROUP_BOX_JIG_ID
#define HEIGHT_STATUS_BOX_SERVER_CONNECTION        30

// BOOL CALLBACK DestroyChildProc(HWND hwnd, LPARAM lParam);

#endif /* START_MENU_GUI_DRAW_HPP */
