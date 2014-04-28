#!/bin/bash

function exit_with_error(){
	echo "*** Failed! ";
	exit 1;
}

function show_help(){
	echo "Usage: "
	echo -e "\t" $0 "filename"
	echo
	echo "Note: filename is the c file (without extension) you want to compile and link"
}

NAME='db_wrapper'

if [ "$#" -lt 1 ]; then
	show_help
	exit_with_error
fi

if [ ! -f $NAME.o ]; then
	echo "File" $NAME.o "Does not exist in current directory."
	exit_with_error
fi


echo "*** Creating object code for $1..."
gcc -std=c99 -c $1.c -o $1.o && echo "*** Sucess!" || exit_with_error

echo "*** Linking object code..."
gcc $NAME.o $1.o -o $1 -I /usr/include/postgresql -L /usr/lib/postgresql/9.3/lib -lecpg && \
echo "*** Executable generated!" || exit_with_error
