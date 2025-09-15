#! usr/bin/bash

read -p "Enter the number of directories: " n
read -p "Enter the path where the directories should go? (. for current): " path
mkdir -p -v $path

for ((i=0; i<$n; i++))
do
	read -p "Enter the name of "$((i+1))"th directory: " dir_name
	mkdir -v $path/$dir_name
	echo ""
done

echo ""
echo "Successfull Execution"
