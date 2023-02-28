#!/bin/bash

FIX="0"
if [[ "$1" == "fix" ]]; then
  FIX="1"
fi

CLANG_FORMAT="clang-format -style=Google"

PROPER_STYLE="1"
files="$(find ./* -name '*.cpp' -or -name '*.h')"
for file in $files; do
  # Check the style, but do not fix.
  if [[ "$FIX" == "0" ]]; then
    cmp -s <($CLANG_FORMAT $file) $file
    if [[ "$?" != "0" ]]; then
      PROPER_STYLE="0"
    fi
  
  # Fix the style.
  else
    echo "Fixing style: $file"
    $CLANG_FORMAT -i $file
  fi
done

if [[ "$FIX" == "0" ]]; then
  if [[ "$PROPER_STYLE" == "1" ]]; then
    echo "Style is good!"
  else
    echo "Style is not good."
    echo "Please run: ./scripts/style.sh fix"
  fi
fi