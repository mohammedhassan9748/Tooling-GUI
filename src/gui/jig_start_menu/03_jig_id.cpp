#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include "01_start_menu_data.hpp"
#include "02_start_menu_view.hpp"
#include "03_jig_id.hpp"

// I want to make fucntion that responsiple for creating the GUI for the JigID
// The jig Id is: a drop box where I select between lists of texts
// and a button where I can add a new jig id, the jig is composed of three parts:
// example: if the jig project name is ZE115
// 1. The first part is the project name, is "ZE"
// 2. The second part is the jig number, is "115"
// 3. The third part is the jig number because I have multiple jigs in same project
//    therefore the jig ID is: ZE115_1 or ZE115_2, etc.

// global variables for the GUI controls
HWND hLabelJigID = NULL;
HWND hComboBoxJigID = NULL;

static std::string currentJigID = "";

static std::vector<std::wstring> jigIDs = 
{
    L"USGM30_1", 
    L"USGM30_2", 
    L"USGM30_3",
};

// So there is a button in the GUI to add a new JigID
void create_jig_id_combo_box(HWND hwnd)
{
    // Create a label for the JigID
    hLabelJigID = CreateWindowW(L"Static", L"Select Jig ID:", WS_VISIBLE | 
    WS_CHILD, LOC_X_LABEL_JIG_ID, LOC_Y_LABEL_JIG_ID, 
    WIDTH_LABEL_JIG_ID, HEIGHT_LABEL_JIG_ID, hwnd, 
    (HMENU)ID_LABEL_JIG_ID, NULL, NULL);
    
    // Create a combo box for selecting Jig IDs
    hComboBoxJigID = CreateWindowW(L"ComboBox", L"", WS_VISIBLE | 
    WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 
    LOC_X_COMBO_BOX_JIG_ID, LOC_Y_COMBO_BOX_JIG_ID, 
    WIDTH_COMBO_BOX_JIG_ID, HEIGHT_COMBO_BOX_JIG_ID, hwnd, 
    (HMENU)ID_COMBOBOX_JIG_ID, NULL, NULL);

    // Set the font for the label and combo box
    HFONT refFont = get_jig_start_menu_font();
    SendMessage(hLabelJigID, WM_SETFONT, (WPARAM)refFont, TRUE);
    SendMessage(hComboBoxJigID, WM_SETFONT, (WPARAM)refFont, TRUE);
    
    // Populate the combo box with existing Jig IDs
    update_jig_id_combo_box(hwnd);

    // update the default selected jig
    update_selected_jig_id(hwnd);
}

void update_jig_id_combo_box(HWND hwnd) {
    // Clear the existing items in the combo box and clear the combo box
    SendMessage(hComboBoxJigID, CB_RESETCONTENT, 0, 0);
     
    // sort the vector first alphabetically
    std::sort(jigIDs.begin(), jigIDs.end());

    // Add the items from the jigIDs vector to the combo box
    for (size_t i = 0; i < jigIDs.size(); ++i) {
        const auto& jigID = jigIDs[i];
        SendMessage(hComboBoxJigID, CB_ADDSTRING, 0, (LPARAM)jigID.c_str());
        // Optionally, you can use the index 'i' here if you want to do something with it
        // For example, you could set item data: SendMessage(hComboBoxJigID, CB_SETITEMDATA, i, (LPARAM)i);
    }
    
    // Optionally, set the first item as selected
    if (!jigIDs.empty()) {
        SendMessage(hComboBoxJigID, CB_SETCURSEL, 0, 0);
    }
    update_selected_jig_id(hwnd);
}

void update_selected_jig_id(HWND hwnd)
{
    // Get the selected item index from the combo box
    int selectedIndex = static_cast<int>(SendMessage(hComboBoxJigID, CB_GETCURSEL, 0, 0));

    // If no item is selected, clear currentJigID
    if (selectedIndex == CB_ERR) {
        currentJigID = "";
        return;
    }

    // Get the length of the selected item
    int length = static_cast<int>(SendMessage(hComboBoxJigID, CB_GETLBTEXTLEN, selectedIndex, 0));
    if (length == 0) {
        currentJigID = "";
        return;
    }

    // Create a buffer to hold the selected item text
    std::wstring buffer(length, L'\0');
    SendMessage(hComboBoxJigID, CB_GETLBTEXT, selectedIndex, (LPARAM)buffer.data());

    // Convert the wstring to string and update currentJigID
    currentJigID = std::string(buffer.begin(), buffer.end());
}

const std::string& get_selected_jig_id(HWND hwnd)
{
    return currentJigID;
}
