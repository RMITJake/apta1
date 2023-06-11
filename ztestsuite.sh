#!/bin/bash
clear;
path="/home/jake/uni/2337 Advanded Programming Techniques/apta1"
infile="$path/assign1.out"
testcases="$path/test"

files=( "test1"
				"test2"
				"test3"
				"test4"
				"test5"
				"test6")

if [ ! -f  "$infile" ]; then
	echo "$infile exists"
	echo "#==================================#"
	echo "#    assign1.out does not exist    #"
	echo "#==================================#"
else
	echo "#==================================#"
	echo "#            Testing....           #"
	echo "#==================================#"

	for testcase in ${files[@]}; do
		"$infile" < "$testcases/$testcase.env" >> "$testcases/tests.out"
	done

	if [ $? == 1 ]; then
		echo "#==================================#"
		echo "#  There was an error during test  #"
		echo "#==================================#"
	else
		echo "#==================================#"
		echo "#        Testing complete.         #"
		echo "#==================================#"
	fi
fi
