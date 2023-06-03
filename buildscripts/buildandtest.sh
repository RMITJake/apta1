#!/bin/bash
# files paths
path="/home/jake/uni/2337 Advanded Programming Techniques/apta1"
tests="$path/test"
outfile="$path/assign1.out"

# file names
main="$path/main.cpp"
node="$path/Node.cpp"
list="$path/NodeList.cpp"
solv="$path/PathSolver.cpp"

if [ -f  "$outfile" ]; then
        echo "$oufile exists"
        echo "#==================================#"
        echo "#  assign1.out exists, removing.   #"
        echo "#==================================#"
        rm -rv "$outfile"
fi

echo "#==================================#"
echo "#           Building....           #"
echo "#==================================#"
g++ -Wall -Werror -std=c++14 -O -o "$outfile" "$main" "$node" "$list" "$solv"

if [ $? == 1 ]; then
        echo "#==================================#"
        echo "# There was an error during build. #"
        echo "#==================================#"
else
        echo "#==================================#"
        echo "#         Build complete.          #"
        echo "#==================================#"
        "$outfile" < "$path/sampleTest/sample01.env"
fi

echo "#==================================#"
echo "#            Testing....           #"
echo "#==================================#"
echo "# Running test1" | tee "$tests/tests.out"
"$outfile" < "$tests/test1.env" | tee -a "$tests/tests.out"

echo "# Running test2" | tee -a "$tests/tests.out"
"$outfile" < "$tests/test2.env" | tee -a "$tests/tests.out"
