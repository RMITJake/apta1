#!/bin/bash
clear;
path="/home/jake/uni/2337 Advanded Programming Techniques/apta1"
infile="$path/assign1.out"
testcases="$path/test"
testout="$testcases/tests.out"

files=( "test1"
				"test2"
				"test3"
				"test4"
				"test5"
				"test6"
				"test7"
				"test8"
				"test9"
				"test10")

if [ ! -f  "$infile" ]; then
	echo "$infile exists"
	echo "#==================================#"
	echo "#    assign1.out does not exist    #"
	echo "#==================================#"
else
	echo "#==================================#"
	echo "#            Testing....           #"
	echo "#==================================#"

	if [ -f "$testout" ]; then
		echo "# Removing tests.out....           #"
		rm "$testout"
	fi

	for testcase in ${files[@]}; do
		echo "$testcase.env" | tee -a "$testout"
		"$infile" < "$testcases/$testcase.env" | tee -a "$testout"
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
