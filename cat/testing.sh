#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="file.txt"

FLAGS="-b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank"

for var in $FLAGS
do
  for var2 in $FLAGS
  do
    for var3 in $FLAGS
    do
      for var4 in $FLAGS
      do
        if [ "$var" != "$var2" ] && [ "$var2" != "$var3" ] && [ "$var" != "$var3" ] && [ "$var" != "$var4" ] && [ "$var2" != "$var4" ] && [ "$var3" != "$var4" ]
        then          
          DIFF_RES="$(diff -a <(build/s21_cat $var $var2 $var3 $var4 "$TEST_FILE") <(cat $var $var2 $var3 $var4 "$TEST_FILE"))"
          
          if [ -z "$DIFF_RES" ]; then
            (( COUNTER_SUCCESS++ ))
            echo -e "Testing: $var $var2 $var3 $var4\n[ SUCCESS ]"
          else
            (( COUNTER_FAIL++ ))
            echo -e "Testing: $var $var2 $var3 $var4\n[ FAIL ]"
          fi
        fi
      done
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
