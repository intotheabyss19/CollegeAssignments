# (d) Write a shell program to display and count the number of files in all the directories
# based on the file type.

#! /bin/bash
echo "File count by type: "
find . -type f | rev | cut -d. -f1 | rev | sort | uniq -c | sort -nr
