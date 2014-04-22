#include <stdlib.h>
#include "tools.h"
#define ASSERT(ptr)	if(sqlca.sqlcode != 0){free(ptr);ptr=NULL;}

EXEC SQL INCLUDE sqlca;

EXEC SQL BEGIN DECLARE SECTION;
EXEC SQL INCLUDE model.h;
EXEC SQL END DECLARE SECTION;

int db_connect(char *db_name, char *db_user, char *db_pswd){
	EXEC SQL BEGIN DECLARE SECTION;
	char *SQL_bd_name;
	char *SQL_bd_user;
	char *SQL_bd_passwd;
	EXEC SQL END DECLARE SECTION;
	_STRING_COPY(SQL_bd_name, db_name);
	_STRING_COPY(SQL_bd_user, db_user);
	_STRING_COPY(SQL_bd_passwd, db_pswd);
	//EXEC SQL CONNECT TO :SQL_bd_name USER :SQL_bd_user IDENTIFIED BY :SQL_bd_passwd;
	EXEC SQL CONNECT TO :SQL_bd_name;
	return sqlca.sqlcode;
}

void db_close(){
	EXEC SQL DISCONNECT ALL;
}

void db_commit(){
	EXEC SQL COMMIT;
}

test * select_test_by_id(int id){
	EXEC SQL BEGIN DECLARE SECTION;
	test *SQL_output;
	int SQL_id;
	EXEC SQL END DECLARE SECTION;

	SQL_id = id;
	SQL_output = (test*) malloc(sizeof(test));
	memset(SQL_output, 0, sizeof(test));

	EXEC SQL SELECT id, name, email INTO 
	:SQL_output->id, :SQL_output->name, :SQL_output->email FROM test WHERE test.id = :SQL_id;

	ASSERT(SQL_output);
	return SQL_output;
}