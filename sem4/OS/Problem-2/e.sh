# (e) Write a shell program to display and count the number of files in a current directory
#! /bin/bash
file_count=$(ls -1 | wc -l)
echo "Files count: $file_count"
