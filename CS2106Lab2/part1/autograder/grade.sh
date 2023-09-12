#!/bin/bash

# Check if we have enough arguments
if [[ $# -ne 1 ]]; then
  echo "Usage: ./grade.sh <filename>"
  exit
fi

# Delete temporary files
rm  -f ref/*.out
for i in ref/*; do
  if [[ -x $i ]]; then
    rm $i

  fi
done


# Compile the reference program

gcc ref/utils.c ref/sum.c -o ref/$1

# Generate reference output files

for i in ref/*.in; do
  ref/$1 < $i > $i.out 
done
# Now mark submissions

rm -f results.out
for i in subs/*; do
  var=$(basename $i)
  rm -f $i/compileError
  rm -f $i/*.out
  for j in $i/*; do
    if [[ -x $j ]]; then
      rm -f $j
    fi
  done

  
  gcc $i/utils.c $i/sum.c -o $i/$1 2> $i/compileError
  if [[ $? -ne 0 ]]; then
    echo "Directory $var has a compile error" >> results.out
  fi
  count=0 
  score=0
  for j in ref/*.in; do
    filename=$(basename $j)
    if [[ -f $i/$1 ]]; then
      $i/$1 < $j > $i/$filename.out
      diff $i/$filename.out ref/$filename.out > $i/diff.out
      if [[ $? -eq 0 ]]; then
        score=$((score+1))
      fi
    fi
    count=$((count+1))
  done
  echo "Directory $var score $score/$count" >> results.out
done





#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#

# Iterate over every submission directory
    # Compile C code
    # Print compile error message to output file
    # Generate output from C code using *.in files in ref
    # Compare with reference output files  and award 1 mark if they are identical
# print score for student
# print total files marked.
    
