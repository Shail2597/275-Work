#!/bin/bash
# Complete testing script for A3: sequences, maze, writeval
# Run from: ~/275-Work/Assignments/a3/provided/

BASEDIR="$(cd "$(dirname "$0")" && pwd)"

set -e
echo "========================================"
echo "  A3 Complete Testing Script"
echo "========================================"

########################################
# Q1 - SEQUENCES
########################################
echo ""
echo "======== Q1: SEQUENCES ========"
cd "$BASEDIR/q1"

chmod +x sequences_sample runTests

for t in test1 test2 test3 test4; do
    ./sequences_sample $(cat "$t.args") < "$t.in" > "$t.out"
done
echo "Generated .out files from sequences_sample"

printf 'test1\ntest2\ntest3\ntest4\n' > suite.txt

gcc -o sequences sequences.c
echo "Compiled sequences.c"

echo "--- Running tests ---"
./runTests ./sequences suite.txt

########################################
# Q2 - MAZE
########################################
echo ""
echo "======== Q2: MAZE ========"
cd "$BASEDIR/q2"

chmod +x mazeSample runTests

for t in test1 test2 test3 simpletest; do
    touch "$t.args"
    ./mazeSample < "$t.in" > "$t.out"
done
echo "Generated .out files from mazeSample"

printf 'test1\ntest2\ntest3\nsimpletest\n' > suite.txt

gcc -o maze main.c maze.c
echo "Compiled maze"

echo "--- Running tests ---"
./runTests ./maze suite.txt

########################################
# Q4 - WRITEVAL
########################################
echo ""
echo "======== Q4: WRITEVAL ========"
cd "$BASEDIR/q4"

chmod +x writeValSample runTests

touch test1.args
./writeValSample < test1.in > test1.out
echo "Generated .out files from writeValSample"

printf 'test1\n' > suite.txt

gcc -o writeVal harness.c writeVal.c raw.c
echo "Compiled writeVal"

echo "--- Running tests ---"
./runTests ./writeVal suite.txt

########################################
echo ""
echo "========================================"
echo "  All tests complete!"
echo "========================================"
