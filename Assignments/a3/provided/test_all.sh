#!/bin/bash
# Complete testing script for A3: sequences, maze, writeval
# Run from: ~/275-Work/Assignments/a3/provided/

BASEDIR="$(cd "$(dirname "$0")" && pwd)"
GCC="gcc -Wvla -Wall -Werror"
PASS=0
FAIL=0

run_test() {
    local command="$1"
    local stem="$2"
    local tmpfile=$(mktemp)

    if [ -f "$stem.args" ] && [ -s "$stem.args" ]; then
        $command $(cat "$stem.args") < "${stem}.in" > "$tmpfile" 2>&1
    else
        $command < "${stem}.in" > "$tmpfile" 2>&1
    fi

    diff "$tmpfile" "${stem}.out" > /dev/null 2>&1
    if [[ $? -eq 0 ]]; then
        echo "  PASS: ${stem}"
        PASS=$((PASS+1))
    else
        echo "  FAIL: ${stem}"
        echo "  --- Expected output ---"
        cat "${stem}.out"
        echo "  --- Actual output ---"
        cat "$tmpfile"
        echo "  ----------------------"
        FAIL=$((FAIL+1))
    fi
    rm "$tmpfile"
}

########################################
# Q1 - SEQUENCES
########################################
echo "========================================"
echo "  A3 Complete Testing Script"
echo "  gcc flags: -Wvla -Wall -Werror"
echo "========================================"
echo ""
echo "======== Q1: SEQUENCES ========"
cd "$BASEDIR/q1"
chmod +x sequences_sample

# Generate expected .out files (stdout + stderr)
for t in test1 test2 test3 test4; do
    ./sequences_sample $(cat "$t.args") < "$t.in" > "$t.out" 2>&1
done
echo "Generated .out files from sequences_sample"

# Compile
$GCC sequences.c
if [[ $? -ne 0 ]]; then
    echo "  COMPILE FAILED for sequences.c"
else
    echo "Compiled sequences.c"
    for t in test1 test2 test3 test4; do
        run_test ./a.out "$t"
    done
fi

########################################
# Q2 - MAZE
########################################
echo ""
echo "======== Q2: MAZE ========"
cd "$BASEDIR/q2"
chmod +x mazeSample

# Generate expected .out files (stdout + stderr)
for t in test1 test2 test3 simpletest; do
    touch "$t.args"
    ./mazeSample < "$t.in" > "$t.out" 2>&1
done

# Create additional edge-case tests

# Test: malformed maze (no start tile)
cat > errortest1.in << 'EOF'
OOOXO
OXOOO
OXXXO
OOXXG

p
EOF
touch errortest1.args

# Test: malformed maze (no goal tile)
cat > errortest2.in << 'EOF'
SOOXO
OXOOO
OXXXO
OOXXO

p
EOF
touch errortest2.args

# Test: multiple starts
cat > errortest3.in << 'EOF'
SOOXO
SXOOO
OXXXO
OOXXG

p
EOF
touch errortest3.args

# Test: invalid tile character
cat > errortest4.in << 'EOF'
SOOXO
OXZOO
OXXXO
OOXXG

p
EOF
touch errortest4.args

# Test: reset and move commands
cat > movetest1.in << 'EOF'
SOOG
OOOX
OOOO

p
me p
me p
me p
r p
ms p
q
EOF
touch movetest1.args

# Test: invalid command and invalid move direction
cat > errortest5.in << 'EOF'
SOOG

p
z
ma
q
EOF
touch errortest5.args

# Test: walk into walls and edges
cat > walltest1.in << 'EOF'
XSXG
XOXX

mn p
mw p
ms p
me p
q
EOF
touch walltest1.args

# Generate .out for all new tests
for t in errortest1 errortest2 errortest3 errortest4 movetest1 errortest5 walltest1; do
    ./mazeSample < "$t.in" > "$t.out" 2>&1
done

echo "Generated .out files from mazeSample (including edge cases)"

# Compile
$GCC main.c maze.c
if [[ $? -ne 0 ]]; then
    echo "  COMPILE FAILED for maze"
else
    echo "Compiled maze"
    for t in simpletest test1 test2 test3 errortest1 errortest2 errortest3 errortest4 movetest1 errortest5 walltest1; do
        run_test ./a.out "$t"
    done
fi

########################################
# Q4 - WRITEVAL
########################################
echo ""
echo "======== Q4: WRITEVAL ========"
cd "$BASEDIR/q4"
chmod +x writeValSample

# Generate expected .out for existing test (stdout + stderr)
touch test1.args
./writeValSample < test1.in > test1.out 2>&1

# Create additional tests

# Test: char and ptr types
cat > test2.in << 'EOF'
char A
char z
int 42
EOF
touch test2.args

# Test: pointer type
cat > test3.in << 'EOF'
ptr 0
int 100
str hello
EOF
touch test3.args

# Test: empty input (no values written)
cat > test4.in << 'EOF'
EOF
touch test4.args

# Test: multiple strings
cat > test5.in << 'EOF'
str first
str second
str third
EOF
touch test5.args

# Test: mixed types
cat > test6.in << 'EOF'
int 0
int -1
char X
str test
int 2147483647
EOF
touch test6.args

# Generate .out for all tests
for t in test1 test2 test3 test4 test5 test6; do
    ./writeValSample < "$t.in" > "$t.out" 2>&1
done

echo "Generated .out files from writeValSample (including edge cases)"

# Compile
$GCC harness.c writeval.c raw.c
if [[ $? -ne 0 ]]; then
    echo "  COMPILE FAILED for writeVal"
else
    echo "Compiled writeVal"
    for t in test1 test2 test3 test4 test5 test6; do
        run_test ./a.out "$t"
    done
fi

########################################
echo ""
echo "========================================"
echo "  Results: $PASS passed, $FAIL failed"
echo "========================================"
