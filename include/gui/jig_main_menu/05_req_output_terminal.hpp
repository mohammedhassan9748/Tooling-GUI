#ifndef REQ_OUTPUT_TERMINAL_HPP
#define REQ_OUTPUT_TERMINAL_HPP

#include <windows.h>
#include <string>

void create_req_output_terminal(HWND hwnd);

void write_line_on_req_output_terminal(HWND hwnd, bool, const std::string&);

HWND& getInstance_req_output_terminal(void);

#endif /* REQ_OUTPUT_TERMINAL_HPP */