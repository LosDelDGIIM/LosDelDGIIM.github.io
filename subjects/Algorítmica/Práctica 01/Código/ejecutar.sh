#!/bin/bash

if [ -e ../datos/$5 ]; then
    rm ../datos/$5
fi

for ((i=$2; i<=$3; i+=$4)); do
    ./$1 $i >> ../datos/$5
done
