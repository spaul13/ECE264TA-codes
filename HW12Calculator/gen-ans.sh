#!/bin/bash

rm -rf ans
mkdir ans

make
for f in inputs/*
do
  ./pa11 $f 2> /dev/null | tail -1 > ans/$(basename $f)
done
