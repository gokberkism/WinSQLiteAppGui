#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include "MsgLogListView.h"

bool fMsgLogLV_ColumnNamesWrite(void){
            // this is not data, only name of each header we like
            memset(&LvMsgLogCol,0,sizeof(LvMsgLogCol));                  // Zero Members
            LvMsgLogCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;    // Type of mask
            LvMsgLogCol.fmt = LVS_EX_GRIDLINES | LVCFMT_CENTER;
            LvMsgLogCol.cx=0x28;                                   // width between each coloumn
            LvMsgLogCol.pszText=  (LPSTR) "Date&Time";                            // First Header Text
            LvMsgLogCol.cx= 130;//0x52;                                   // width of column

            SendMessage(hListViewMsgLog,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT); // Set style
            // Inserting Couloms as much as we want
            SendMessage(hListViewMsgLog,LVM_INSERTCOLUMN,0,(LPARAM)&LvMsgLogCol); // Insert/Show the column

            LvMsgLogCol.cx= 610;//0xF2;                                   // width of column
            LvMsgLogCol.pszText= (LPSTR) "Event Message";                            // Next coloum
            SendMessage(hListViewMsgLog,LVM_INSERTCOLUMN,1,(LPARAM)&LvMsgLogCol); // ...

           return TRUE;
        }
bool fMsgLogLV_ColumnItemValWrite(void){

            char szMsgLog[800]="";
             SYSTEMTIME stime = {0};
             GetLocalTime(&stime);
             sprintf(szEventDadeTime,"%02d:%02d:%03d %02d/%02d/%03d",
                     stime.wHour,stime.wMinute,stime.wMilliseconds,stime.wDay,stime.wMonth,stime.wYear );

            memset(&LvMsgLogItem,0,sizeof(LvMsgLogItem)); // Zero struct's Members
           //  Setting properties Of members:
            LvMsgLogItem.mask=LVIF_TEXT;   // Text Style
            LvMsgLogItem.cchTextMax = 256; // Max size of test
            LvMsgLogItem.iItem=0;          // choose item
            LvMsgLogItem.iSubItem=0;       // Put in first coluom
            LvMsgLogItem.pszText= (LPSTR) szEventDadeTime;//"bugunn su saat"; // Text to display (can be from a char variable) (Items)

            SendMessage(hListViewMsgLog,LVM_INSERTITEM,0,(LPARAM)&LvMsgLogItem); // Send info to the Listview
            LvMsgLogItem.iSubItem=1;
            LvMsgLogItem.pszText= (LPSTR) szCharEventMsg;//"Hata var ve benim hatam...Halledecem!";
            SendMessage(hListViewMsgLog,LVM_SETITEM,0,(LPARAM)&LvMsgLogItem); // Enter text to SubItems
            FILE *fp = fopen("./MsgLog.txt", "a+");//const char *filename,const char *mode
            sprintf(szMsgLog,"%s  %s\n",szEventDadeTime,szCharEventMsg);
            fwrite(szMsgLog,sizeof(char),strlen(szMsgLog)+1,fp);
            fclose(fp);
        return TRUE;
}
