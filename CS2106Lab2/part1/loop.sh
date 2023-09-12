#!/bin/bash

for i in /home/v/vishnu/*; do 
  echo $i
done

for i in {1..5}; do
  echo $i
done

i=0
while [[ $i -le 5 ]]; do
  echo $i
  let i=i+1
done

while read line; do
  echo $line
done
