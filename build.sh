#!/bin/bash

function exit_with_error(){
	echo "*** Failed! ";
	exit 1;
}

NAME='db_wrapper'

if [ ! -f $NAME.c ]; then
	echo "File" $NAME.c "Does not exist in current directory."
	exit_with_error
fi

echo "*** Preprocessing SQL "
ecpg -o _$NAME.c $NAME.c && echo "*** Sucess!" || exit_with_error

echo "*** Building object code..."
cc -I /usr/include/postgresql  -c _$NAME.c -o $NAME.o -L /usr/lib/postgresql/9.3/lib  && \
echo "*** '$NAME.o' Generated!" || exit_with_error

