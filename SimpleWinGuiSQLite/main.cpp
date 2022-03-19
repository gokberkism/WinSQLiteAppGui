#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif


#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <commctrl.h>
#include "resource.h"
#include "main.h"
#include "DbListView.h"
#include "MainWindowControls.h"
#include "MsgLogListView.h"
#include "SQLiteOperations.h"

extern "C" {
#include "sqlite3.h"
}
#define DllImport __declspec( dllimport )

HINSTANCE hInst;                                // current instance
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
TCHAR szChkMessage[ ] = _T("mouse double klik yaptin");
TCHAR szUyariMsgTitle[ ] = _T("UYARI");


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
                   /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    hInst = hThisInstance;
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
   // wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
   // wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

    wincl.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wincl.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);

    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  //  wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_CLIENTEDGE,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Sample Windows App for SQLite, Windows Controls, Windows Messages etc..."),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
                return 0;
    }
    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
     int ret=0;

            ret = (int) SetTimer(hwnd, ID_TIMER, 4000, (TIMERPROC) NULL);
            if(ret == 0)
                MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    char szText[50];

    switch (message)                  /* handle the messages */
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            if(hdc == NULL)
                MessageBox(hwnd, "BeginPaint hdc olusturamadi!", "Bildirim",MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2 );
            EndPaint(hwnd, &ps);
            DeleteDC(hdc);
            break;
        case WM_CREATE:
        {
            fMainMenuCreateShow(hwnd);
            fMainWndControlAddShow(hwnd);
            fMsgLogLV_ColumnNamesWrite();//Log Message List View Control initialization
        }
        break;
        case WM_SIZE:
        {

        }
        break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_FILE_EXIT:
                    sprintf(szCharEventMsg,"%s","Programdan Cikis Istegi Yapildi. Cikiliyor!");
                    SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                   PostMessage(hwnd, WM_CLOSE, 0, 0);
                break;
                case ID_CONNECT_DB:
                        rc = SQLITE_OK;
                        rc =SQliteOpenDb();
                  //   rc = sqlite3_open(szDBNamePath, &db);
                    if( rc ){
                        SQliteDbQueryError();
                        sprintf(szCharEventMsg,"Can't open database: %s", zErrMsg);
                        SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                 //      sprintf(szErrText, "Can't open database: %s\n", sqlite3_errmsg(db));
                //        MessageBox(hwnd, szErrText, "Database Op Bildirimi", MB_OK | MB_ICONERROR);
                       EnableMenuItem(hSubMenuDb, (UINT)  ID_CONNECT_DB,MF_ENABLED);
                       //return(0);
                    }
                    else {//DB Opened
                        sprintf(szCharEventMsg,"Database Opened and connected:%s",szDBNamePath);
                        SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);

                        EnableMenuItem(hSubMenuDb, (UINT)  ID_CONNECT_DB,MF_DISABLED);
                        EnableMenuItem(hSubMenuDb, (UINT)  ID_QUERRY_DB,MF_ENABLED);
                        EnableMenuItem(hSubMenuDb, (UINT)  ID_CLOSE_DB,MF_ENABLED);
                        EnableMenuItem(hSubMenuDb, (UINT)  ID_CONFIGURE_DB,MF_DISABLED);
                       }
                   break;
                case ID_QUERRY_DB://If DB Opened
                        bLVColNamesOk = FALSE;
                       /* Create SQL statement */
                        GetWindowText(hEdit3,szSqlQuery,GetWindowTextLength(hEdit3)+1);
                  //     fprintf(stderr,"Querry:%d", GetWindowTextLength(hEdit3)+1);
                       // sql = "SELECT * FROM MATERIALDEFS";
                      //  MessageBox(hwnd,   szMstr, "BILGI", MB_OK | MB_ICONERROR);

                        /* Execute SQL statement */
                       iSQLColCount = 0; iRecSetCount = 0;
                        rc = SQLITE_OK;
                        rc = SQLiteDbQuery();
                       // rc = sqlite3_exec(db, szSqlQuery, callback, (void*)data, &zErrMsg);

                        if( (rc != SQLITE_OK) || GetWindowTextLength(hEdit3) <=1 ) {
                            SQliteDbQueryError();
                            sprintf(szCharEventMsg,"SQL Query has beend applied. Error: %s : SQL Query:%s",zErrMsg, szSqlQuery);
                            SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                            sqlite3_free(zErrMsg);
                            }
                       else {
                            sprintf(szCharEventMsg,"SQL Querry has been Executed: SQL Query:%s",szSqlQuery);
                            SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                            }

                        //Redraw ListView Control to initialize all columns!
                        if(iRecSetCount >0)
                                fRDrwListView();
                 break;
                case ID_CLOSE_DB:
                    SQliteCloseDb();
                  //  sqlite3_close(db);
                    sprintf(szCharEventMsg,"Database has been CLOSED: %s",szDBNamePath);
                    SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);

                    EnableMenuItem(hSubMenuDb, (UINT)  ID_CONNECT_DB, MF_ENABLED);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_QUERRY_DB,  MF_DISABLED);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_CLOSE_DB,  MF_DISABLED);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_CONFIGURE_DB,  MF_ENABLED);
                 break;
               case ID_CONFIGURE_DB:
                    sprintf(szDBNamePath,"%s", "mySIODB.s3db");
              //      sprintf(szDBNamePath,"%s", "D:\\SIODB\\mySIODB.s3db");
                   SetWindowText(hEdit2, szDBNamePath);
                    EnableWindow(hEdit2, FALSE);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_CONNECT_DB, MF_ENABLED);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_QUERRY_DB,  MF_DISABLED);
                    EnableMenuItem(hSubMenuDb, (UINT)  ID_CLOSE_DB,  MF_DISABLED);
                  break;
               case ID_ADDMATERIAL_DB:
                     sprintf(szSqlQuery,"%s","INSERT INTO MATERIALDEFS VALUES( 'GYM13272', 'ADT','ADIDAS SPAIR 027346',1380,6,15 )");
                  //   sprintf(szSqlQuery,"CREATE TABLE t(x INTEGER, y CHAR(30) UNIQUE NOT NULL , z INTEGER  NOT NULL, PRIMARY KEY(x DESC))");
                 //   rc = sqlite3_exec(db, szSqlQuery, NULL, NULL, &zErrMsg);

                    if (rc != SQLITE_OK){
                        sprintf(szCharEventMsg,"SQL Query has beend applied. Error: %s : SQL Query:%s",zErrMsg, szSqlQuery);
                        SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                        }
                    else {
                        sprintf(szCharEventMsg,"SQL Query has beend applied. SQL Query:%s",szSqlQuery);
                        SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                        }
                     break;
               case ID_GIVETABLES_DB:
                       //Lists of tables in a SQLite Database
                       sprintf(szSqlQuery,"SELECT name FROM sqlite_master WHERE type='table'");

                        iSQLColCount = 0; iRecSetCount = 0;
                        rc = SQLITE_OK;
                        rc = SQLiteDbQuery();
                   //     rc = sqlite3_exec(db, szSqlQuery, callback, (void*)data, &zErrMsg);
                        fRDrwListView();
                   break;
               case ID_GIVECOLUMNS_DB:
                       //List of Columns of a SQLite Database's Table
                       GetWindowText(hEdit3,szSqlColumnName,GetWindowTextLength(hEdit3)+1);
                       sprintf(szSqlQuery, "PRAGMA table_info(%s)",szSqlColumnName);
                       iSQLColCount = 0; iRecSetCount = 0;
                        rc = SQLITE_OK;
                        rc = SQLiteDbQuery();
               //         rc = sqlite3_exec(db, szSqlQuery, callback, (void*)data, &zErrMsg);
                        fRDrwListView();
                    break;
               case ID_DEL_DB_REPVIEWTEMS_LV :
                   SendMessage(hListView,LVM_DELETEALLITEMS,0,0);
                    break;
                case IDC_CLRQRYRES_BTN :
                  SendMessage(hListView,LVM_DELETEALLITEMS,0,0);
                    break;
               case ID_DEL_MSG_LOG_ITEMS_LV :
                    SendMessage(hListViewMsgLog,LVM_DELETEALLITEMS,0,0);
                    break;
                 case IDC_CLRLOGMSG_BTN :
                   SendMessage(hListViewMsgLog,LVM_DELETEALLITEMS,0,0);
                    break;
               case ID_KOVAN_STOK:
                      // void (*ptr)() = &my_function;
                      // my_callback_function(ptr);
                       break;
                case ID_KOVAN_BAKIM:
                    SendMessage(hListView,LVM_DELETEALLITEMS,0,0);
                    remove("./MsgLog.txt");
                    sprintf(szCharEventMsg,"%s","Event Logs and Log File has been deleted!");
                    SendMessage(hwnd,(UINT) WM_LOGMESSAGE_LV,0,0);
                    break;
            }
     //       if(( (HWND) lParam ==  hEdit2) && (HIWORD(wParam)== EN_CHANGE))
     //           MessageBox(hwnd, "Number Edit yapildi", "BILGI", MB_OK | MB_ICONERROR);
         break;
        case WM_LOGMESSAGE_LV:
                 fMsgLogLV_ColumnItemValWrite();//Log the Message

            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            KillTimer(hwnd,(UINT_PTR) ID_TIMER);
            break;
         case WM_LBUTTONDBLCLK:
                    //   xPos = GET_X_LPARAM(lParam);
                     //  yPos = GET_Y_LPARAM(lParam);
                     // cout<< "X:"<< xPos <<"  Y:"<<yPos;
               MessageBox(
                        NULL,
                         _T("mouse double klik yaptin sanirim"),//(LPCTSTR)szChkMessage,
                        (LPCTSTR) szUyariMsgTitle,
                        MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2
                        );
                break;
        case EN_CHANGE:
       //     MessageBox(hwnd, "Edit Box degisti...", "Note That", MB_OK | MB_ICONINFORMATION);
            break;
        case WM_TIMER:
        {
           iCount++;
           sprintf(szText,"Whales %d .hmkgh--afcfsdfsgsgsgs%dd54647745ur%dhfnht",iCount,iCount+1,iCount+2);
          //  MessageBox(hwnd, szText, "Bildirim Penceresi",MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2 );
  /*          SetWindowText(hEdit, szText);
            if(iCount%3 == 0){
                EnableWindow(hEdit, TRUE);
              //  SetFocus(hEdit);
                GetWindowTextA( hEdit,szText,5);
                //MessageBox(hwnd, szText, "Bildirim Penceresi",MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2 );
            }
            else
                EnableWindow(hEdit, FALSE);
*/
            if(iCount == 100) iCount =0;

        }
    break;
       default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {

                 MessageBox(
                        NULL,
                         _T("About Box icindeki Mesaj."),//(LPCTSTR)szChkMessage,
                        _T("About Box"),
                        MB_ICONWARNING | MB_DEFBUTTON2
                        );

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

