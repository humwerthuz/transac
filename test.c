#include "stdio.h"
#include "db_wrapper.h"

int main(){

	if(db_connect("humberto", "humberto", "asdasd")){
		printf("%s\n", "Failed to connect to database");
		return 1;
	}
	
	test * temp;

	temp = select_test_by_id(1);
	printf("Test name: %s, email: %s\n", temp->name, temp->email);

	temp = select_test_all();

	for(int pos=0; temp[pos].SQL_CODE != 0; pos++){
		printf("Test name: %s, email: %s\n", temp[pos].name, temp[pos].email);
	}

	db_close();
	return 0;
}