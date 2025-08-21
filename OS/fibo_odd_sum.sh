#! usr/bin/bash

read -p "Enter N: " n
a=0
b=1
c=0
sum_odd=0
for ((i=0 ; i<$n; i++));
do
	echo $c
	if [$c -eq $0]; then
		sum_odd=$((sum_odd+c))
	fi
	c=$((a+b))
	a=$b
	b=$c
done
echo "Sum of odd numbers of the fibonacci is: " $sum_odd
