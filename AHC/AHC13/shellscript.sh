#!/bin/sh

dir_path="./in/*"
dirs=`find $dir_path -maxdepth 0 -type f`

for dir in $dirs;
do
    # echo $dir
    # ここから実行処理を記述
    ./random.exe < $dir > /dev/null
done