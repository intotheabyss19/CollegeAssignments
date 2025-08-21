#! usr/bin/bash

path=$(pwd)
echo "Path of Current Directory: $path"
files=$(ls)
echo "List of Files in Current Directory:"
count=0
# echo $files #lists all files at once in a single line
for f in $files
	do
		echo "    $f"
		count=$((count+1))
	done
echo ">>$count files found!!"
