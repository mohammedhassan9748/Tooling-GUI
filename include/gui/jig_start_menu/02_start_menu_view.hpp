#ifndef START_MENU_VIEW_HPP
#define START_MENU_VIEW_HPP

#include <windows.h>

void create_jig_id_group_box(HWND hwnd);

HFONT& get_jig_start_menu_font(void);

void create_start_menu_views(HWND hwnd);

void destroy_start_menu_views(HWND hwnd);

void setStartMenuTurn(bool turn);

void clearStartMenuTurn(void);

bool isStartMenuTurn(void);

#endif /* START_MENU_VIEW_HPP */
