# (c) Write a Shell program to create n files with different extensions in another directory.
# The names of the files must be taken as input from the user, and the directory’s path
# must be given as input.

#! /bin/bash
read -p "Enter directory path: " dir
read -p "Enter file names with extensions: " -a files
mkdir -p "$dir"
for f in "${files[@]}"; do
    touch "$dir/$f"
done
