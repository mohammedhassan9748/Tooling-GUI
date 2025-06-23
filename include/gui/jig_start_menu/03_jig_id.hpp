#ifndef JIG_ID_HPP
#define JIG_ID_HPP

#include <windows.h>
#include <string>

void create_jig_id_combo_box(HWND hwnd);
void update_jig_id_combo_box(HWND hwnd);
void update_selected_jig_id(HWND hwnd);
const std::string& get_selected_jig_id(HWND hwnd);

#endif /* JIG_ID_HPP */
