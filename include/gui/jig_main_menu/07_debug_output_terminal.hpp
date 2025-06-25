#ifndef DEBUG_OUTPUT_TERMINAL_HPP
#define DEBUG_OUTPUT_TERMINAL_HPP

#include <windows.h>
#include <string>

void create_debug_output_terminal(HWND hwnd);

void write_on_debug_output_terminal(HWND hwnd, const std::string& text);

void write_line_on_debug_output_terminal(HWND hwnd, const std::string&);

HWND& getInstance_debug_output_terminal(void);

#endif /* DEBUG_OUTPUT_TERMINAL_HPP */
