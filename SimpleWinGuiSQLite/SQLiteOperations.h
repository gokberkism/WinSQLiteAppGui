#ifndef SQLITEOPERATIONS_H_INCLUDED
#define SQLITEOPERATIONS_H_INCLUDED

extern "C" {
#include "sqlite3.h"
}

//const char* data = "Callback function called";
extern sqlite3 *db;
extern int rc;
extern int iSQLColCount;
extern int iRecSetCount;
extern bool bLVColNamesOk;
extern char szColNames[20][50];
extern char szItemVals[100][100][50];
extern char *zErrMsg;
extern char szDBNamePath[50];
extern char szSqlQuery[500];
extern char szSqlColumnName[20];

//int OpenDb(char szDBNamePath, sqlite3 *db);
int SQliteOpenDb(void);
//int SQLiteDoQuery(sqlite3 *db,(void*)data, char **errmsg );
int SQLiteDbQuery(void);
void SQliteCloseDb(void);
void SQliteDbQueryError (void);
static int callback( void *data, int argc, char **argv, char **azColName);
#endif // SQLITEOPERATIONS_H_INCLUDED
