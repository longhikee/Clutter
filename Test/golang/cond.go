package main
import (
	"fmt"
	"sync"
	"time"
)

var done = false

func consumer(name string, c *sync.Cond) {
	c.L.Lock()
	for !done {
		c.Wait()
	}
	fmt.Println(name,"read")
	c.L.Unlock()
}

func producer(c *sync.Cond) {
	c.L.Lock()
	done = true
	c.L.Unlock()
	fmt.Println("product is ready")
	c.Broadcast()
	fmt.Println("Wake all")
}

func main() {
	cond := sync.NewCond(&sync.Mutex{})

	for i:=0; i<5; i++ {
		name := fmt.Sprintf("consumer-%d", i)
		go consumer(name, cond)
	}
	producer(cond)
	time.Sleep(5)
}
