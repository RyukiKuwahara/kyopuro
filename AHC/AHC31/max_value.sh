#!/bin/bash

src_file="../src/a.out"
# ループで0000.txtから0050.txtまでを処理
for i in {0..50}
do
    input_file="./in/$(printf "%04d.txt" $i)"  # 入力ファイルのパス
    max_value=$(awk 'NR>1{for(i=1;i<=NF;i++) if($i>max) max=$i} END{print max}' $input_file)
    echo $i $max_value
done