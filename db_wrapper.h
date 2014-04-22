#ifndef _DB_WRAPPER_H
#define _DB_WRAPPER_H
#include "model.h"

int db_connect(char *db_name, char *db_user, char *db_pswd);
void db_close();
void db_commit();

test *  select_test_by_id(int);

#endif