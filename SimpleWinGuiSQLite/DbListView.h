#ifndef DBLISTVIEW_H_INCLUDED
#define DBLISTVIEW_H_INCLUDED


extern LVITEM LvItem;
extern LVCOLUMN LvCol;
extern const char* data;
extern bool bLVColNamesOk;
extern int iSQLColCount;
extern int iRecSetCount;
extern char szItemVals[100][100][50];
extern char szColNames[20][50];

extern HWND hwnd;
extern HWND hListView;
//extern (HMENU)IDC_MAIN_LISTVIEW;
extern bool fLV_ColumnNamesWrite(void);
extern bool fLV_ColumnItemValWrite(void);

void fRDrwListView(void);

#endif // DBLISTVIEW_H_INCLUDED
