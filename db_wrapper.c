#include <stdlib.h>
#include "tools.h"
#define ASSERT(ptr)	if(sqlca.sqlcode != 0){free(ptr);ptr=NULL;}

EXEC SQL BEGIN DECLARE SECTION;
EXEC SQL INCLUDE model.h;
EXEC SQL END DECLARE SECTION;

int db_connect(char *db_name, char *db_user, char *db_pswd){
	EXEC SQL INCLUDE sqlca;
	EXEC SQL BEGIN DECLARE SECTION;
	char *bdd_name;
	char *bdd_user;
	char *bdd_passwd;
	EXEC SQL END DECLARE SECTION;
	_STRING_COPY(bdd_name, db_name);
	_STRING_COPY(bdd_user, db_user);
	_STRING_COPY(bdd_passwd, db_pswd);
	//EXEC SQL CONNECT TO :bdd_name USER :bdd_user IDENTIFIED BY :bdd_passwd;
	EXEC SQL CONNECT TO :bdd_name;
	return sqlca.sqlcode;
}

void db_close(){
	EXEC SQL DISCONNECT ALL;
}

void db_commit(){
	EXEC SQL COMMIT;
}

test * select_test_by_id(int _id){
	EXEC SQL BEGIN DECLARE SECTION;
	test *output;
	int id;
	EXEC SQL END DECLARE SECTION;
	id = _id;
	output = (test*) malloc(sizeof(test));
	memset(output, 0, sizeof(test));

	EXEC SQL SELECT id, name, email INTO 
	:output->id, :output->name, :output->email FROM test WHERE test.id = :id;

	ASSERT(output);
	return output;
}