#!/usr/bin/bash
p=$1
r=$2
(( m=$p*$r ))
(( n=2*$m ))
rm *.in
for (( i=0; i<$m; i++ ))
do
for (( j=0; j<$n; j++ ))
	do
echo -n “$((0 + $RANDOM % 100)) “ >> file${i}.in
done
echo >> file${i}.in
done
cat *.in

ml icc
ml openmpi
mpic++ -std c++14 -fopenmp -02 -g3 -Wall -c -fmessage-length=0 -o program.o code.cpp
mpic++ -fopenmp -o program program.o
mpiexec -np $p ./program $r
