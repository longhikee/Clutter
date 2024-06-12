package main
import (
	"fmt"
	"sync"
	"time"
)

func main() {
	done := make(chan struct{})
	var wg sync.WaitGroup
	for i:=0; i<5; i++ {
		wg.Add(1)
		fmt.Printf("worker %d starting\n", i)
		//fmt.Println("\n")
		go func() {
			defer wg.Done()
			<-done
			fmt.Println("working")
		}()
	}
	time.Sleep(5)
	fmt.Println("Preparation is done, unblock all goroutines")
	close(done)
	wg.Wait()

}
