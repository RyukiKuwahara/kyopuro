package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
)

type Point struct {
	x int
	y int
}

type Edge struct {
	from, to int
	cost     int
	index    int
}

type PriorityQueue []*Edge

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].cost < pq[j].cost
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

func (pq *PriorityQueue) Push(x interface{}) {
	e := x.(*Edge)
	*pq = append(*pq, e)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	e := old[n-1]
	old[n-1] = nil // avoid memory leak
	*pq = old[0 : n-1]
	return e
}

func data_load(N, M, K *int, stations, customers *[]Point) [][]Edge {
	r := bufio.NewReader(os.Stdin)
	fmt.Fscan(r, N)
	fmt.Fscan(r, M)
	fmt.Fscan(r, K)

	for i := 0; i < *N; i++ {
		var p Point
		fmt.Fscan(r, &p.x)
		fmt.Fscan(r, &p.y)
		*stations = append(*stations, p)
	}

	graph := make([][]Edge, *N)
	for i := 0; i < *M; i++ {
		var u, v, w int
		fmt.Fscan(r, &u)
		fmt.Fscan(r, &v)
		fmt.Fscan(r, &w)
		u--
		v--
		e1 := Edge{u, v, w, i}
		e2 := Edge{v, u, w, i}
		graph[u] = append(graph[u], e1)
		graph[v] = append(graph[v], e2)
	}

	for i := 0; i < *K; i++ {
		var p Point
		fmt.Fscan(r, &p.x)
		fmt.Fscan(r, &p.y)
		*customers = append(*customers, p)
	}

	return graph
}

func data_out(N, M, K int, stations, customers []Point, graph [][]Edge, P, B []int) {
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()
	// fmt.Fprintln(w, N, M, K)
	// fmt.Fprintln(w, stations)
	// fmt.Fprintln(w, customers)
	// fmt.Fprintln(w, graph)
	for _, ele := range P {
		fmt.Fprintf(w, "%d ", ele)
	}
	fmt.Fprintln(w)
	for _, ele := range B {
		fmt.Fprintf(w, "%d ", ele)
	}
}

func prim(N, M, K int, stations, customers []Point, graph [][]Edge, P, B *[]int) {
	pq := make(PriorityQueue, 0)
	heap.Init(&pq)
	for _, edge := range graph[0] {
		e := edge
		heap.Push(&pq, &e)
	}
	var used = make([]bool, N)
	used[0] = true
	for pq.Len() > 0 {
		e := heap.Pop(&pq).(*Edge)
		if !used[e.to] {
			used[e.to] = true
			(*P)[e.to] = 1000
			(*B)[e.index] = 1
			for _, edge := range graph[e.to] {
				e := edge
				heap.Push(&pq, &e)
			}
		}
	}

	// for pq.Len() > 0 {
	// 	e := heap.Pop(&pq).(*Edge)
	// 	fmt.Printf("%.2d:%d %d\n", e.cost, e.from, e.to)
	// }
}

func main() {
	var N, M, K int
	var stations []Point
	var customers []Point
	graph := data_load(&N, &M, &K, &stations, &customers)
	P := make([]int, N)
	B := make([]int, M)
	prim(N, M, K, stations, customers, graph, &P, &B)
	data_out(N, M, K, stations, customers, graph, P, B)
}
