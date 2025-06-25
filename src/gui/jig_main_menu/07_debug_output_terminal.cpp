#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#define NOMINMAX
#include <windows.h>
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "07_debug_output_terminal.hpp"

HWND hDebugOutputTerminal = NULL;
HWND hDebugOutputGroupBox = NULL;

void create_debug_output_terminal(HWND hwnd)
{
    // Create a read-only, multiline edit control with vertical scroll bar and visible caret
    hDebugOutputTerminal = CreateWindowExW(
        0, L"EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        LOC_X_DEBUG_TERMINAL_OUTPUT, LOC_Y_DEBUG_TERMINAL_OUTPUT, WIDTH_DEBUG_TERMINAL_OUTPUT, 
        HEIGHT_DEBUG_TERMINAL_OUTPUT, hwnd, (HMENU)1001, GetModuleHandleW(NULL), NULL
    );

    HFONT& refFont = get_jig_main_menu_font();

    if (hDebugOutputTerminal)
    {
        SendMessageW(hDebugOutputTerminal, WM_SETFONT, (WPARAM)refFont, TRUE);

        // Show the caret (cursor)
        CreateCaret(hDebugOutputTerminal, NULL, 2, 16); // width, height; adjust as needed
        ShowCaret(hDebugOutputTerminal);
    }
    
    // Set font for the group box to match the terminal (optional: smaller size, regular weight)
    hDebugOutputGroupBox = CreateWindowExW(
        0, L"BUTTON", L"Debug Output",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        LOC_X_GROUP_BOX_DEBUG_OUTPUT, LOC_Y_GROUP_BOX_DEBUG_OUTPUT, WIDTH_GROUP_BOX_DEBUG_OUTPUT, 
        HEIGHT_GROUP_BOX_DEBUG_OUTPUT, hwnd, (HMENU)1002, GetModuleHandleW(NULL), NULL
    );
    
    if (hDebugOutputGroupBox)
    {
        SendMessageW(hDebugOutputGroupBox, WM_SETFONT, (WPARAM)refFont, TRUE);
    }
}

void write_on_debug_output_terminal(HWND hwnd, const std::string& text)
{    
    if (hDebugOutputTerminal)
    {
        // Convert std::string (UTF-8 or ANSI) to wide string
        int wlen = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
        if (wlen > 1)
        {
            std::wstring wtext(wlen, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &wtext[0], wlen);
            // Remove the null terminator for EM_REPLACESEL
            wtext.pop_back();

            // Get current text length
            int len = GetWindowTextLengthW(hDebugOutputTerminal);
            // Set selection to the end
            SendMessageW(hDebugOutputTerminal, EM_SETSEL, len, len);
            // Replace selection with new text (i.e., append)
            SendMessageW(hDebugOutputTerminal, EM_REPLACESEL, FALSE, (LPARAM)wtext.c_str());
            // write new line in the end
            SendMessageW(hDebugOutputTerminal, EM_REPLACESEL, FALSE, (LPARAM)L"\r\n");
        }
    }
}

void write_line_on_debug_output_terminal(HWND hwnd, const std::string& text)
{
    const size_t max_chars_per_line = 67;
    std::string prefix = "-> ";
    size_t start = 0;

    bool first_line = true;

    while (start < text.length())
    {
        size_t space_for_text = max_chars_per_line - (first_line ? prefix.length() : 0);
        size_t end = std::min(start + space_for_text, text.length());
        std::string chunk = text.substr(start, end - start);

        std::string line_to_write = (first_line ? prefix : prefix) + chunk;
        write_on_debug_output_terminal(hwnd, line_to_write);

        start = end;
        first_line = false;
    }
}

HWND& getInstance_debug_output_terminal(void)
{
    return hDebugOutputTerminal;
}