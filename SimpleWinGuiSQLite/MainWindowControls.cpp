#include <windows.h>
#include <commctrl.h>
#include "resource.h"

#include "MainWindowControls.h"

void fMainMenuCreateShow(HWND hwnd){
            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&File");

            hSubMenuDb = CreatePopupMenu();
            AppendMenu(hSubMenuDb, MF_STRING, ID_CONFIGURE_DB, "C&Onfigure DB");
            AppendMenu(hSubMenuDb, MF_STRING, ID_CONNECT_DB, "&Connect");
            AppendMenu(hSubMenuDb, MF_STRING, ID_QUERRY_DB, "&Querry");
            AppendMenu(hSubMenuDb, MF_STRING, ID_GIVETABLES_DB, "Get List of TABLES");
            AppendMenu(hSubMenuDb, MF_STRING, ID_GIVECOLUMNS_DB, "Get List of COLUMNS");
            AppendMenu(hSubMenuDb, MF_STRING, ID_CLOSE_DB, "&Close");
            AppendMenu(hSubMenuDb, MF_STRING, ID_ADDMATERIAL_DB, "ADD MATERIAL");
            AppendMenu(hSubMenuDb, MF_STRING, ID_ADDSUPPLIER_DB, "ADD SUPPLIER");
            AppendMenu(hSubMenuDb, MF_STRING, ID_ADDEMPLOYEE_DB, "ADD EMPLOYEE");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenuDb, "&Database");

            EnableMenuItem(hSubMenuDb, (UINT)  ID_QUERRY_DB, MF_DISABLED);
            EnableMenuItem(hSubMenuDb, (UINT)  ID_CLOSE_DB, MF_DISABLED);
            EnableMenuItem(hSubMenuDb, (UINT)  ID_CONNECT_DB, MF_DISABLED);
            EnableMenuItem(hSubMenuDb, (UINT)  ID_CONFIGURE_DB, MF_ENABLED);

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_DEL_DB_REPVIEWTEMS_LV, "Delete DB Report View");
            AppendMenu(hSubMenu, MF_STRING, ID_DEL_MSG_LOG_ITEMS_LV, "Delete Operation Messages");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "Simple Stuf ");
            SetMenu(hwnd, hMenu);
}
void    fMainWndControlAddShow(HWND hwnd){
            hIcon = (HICON)LoadImage(NULL, "Slideshow.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
            if(hIcon)
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
            else
                MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);

            hIconSm = (HICON) LoadImage(NULL, "Slideshow_sm.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            if(hIconSm)
                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
            else
                MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);

             //creating an EDIT control
      /*      hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                WS_CHILD | WS_VISIBLE | WS_VSCROLL |  ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL ,
                0, 50, 100, 50, hwnd, (HMENU)IDC_MAIN_EDIT,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            if(hEdit == NULL)
                MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
        */
             //creating an EDIT controls
            hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                WS_CHILD | WS_VISIBLE | WS_HSCROLL  | ES_CENTER ,
                220, 10, 550, 45, hwnd, (HMENU)IDC_INTEGER_EDIT,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            if(hEdit2 == NULL)
                MessageBox(hwnd, "Could not create Integer Edit box.", "Error", MB_OK | MB_ICONERROR);
            hfDefault = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hEdit2, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));

            hEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                220, 70, 550,100, hwnd, (HMENU)IDC_CHARSTRING_EDIT,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

            hStatic1 = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                120, 10,90,20, hwnd, (HMENU)IDC_LBLDBNAME_STC,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hStatic1, "DataBase:");
            hStatic2 = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                120, 70,90,20, hwnd, (HMENU)IDC_LBLQRY_STC,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hStatic2, "SQL Query:");
            hStatic3 = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                90, 150,120,20, hwnd, (HMENU)IDC_LBLQRYRES_STC,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hStatic3, "DB Query Result:");
            hStatic4 = CreateWindowEx(WS_EX_CLIENTEDGE, "Static", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                80, 378,120,20, hwnd, (HMENU)IDC_LBLLOGMSG_STC,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hStatic4, "Operation LOG:");

            hButton = CreateWindowEx(WS_EX_CLIENTEDGE, "button", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                30, 150,40,20, hwnd, (HMENU)IDC_CLRQRYRES_BTN,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hButton, "CLR");

            hButton2 = CreateWindowEx(WS_EX_CLIENTEDGE, "button", "",
                WS_CHILD | WS_VISIBLE | ES_LEFT ,
                30, 378,40,20, hwnd, (HMENU)IDC_CLRLOGMSG_BTN,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SetWindowText(hButton2, "CLR");

            if(hEdit3 == NULL)
                MessageBox(hwnd, "Could not create Integer Edit box.", "Error", MB_OK | MB_ICONERROR);
            hfDefault = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hEdit3, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));

            HFONT hFont = CreateFont (20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
                  OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                  DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
             SendMessage(hEdit3, WM_SETFONT, (WPARAM) hFont, TRUE);

                    //creating an ListBox control
      /*      hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", "",
                WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |  ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL ,
                0, 110, 70, 50, hwnd, (HMENU)IDC_MAIN_LISTBOX,(HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            if(hListBox == NULL)
                MessageBox(hwnd, "Could not create ListBox.", "Error", MB_OK | MB_ICONERROR);

            hfDefault = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hListBox, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
            */
            hListView = CreateWindow(WC_LISTVIEW,
                                         (LPCSTR) "gdg",
                                         WS_CHILD | WS_VISIBLE | WS_HSCROLL |  WS_VSCROLL  | LVS_REPORT | LVS_EDITLABELS,
                                         30, 180,
                                         740,
                                         190,
                                         hwnd,
                                         (HMENU)IDC_MAIN_LISTVIEW,
                                         (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                         NULL);
           hListViewMsgLog = CreateWindow(WC_LISTVIEW,
                                         (LPCSTR) "gdgMsg",
                                         WS_CHILD | WS_VISIBLE | WS_HSCROLL |  WS_VSCROLL  | LVS_REPORT | LVS_EDITLABELS,
                                         30, 400,
                                         740,
                                         130,
                                         hwnd,
                                         (HMENU)IDC_LOGMSG_LISTVIEW,
                                         (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                                         NULL);
}

