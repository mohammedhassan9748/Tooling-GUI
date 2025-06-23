#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#define NOMINMAX
#include <windows.h>
#include <algorithm>
#include "01_main_menu_data.hpp"
#include "02_main_menu_view.hpp"
#include "05_req_output_terminal.hpp"

HWND hReqOutputTerminal = NULL;

void create_req_output_terminal(HWND hwnd)
{
    // Create a read-only, multiline edit control with vertical scroll bar and visible caret
    hReqOutputTerminal = CreateWindowExW(
        0, L"EDIT", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        LOC_X_REQ_TERMINAL_OUTPUT, LOC_Y_REQ_TERMINAL_OUTPUT, WIDTH_REQ_TERMINAL_OUTPUT, HEIGHT_REQ_TERMINAL_OUTPUT,
        hwnd, (HMENU)1001, GetModuleHandleW(NULL), NULL
    );

    if (hReqOutputTerminal)
    {
        // Set font to a monospace font for terminal-like appearance
        HFONT hFont = CreateFontW(
            -16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            FIXED_PITCH | FF_MODERN, L"Consolas"
        );
        SendMessageW(hReqOutputTerminal, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Show the caret (cursor)
        CreateCaret(hReqOutputTerminal, NULL, 2, 16); // width, height; adjust as needed
        ShowCaret(hReqOutputTerminal);
    }
}

static void write_on_req_output_terminal(HWND hwnd, const std::string& text)
{    
    if (hReqOutputTerminal)
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
            int len = GetWindowTextLengthW(hReqOutputTerminal);
            // Set selection to the end
            SendMessageW(hReqOutputTerminal, EM_SETSEL, len, len);
            // Replace selection with new text (i.e., append)
            SendMessageW(hReqOutputTerminal, EM_REPLACESEL, FALSE, (LPARAM)wtext.c_str());
            // write new line in the end
            SendMessageW(hReqOutputTerminal, EM_REPLACESEL, FALSE, (LPARAM)L"\r\n");
        }
    }
}

void write_line_on_req_output_terminal(HWND hwnd, bool req ,const std::string& text)
{
    const size_t max_chars_per_line = 80; // ← adjust this based on terminal width and font

    std::string outBeginning;
    if(req)
    {   
        outBeginning = "$  ";
    }
    else
    {
        outBeginning = "-> ";
    }
    
    size_t start = 0;
    while (start < text.length())
    {
        size_t end = std::min(start + max_chars_per_line, text.length());
        std::string line = text.substr(start, end - start);
        write_on_req_output_terminal(hwnd, outBeginning + line);
        start = end;
    }
}

HWND& getInstance_req_output_terminal(void)
{
    return hReqOutputTerminal;
}