#!/bin/bash
> 'Res/result_M_1.csv'
> 'Res/result_N_1.csv'
> 'Res/result_K_1.csv'

if [ -n "$1" ]
then 
for ((i = 1; i <= $1 ;i++))
do
k=$(($i * 48))
res=$(./a.out 144 144 $k)
printf "%s \n" "$res" >> 'Res/result_K_1.csv' 
done
for ((i = 1; i <= $1 ;i++))
do
k=$(($i * 48))
res=$(./a.out 144 $k 144)
printf "%s \n" "$res" >> 'Res/result_N_1.csv'
done
for ((i = 1; i <= $1 ;i++))
do
k=$(($i * 48))
res=$(./a.out $k 144 144)
printf "%s \n" "$res" >> 'Res/result_M_1.csv'
done
else
./a.out
fi
