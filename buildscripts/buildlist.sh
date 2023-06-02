#!/bin/bash
path="/home/jake/uni/2337 Advanded Programming Techniques/apta1"
outfile="$path/x.out"
if [ -f  "$outfile" ]; then
	echo "$oufile exists"
	rm -rv "$outfile"
fi

# rm -rv "$path/buildscripts/main.out"

echo "Building..."
g++ -Wall -Werror -std=c++14 -O -o "$outfile" "$path/main.cpp" "$path/Node.cpp" "$path/NodeList.cpp"

if [ $? == 1 ]; then
	echo "There was an error during build."
else
	echo "Build complete."
fi
