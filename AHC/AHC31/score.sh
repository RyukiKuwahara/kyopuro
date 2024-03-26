#!/bin/bash

src_file="../src/a.out"
# ループで0000.txtから0050.txtまでを処理
for i in {0..50}
do
    input_file="./in/$(printf "%04d.txt" $i)"  # 入力ファイルのパス
    output_file="./out/$(printf "%04d.txt" $i)"  # 出力ファイルのパス
    python3 main.py < "$input_file" > "$output_file"
    std_err_file="./std_err/$(printf "%04d.txt" $i)"  # 標準エラーファイルのパス

    # コマンドを実行
    cargo run --release --bin vis "$input_file" "$output_file"
done
