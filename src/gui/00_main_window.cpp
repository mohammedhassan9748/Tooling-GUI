#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include "00_main_window.hpp"

HWND main_window_handle = NULL; // Global handle for the main window

HWND& getInstance_main_window(void)
{
   return main_window_handle;
}