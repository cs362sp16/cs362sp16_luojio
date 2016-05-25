#!/bin/bash

file1="$1"
file2="$2"
seednum="$3"
output1="diff1.out"
output2="diff2.out"
rootpath=${PWD##*/}

rm -r -f $file1
mkdir $file1
mkdir $file2

make testdominion
mv testdominion $file1
make clean
make testdominion
mv testdominion $file2

cd $file1
./testdominion $seednum > $output1

cd ../$file2
./testdominion $seednum > $output2

cd ..

diff -s -y $file1"/"$output1 $file2"/"$output2 > diff.out
make cleantest

if [ $? -eq 0 ]
then
	echo "TEST PASSED"
else
	echo "TEST FAILED"
fi
