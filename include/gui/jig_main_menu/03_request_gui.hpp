#ifndef REQUEST_TEXT_BOX_HPP
#define REQUEST_TEXT_BOX_HPP

#include <windows.h>
#include <string>

void create_request_gui(HWND hwnd);

const std::string& get_typed_request(HWND hwnd);

#endif /* REQUEST_TEXT_BOX_HPP */

