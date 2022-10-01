#!/bin/bash

g++ heur.cpp -o heur && 

declare -i counter = 0;

for fname in in-*.txt; do 
  echo -e "\n\n$fname";
  echo -e "--- result ---"
  ./heur < "$fname";
  echo -e "--- validation ---"
  cat out-"$counter".txt;
  ((counter=counter+1))
done
