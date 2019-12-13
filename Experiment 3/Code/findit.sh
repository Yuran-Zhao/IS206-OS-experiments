#!/bin/bash

if [ $# -lt 1 ] 
then
	echo "Please enter at least one string as a serch parameter!"
	exit
fi

if [ $# -gt 2 ]
then
	echo "Enter up to two strings!"
	exit
fi

if [ $# -eq 1 ]
then
	path=./
	searching=$1
else
	path=$1
	searching=$2
fi

# for testing
# echo $path
# echo $searching

find $path -name "*.[ch]" -exec grep -Hn $searching {} \;

