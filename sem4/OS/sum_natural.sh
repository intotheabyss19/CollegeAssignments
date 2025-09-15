#! usr/bin/bash

sum=0
read -p "Enter the value of N: " n

for ((i=1 ; i<=$n ; i++));
do
	echo "$i"
	sum=$((sum+i))
done
echo "Sum of first $n natural numbers is: " $sum
