#!/bin/bash
NAME='db_wrapper'
export LD_LIBRARY_PATH=/usr/pgsql-9.0/lib
echo "*** Creating object code for $1..."
cc -c $1.c -o $1.o
echo "*** Linking object code..."
cc $NAME.o $1.o -o $1 -I /usr/include/postgresql -L /usr/lib/postgresql/9.3/lib -lecpg
echo "*** Executable Generated!"
