#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RESULT=""
TEST_FILE="file1.txt"
TEST_FILE2="file2.txt"
PATTERN_FILE="patterns.txt"

ALL_FLAGS="-i -v -c -l -n -h -s"
TEMPLATES_ARRAY=(
    "-" "." "f" "ab" "A" "[!0-9]" "[0-9]" "[a-z]" "[A-Z0-9]"
)
size=${#TEMPLATES_ARRAY[@]}

echo -e "Hello\nworld\n123\nABC\nabc\nspecial characters: @#$%^&*()\nghi" > "$TEST_FILE"
echo -e "Testing\HELLO AGAIN\nprogram\nblueberry muffin\nDEF\nGHI\n12345" > "$TEST_FILE2"
echo -e "Hello\n[0-9]\nabc" > "$PATTERN_FILE"

if [ ! -f "$TEST_FILE" ] || [ ! -f "$TEST_FILE2" ] || [ ! -f "$PATTERN_FILE" ]; then
    echo "Error: Required test files are missing!"
    exit 1
fi

run_test() {
    local cmd="$1"
    ./s21_grep $cmd > s21_grep.txt
    grep $cmd > grep.txt
    DIFF_RESULT="$(diff s21_grep.txt grep.txt)"

    if [ -z "$DIFF_RESULT" ]; then
        (( SUCCESS++ ))
        echo -e "$cmd\n [ SUCCESS ]"
    else
        (( FAIL++ ))
        echo -e "$cmd\n [ FAIL ]"
    fi

    rm -f s21_grep.txt grep.txt
}

for flag in $ALL_FLAGS; do
    for pattern in "${TEMPLATES_ARRAY[@]}"; do
        TEST_CMD="$flag -f $PATTERN_FILE -e $pattern $TEST_FILE"
        run_test "$TEST_CMD"
    done
done

for flag1 in $ALL_FLAGS; do
    for flag2 in $ALL_FLAGS; do
        if [ "$flag1" != "$flag2" ]; then
            N1=$((RANDOM % $size))
            N2=$((RANDOM % $size))
            TEST_CMD="$flag1 $flag2 -f $PATTERN_FILE -e ${TEMPLATES_ARRAY[$N1]} -e ${TEMPLATES_ARRAY[$N2]} $TEST_FILE $TEST_FILE2"
            run_test "$TEST_CMD"
        fi
    done
done

for flag1 in $ALL_FLAGS; do
    for flag2 in $ALL_FLAGS; do
        for flag3 in $ALL_FLAGS; do
            if [ "$flag1" != "$flag2" ] && [ "$flag2" != "$flag3" ] && [ "$flag1" != "$flag3" ]; then
                N1=$((RANDOM % $size))
                N2=$((RANDOM % $size))
                N3=$((RANDOM % $size))
                TEST_CMD="$flag1 $flag2 $flag3 -f $PATTERN_FILE -e ${TEMPLATES_ARRAY[$N1]} -e ${TEMPLATES_ARRAY[$N2]} -e ${TEMPLATES_ARRAY[$N3]} $TEST_FILE $TEST_FILE2"
                run_test "$TEST_CMD"
            fi
        done
    done
done

for flag1 in $ALL_FLAGS; do
    for flag2 in $ALL_FLAGS; do
        for flag3 in $ALL_FLAGS; do
            for flag4 in $ALL_FLAGS; do
                if [ "$flag1" != "$flag2" ] && [ "$flag2" != "$flag3" ] && [ "$flag1" != "$flag3" ] && [ "$flag4" != "$flag1" ] && [ "$flag4" != "$flag2" ] && [ "$flag4" != "$flag3" ]; then
                    N1=$((RANDOM % $size))
                    N2=$((RANDOM % $size))
                    N3=$((RANDOM % $size))
                    N4=$((RANDOM % $size))
                    TEST_CMD="$flag1 $flag2 $flag3 $flag4 -f $PATTERN_FILE -e ${TEMPLATES_ARRAY[$N1]} -e ${TEMPLATES_ARRAY[$N2]} -e ${TEMPLATES_ARRAY[$N3]} -e ${TEMPLATES_ARRAY[$N4]} $TEST_FILE $TEST_FILE2"
                    run_test "$TEST_CMD"
                fi
            done
        done
    done
done

rm -f file* patterns*

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
