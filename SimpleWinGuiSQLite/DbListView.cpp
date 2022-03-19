#include <windows.h>
#include <commctrl.h>
#include "resource.h"

#include "DbListView.h"


//Purpose: Assigning Header-Column Names of List View Control
//Arguments: Globally declared!
// IN:  hListView       : handled for List View Control HWND type
//      iSQLColCount    :Number of Columns in ListView ..item + number of subitem(s)    int type
//      azColName[iSQLCOlCount:20][50]: Column Name string vektor  20x50 char szColNames[20][50]
//      LvCol           : LVCOLUMN type variable for names columnns
 bool fLV_ColumnNamesWrite(void){
            int j =0;
            // Here we put the info on the Coulom headers
            // this is not data, only name of each header we like
            memset(&LvCol,0,sizeof(LvCol));                  // Zero Members
            LvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;    // Type of mask
            LvCol.cx=0x28;                                   // width between each coloumn
            LvCol.pszText=  szColNames[0];                            // First Header Text
            LvCol.cx= 0x42;                                   // width of column

            SendMessage(hListView,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT); // Set style
            // Inserting Couloms as much as we want
            SendMessage(hListView,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol); // Insert/Show the column
            for (j=1; j< iSQLColCount;j++){
                // Inserting Couloms as much as we want
                LvCol.pszText= szColNames[j];                            // Next column
                SendMessage(hListView,LVM_INSERTCOLUMN,j,(LPARAM)&LvCol); // ...
                }
           return TRUE;
}
//Purpose: Assigning value of items and subitems of List View Control's Columns
//Arguments: Globally declared!
// IN:  hListView       : handled for List View Control    HWND type
//      iRecSetCount    : Number of Record Set reurned from databse int type
//      iSQLColCount    :Number of Columns in ListView ..item + number of subitem(s)    int type
//      szItemVals[][]: Column Values Matrix char string matrix  20x50 char szItemVals[100][100][50];
//      LvItem           : LVITEM type variable for values of columnns
bool fLV_ColumnItemValWrite(void){
        int ii = 0;

        for (ii=0; ii < iRecSetCount;ii++){
            memset(&LvItem,0,sizeof(LvItem)); // Zero struct's Members
           //  Setting properties Of members:
            LvItem.mask=LVIF_TEXT;   // Text Style
            LvItem.cchTextMax = 256; // Max size of test
            LvItem.iItem=0;          // choose item
            LvItem.iSubItem=0;       // Put in first coluom
            LvItem.pszText= szItemVals[ii][0]; // Text to display (can be from a char variable) (Items)
            SendMessage(hListView,LVM_INSERTITEM,0,(LPARAM)&LvItem); // Send info to the Listview
             int i =0;
            for(i=1;i<iSQLColCount;i++) // Add SubItems in a loop
            {
               LvItem.iSubItem=i;
               LvItem.pszText=szItemVals[ii][i];
               SendMessage(hListView,LVM_SETITEM,0,(LPARAM)&LvItem); // Enter text to SubItems
                }
        }
        return TRUE;
    }
void fRDrwListView(void){
            DestroyWindow(hListView);
            hListView = CreateWindow(WC_LISTVIEW,
                    (LPCSTR) "gdg",
                    WS_CHILD | WS_VISIBLE | WS_HSCROLL |  WS_VSCROLL  | LVS_REPORT | LVS_EDITLABELS,
                    30, 180,
                    740,
                    200,
                    hwnd,
                    (HMENU)IDC_MAIN_LISTVIEW,
                    (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                    NULL);
            fLV_ColumnNamesWrite();
            SendMessage(hListView,LVM_DELETEALLITEMS,0,0);
            ListView_SetExtendedListViewStyleEx(hListView, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
            fLV_ColumnItemValWrite();
}
