# (a) Write a Shell program to create n directories with a given folder name from the user.

#! /bin/bash
read -p "Enter folder name: " name
read -p "Enter count: " n
for (( i=1; i<=n; i++ )); do
    mkdir -p "$name$i"
done
