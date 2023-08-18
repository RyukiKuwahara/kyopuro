#!/bin/bash

cd /home/ryuki/kyopuro/AHC/AHC22/tools

src_file="../src/a.out"
# ループで0000.txtから0099.txtまでを処理
for i in {0..10}
do
    input_file="./in/$(printf "%04d.txt" $i)"  # 入力ファイルのパス
    output_file="./out/$(printf "%04d.txt" $i)"  # 出力ファイルのパス
    std_err_file="./std_err/$(printf "%04d.txt" $i)"  # 標準エラーファイルのパス

    # コマンドを実行
    cargo run --release --bin tester "$src_file" < "$input_file" > "$output_file" 2> "$std_err_file"
done

# 日付と時刻を取得（日_時間_分 形式）
timestamp=$(date +"%d_%H_%M")

# フォルダ名の作成
folder_name="../result/$timestamp"
mkdir "$folder_name"

#　ソースコードをコピー
cp "../src/main.cpp" "$folder_name/main.cpp"

output_file="ave_score.txt"

# 初期化
total_score=0
total_wrong=0
total_placement_cost=0
total_measurement_cost=0
total_measurement_count=0
total_count=0

# ループで結果を処理
for i in {0..10}
do
    result_file="./std_err/$(printf "%04d.txt" $i)"
    
    if [ -f "$result_file" ]; then
        score=$(grep "Score =" "$result_file" | awk '{print $3}')
        wrong=$(grep "Number of wrong answers =" "$result_file" | awk '{print $6}')
        placement_cost=$(grep "Placement cost =" "$result_file" | awk '{print $4}')
        measurement_cost=$(grep "Measurement cost =" "$result_file" | awk '{print $4}')
        measurement_count=$(grep "Measurement count =" "$result_file" | awk '{print $4}')
        
        total_score=$((total_score + score))
        total_wrong=$((total_wrong + wrong))
        total_placement_cost=$((total_placement_cost + placement_cost))
        total_measurement_cost=$((total_measurement_cost + measurement_cost))
        total_measurement_count=$((total_measurement_count + measurement_count))
        
        total_count=$((total_count + 1))
    fi
done

# 平均値の計算
ave_score=$((total_score / total_count))
ave_wrong=$((total_wrong / total_count))
ave_placement_cost=$((total_placement_cost / total_count))
ave_measurement_cost=$((total_measurement_cost / total_count))
ave_measurement_count=$((total_measurement_count / total_count))

# 平均値をファイルに書き込む
echo "Average Score = $ave_score" > "$folder_name/$output_file"
echo "Average Number of wrong answers = $ave_wrong" >> "$folder_name/$output_file"
echo "Average Placement cost = $ave_placement_cost" >> "$folder_name/$output_file"
echo "Average Measurement cost = $ave_measurement_cost" >> "$folder_name/$output_file"
echo "Average Measurement count = $ave_measurement_count" >> "$folder_name/$output_file"

echo "Averages have been written to $folder_name/$output_file"


cd /home/ryuki/kyopuro/AHC/AHC22