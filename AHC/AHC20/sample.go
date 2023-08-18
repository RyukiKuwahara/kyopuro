package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup

	start := time.Now()
	for i := 0; i < 1000; i++ {
		wg.Add(1) // ゴルーチンの開始を待機するためにカウンタを増やす
		go f(&wg, i)
	}

	wg.Wait() // ゴルーチンの完了を待機する

	time := time.Since(start)
	fmt.Println(time)

	runtime := runtime.GOMAXPROCS(-1)
	fmt.Println(runtime)
}

func f(wg *sync.WaitGroup, ind int) {
	// 重たい処理
	cnt := 0
	for i := 0; i < 100000000; i++ {
		cnt++
	}
	fmt.Println(ind)

	defer wg.Done() // ゴルーチンの完了を通知する
}
