#! usr/bin/bash

read -p "Enter the path to the directory: " dir

cd $HOME/$dir

read -p "Enter the file extension: ." ext
find *.$ext | wc -l
