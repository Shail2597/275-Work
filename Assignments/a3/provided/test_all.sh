#!/bin/bash
# Complete testing script for A3: sequences, maze, writeval
# Run from: ~/275/275-Work/Assignments/a3/provided/

set -e
echo "========================================"
echo "  A3 Complete Testing Script"
echo "========================================"

########################################
# Q1 - SEQUENCES
########################################
echo ""
echo "======== Q1: SEQUENCES ========"
cd /home/shail/275/275-Work/Assignments/a3/provided/q1

# Make sample executable
chmod +x sequences_sample runTests

# Generate expected .out files from prof's sample
for t in test1 test2 test3 test4; do
    ./sequences_sample $(cat "$t.args") < "$t.in" > "$t.out"
done
echo "Generated .out files from sequences_sample"

# Create suite file
printf 'test1\ntest2\ntest3\ntest4\n' > suite.txt

# Compile your code
gcc -o sequences sequences.c
echo "Compiled sequences.c"

# Run tests
echo "--- Running tests ---"
./runTests ./sequences suite.txt

########################################
# Q2 - MAZE
########################################
echo ""
echo "======== Q2: MAZE ========"
cd /home/shail/275/275-Work/Assignments/a3/provided/q2

# Make sample executable
chmod +x mazeSample runTests

# Generate expected .out files from prof's sample
# Maze doesn't use .args, so create empty ones
for t in test1 test2 test3 simpletest; do
    touch "$t.args"
    ./mazeSample < "$t.in" > "$t.out"
done
echo "Generated .out files from mazeSample"

# Create suite file
printf 'test1\ntest2\ntest3\nsimpletest\n' > suite.txt

# Compile your code
gcc -o maze main.c maze.c
echo "Compiled maze"

# Run tests
echo "--- Running tests ---"
./runTests ./maze suite.txt

########################################
# Q4 - WRITEVAL
########################################
echo ""
echo "======== Q4: WRITEVAL ========"
cd /home/shail/275/275-Work/Assignments/a3/provided/q4

# Make sample executable
chmod +x writeValSample runTests

# Generate expected .out files from prof's sample
# Create empty .args if needed
touch test1.args
./writeValSample < test1.in > test1.out
echo "Generated .out files from writeValSample"

# Create suite file
printf 'test1\n' > suite.txt

# Compile your code
gcc -o writeval harness.c writeval.c raw.c
echo "Compiled writeval"

# Run tests
echo "--- Running tests ---"
./runTests ./writeval suite.txt

########################################
echo ""
echo "========================================"
echo "  All tests complete!"
echo "========================================"
