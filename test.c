#include "stdio.h"
#include "db_wrapper.h"

int main(){

	if(db_connect("humberto", "humberto", "asdasd")){
		printf("%s\n", "Failed to connect to database");
	}
	test *t = select_test_by_id(2);
	printf("Test name: %s, email: %s\n", t->name, t->email);
	return 0;
}