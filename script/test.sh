#!/bin/bash


if [ ! -d "output" ];
then
    mkdir ./output
fi


head -n 1 ./input/data.txt
head -n 1 ./input/data.txt |  grep -nE ../code/model.cpp | tee ./output/res.txt
# grep -nE "*int" ../code/model.cpp  tee ./output/res.txt