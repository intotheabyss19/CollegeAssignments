#! usr/bin/bash

read -p "Enter the path: " path
mkdir -v -p $path

read -p "Enter the number of files to be created: " n

for ((i=0; i<$n; i++))
do
	read -p "Enter the "$((i+1))"th file name: " f_name
	touch $path/$f_name
done

echo ""
echo "Succesfully created all the files in the given directory"
