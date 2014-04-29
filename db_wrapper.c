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
	EXEC SQL CONNECT TO :SQL_bd_name USER :SQL_bd_user IDENTIFIED BY :SQL_bd_passwd;
//	EXEC SQL CONNECT TO :SQL_bd_name;
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

	SQL_output->SQL_CODE = 1;

	ASSERT(SQL_output);
	return SQL_output;
}


test * select_test_all(){
	EXEC SQL BEGIN DECLARE SECTION;
	test *SQL_output;
	int SQL_count;
	EXEC SQL END DECLARE SECTION;

	EXEC SQL SELECT COUNT(*) INTO :SQL_count FROM test;

	if(SQL_count == 0) return NULL;

	SQL_output = malloc(sizeof(test) * (SQL_count + 1));
	SQL_output[SQL_count].SQL_CODE = 0;

	EXEC SQL DECLARE RESULT_SET CURSOR FOR SELECT id, name, email
	FROM test ORDER BY test.id;
	EXEC SQL OPEN RESULT_SET;

	int resultset_pos = 0;

	while(!sqlca.sqlcode && resultset_pos < SQL_count){
		EXEC SQL FETCH NEXT FROM RESULT_SET INTO :SQL_output[resultset_pos].id,
		:SQL_output[resultset_pos].name, :SQL_output[resultset_pos].email;
		
		SQL_output[resultset_pos].SQL_CODE = 1;
		resultset_pos ++;
	}
	
	EXEC SQL CLOSE RESULT_SET;
	return SQL_output;
}
