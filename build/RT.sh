#!/bin/bash


cd src

rm *.ll


for fn in *.c; do


	/usr/lib/llvm-12/bin/clang-12 -O0 -emit-llvm -Xclang -disable-O0-optnone $fn -S -o $fn.ll 

	/usr/lib/llvm-12/bin/opt -instnamer -S $fn.ll -o $fn.ll

	/usr/lib/llvm-12/bin/opt -mem2reg  -S $fn.ll -o $fn.ll

done






