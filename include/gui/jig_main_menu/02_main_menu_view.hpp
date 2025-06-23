#ifndef MAIN_MENU_VIEW_HPP
#define MAIN_MENU_VIEW_HPP

#include <windows.h>

void create_request_combo_box(HWND hwnd);

HFONT& get_jig_main_menu_font(void);

HWND& getInstance_choosen_jig_id(void);

void create_main_menu_views(HWND hwnd);

void etablish_main_menu_enviroment(HWND hwnd);

void destroy_main_menu_views(HWND hwnd);

#endif /* START_MENU_VIEW_HPP */