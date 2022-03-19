#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif
#include "sqlite3.h"
BOOL DLL_EXPORT SomeFunction(const LPCSTR sometext, int iVal);

#ifdef __cplusplus
}
#endif

int iCount =0;
 const int ID_TIMER = 1;
 HWND hwnd;
 PAINTSTRUCT ps;
 HDC hdc;

 HMENU hMenuDb, hSubMenuDb;
 HMENU hMenu, hSubMenu;
 HICON hIcon, hIconSm;

 HFONT hfDefault;
// HWND hEdit;
 HWND hEdit2;
 HWND hEdit3;
 HWND hStatic1;
 HWND hStatic2;
 HWND hStatic3;
 HWND hStatic4;
 HWND hButton;
 HWND hButton2;
 //HWND hListBox;
 HWND hListView;
 HWND hListViewMsgLog;

LVITEM LvItem;
LVCOLUMN LvCol;

LVITEM LvMsgLogItem;
LVCOLUMN LvMsgLogCol;
int iValEnt = 0;
char szCharEnt [50];
char szCharEventMsg [700];
char szEventDadeTime[30]="";
char szSqlQuery[500];
char szSqlColumnName[20]="";




char *zErrMsg = 0;
sqlite3 *db;
int rc;
char szErrText[50];
char *sql;
char szDBNamePath[50]="";

bool bLVColNamesOk = FALSE;
int iSQLColCount = 0;
int iRecSetCount = 0;
char szItemVals[100][100][50];
char szColNames[20][50];

void fMainMenuCreateShow(HWND hwnd);
void fMainWndControlAddShow(HWND hwnd);

bool fMsgLogLV_ColumnNamesWrite(void);
bool fMsgLogLV_ColumnItemValWrite(void);

bool fLV_ColumnNamesWrite(void);
bool fLV_ColumnItemValWrite(void);
void fRDrwListView(void);

int OpenDb(void);
int SQLiteDoQuery(void);
void CloseDb(void);
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
/*  Make the class name into a global variable  */


#endif // __MAIN_H__
