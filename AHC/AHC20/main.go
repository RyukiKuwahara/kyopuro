package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"math"
	"math/rand"
	"os"
	"sort"
)

var weight []int
var stations []Point
var customers []Point

type Point struct {
	x int
	y int
}

type Edge struct {
	from, to int
	cost     int
	index    int
}

type Format struct {
	P, B []int
	cost int
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

func data_load(N, M, K *int) [][]Edge {
	r := bufio.NewReader(os.Stdin)
	fmt.Fscan(r, N)
	fmt.Fscan(r, M)
	fmt.Fscan(r, K)

	for i := 0; i < *N; i++ {
		var p Point
		fmt.Fscan(r, &p.x)
		fmt.Fscan(r, &p.y)
		stations = append(stations, p)
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
		weight = append(weight, w)
	}

	for i := 0; i < *K; i++ {
		var p Point
		fmt.Fscan(r, &p.x)
		fmt.Fscan(r, &p.y)
		customers = append(customers, p)
	}

	return graph
}

func data_out(N, M, K int, graph [][]Edge, P, B []int) {
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

func prim(N, M, K int, graph [][]Edge, P, B *[]int) {
	pq := make(PriorityQueue, 0)
	heap.Init(&pq)
	for _, edge := range graph[0] {
		e := edge
		heap.Push(&pq, &e)
	}
	var used = make([]bool, N)
	used[0] = true
	(*P)[0] = 2000
	for pq.Len() > 0 {
		e := heap.Pop(&pq).(*Edge)
		if !used[e.to] {
			used[e.to] = true
			(*P)[e.to] = 2000
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

func genetic_algorithm(N, M, K int, f Format) Format {
	rand.Seed(0)

	var (
		elite      = 20
		candi_size = 100
		step       = 500
		maxiter    = 10
	)
	var candi []Format
	for i := 0; i < elite; i++ {
		var nf Format
		nf.P = append(nf.P, f.P...)
		nf.B = append(nf.B, f.B...)
		nf.P = mutate(nf.P, step)
		candi = append(candi, nf)

	}

	for i := 0; i < maxiter; i++ {

		//スコアを付ける
		for j := 0; j < len(candi); j++ {
			candi[j].cost = costf(candi[j])
		}

		sort.Slice(candi, func(i, j int) bool {
			return candi[i].cost < candi[j].cost
		})

		// for j := 0; j < len(candi); j++ {
		// 	fmt.Println(candi[j].cost)
		// }
		// fmt.Println(len(candi), cap(candi))
		fmt.Println(candi[0].cost)
		// fmt.Print("\n\n\n")

		candi = candi[:elite]

		for len(candi) < candi_size {
			rate := rand.Float64()

			if rate < 0.8 {
				c := rand.Intn(elite)
				var nf Format
				nf.P = append(nf.P, candi[c].P...)
				nf.B = append(nf.B, candi[c].B...)
				nf.P = mutate(nf.P, step)
				candi = append(candi, nf)
			} else {
				c1 := rand.Intn(elite)
				c2 := rand.Intn(elite)
				var nf1, nf2 Format
				nf1.P = append(nf1.P, candi[c1].P...)
				nf1.B = append(nf1.B, candi[c1].B...)
				nf2.P = append(nf2.P, candi[c2].P...)
				nf2.B = append(nf2.B, candi[c2].B...)
				nf1.P = crossover1(nf1.P, nf2.P)
				candi = append(candi, nf1)
			}
		}
	}
	sort.Slice(candi, func(i, j int) bool {
		return candi[i].cost < candi[j].cost
	})

	return candi[0]
}

func cnt_receiver(f Format) int {
	received := make([]int, len(customers))
	for i := 0; i < len(stations); i++ {
		for j := 0; j < len(customers); j++ {
			if calc_euclid(stations[i], customers[j]) < f.P[i] {
				received[j] += 1
			}
		}
	}
	cnt := 0
	for i := 0; i < len(received); i++ {
		if received[i] > 0 {
			cnt++
		}
	}
	return cnt
}

func calc_euclid(a, b Point) int {
	return int(math.Round(math.Sqrt(math.Pow(float64(b.x-a.x), 2) + math.Pow(float64(b.y-a.y), 2))))
}

func costf(f Format) int {
	cost := 0
	P := f.P
	B := f.B

	receiver_cnt := cnt_receiver(f)

	if receiver_cnt < len(B) {
		return int(math.Round(math.Pow(10, 6) * float64(receiver_cnt) / float64(len(B))))
	}

	for _, pow := range P {
		cost += pow * pow
	}
	for i, w := range weight {
		if B[i] == 1 {
			cost += w
		}
	}
	return int(math.Round(math.Pow(10, 6) * ((1 + math.Pow(10, 8)) / (float64(cost) + math.Pow(10, 7)))))
}

func mutate(P []int, step int) []int {
	i := rand.Intn(len(P))

	low := int(math.Max(0, float64(P[i]-step)))
	high := int(math.Min(5000, float64(P[i]+step)))

	P[i] = rand.Intn(high-low+1) + low
	return P
}

func crossover1(P1, P2 []int) []int {
	m := rand.Intn(len(P1)-2) + 1
	return append(P1[:m], P2[m:]...)
}

func main() {
	var N, M, K int
	graph := data_load(&N, &M, &K)
	P := make([]int, N)
	B := make([]int, M)
	prim(N, M, K, graph, &P, &B)
	f := Format{P: P, B: B}
	f = genetic_algorithm(N, M, K, f)
	data_out(N, M, K, graph, f.P, f.B)
}
