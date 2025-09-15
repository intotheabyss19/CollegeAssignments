# (e) Write a shell program to display and delete all the .txt files in all the directories.

#! /bin/bash
echo "Deleting all .txt files..."
find . -type f -name "*.txt" -delete -print
