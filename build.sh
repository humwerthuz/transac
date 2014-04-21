#!/bin/bash
NAME='db_wrapper'
export LD_LIBRARY_PATH=/usr/pgsql-9.0/lib
echo "*** Preprocessing SQL "
ecpg -o _$NAME.c $NAME.c
echo "*** Building object code..."
cc -I /usr/include/postgresql  -c _$NAME.c -o $NAME.o -L /usr/lib/postgresql/9.3/lib
echo "*** '$NAME.o' Generated!"
