#include <windows.h>
#include <stdio.h>
#include "SQLiteOperations.h"

extern "C" {
#include "sqlite3.h"
}

int SQliteOpenDb(void){
    rc =sqlite3_open(szDBNamePath, &db);
    return rc;
}
int SQLiteDbQuery(void){
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, szSqlQuery, callback, (void*)data, &zErrMsg);
    return rc;
}
void SQliteCloseDb(void){
    sqlite3_close(db);
    return;
}
void SQliteDbQueryError (void){
    sprintf(zErrMsg,"%s",sqlite3_errmsg(db));
    return;
}
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;

 //  fprintf(stderr, "%s: ", (const char*)data);
   iRecSetCount++;
   for(i = 0; i<argc; i++){
     // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      if(!bLVColNamesOk){
            sprintf(szColNames[i],"%s",azColName[i]);
            }
        sprintf(szItemVals[iRecSetCount-1][i],"%s",argv[i] ? argv[i] : "NULL");
        }
    iSQLColCount = argc;
    bLVColNamesOk = TRUE;

  // printf("\n");
   return 0;
}
