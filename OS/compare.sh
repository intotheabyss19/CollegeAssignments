#!/bin/bash
read -p "Enter a number: " n
if ((n % 2 == 0)); then echo "Even"; else echo "Odd"; fi
