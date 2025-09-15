# (b) Write a Shell program to create n files in one of the previously created directories. The
# names of the files must be taken as input from the user, and the path of the directory
# must be given as input.

#! /bin/bash
read -p "Enter directory path: " dir
read -p "Enter file names (space-separated): " -a files
mkdir -p "$dir"
for f in "${files[@]}"; do
    touch "$dir/$f"
done
