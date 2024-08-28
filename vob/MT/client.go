package main

import (
	"fmt"
	"net/http"
	"net/url"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage:")
		fmt.Println("./exe \"xxx yyy zzz\"")
		return
	}
	fmt.Println("query: ", os.Args[1])
	query := url.QueryEscape(os.Args[1])

	//url := "http://127.0.0.1:9999/search?log=" + query
	url := "http://10.67.30.50:9999/search?log=" + query
	resp, err := http.Get(url)
	if err != nil {
		fmt.Println(err)
		return
	}

	if nil == resp {
		fmt.Println("server is down")
		return
	}

	defer resp.Body.Close()

	//fmt.Printf("%#v\n", resp)
	result := make([]byte, 4096)
	for true {
		n, err := resp.Body.Read(result)
		if 0 == n {
			fmt.Println("server error")
			break
		}
		if err != nil {
			fmt.Print(string(result)[0:n])
			break
		}
		fmt.Print(string(result))
	}
}
