#! usr/bin/bash

# for ((i=1; i<=3; i++))
# do
# 	mkdir -v ./textdir"$i"
# 	cd ./textdir"$i"
# 	for ((j=1; j<=5; j++))
# 	do
# 		touch ./text"$j".txt
# 	done
# 	cd ..
# done
#
# echo "created txt files"

read -p "Enter the directory: " dir
cd ./$dir


