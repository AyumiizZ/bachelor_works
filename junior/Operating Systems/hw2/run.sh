#!/bin/bash
rm log*.txt -rf
for i in {1..100};do echo "Round $i" >> log1.txt; gcc p1.c; ./a.out >> log1.txt; echo >> log1.txt;done
rm a.out
for i in {1..100};do echo "Round $i" >> log2.txt; gcc p2.c; ./a.out >> log2.txt; echo >> log2.txt;done
rm a.out
for i in {1..100};do echo "Round $i" >> log3.txt; gcc p3.c; ./a.out >> log3.txt; echo >> log3.txt;done
rm a.out
gcc p4.c
./a.out > log4.txt
rm a.out
gcc p5.c;
./a.out > log5.txt
rm a.out

