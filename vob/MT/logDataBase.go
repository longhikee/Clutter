package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	FOLDER = "/home/brantz/log-database/"
)

//key-value: trace - file list
var LogMap map[string][]string

func buildMap(fname string) {
	//fmt.Println(fname)
	file, err := os.Open(FOLDER + fname)
	if err != nil {
		fmt.Println(err)
		return
	}
	fileScanner := bufio.NewScanner(file)
	fileScanner.Split(bufio.ScanLines)
	for fileScanner.Scan() {
		key := string(fileScanner.Text())
		LogMap[key] = append(LogMap[key], fname)
	}
	file.Close()
}

func initData() {
	file, err := os.Open(FOLDER)
	if err != nil {
		return
	}
	var fileList []string
	fileList, err = file.Readdirnames(0)

	for _, fname := range fileList {
		buildMap(fname)
	}
	file.Close()
}

func main() {
	fmt.Println("start init ...")
	LogMap = make(map[string][]string, 2048)
	initData()

	fmt.Println("... init finished")
	fmt.Println("Log Map size: ", len(LogMap))

	for k, v := range LogMap {
		if (1 == len(v)) {
			fmt.Println(k)
		}
	}
}



//------------------------------debug functions-------------------------------------

func testResult(inputMap map[string]string) {
	file, _ := os.Create("./txt")

	for k, v := range inputMap {
		fmt.Println(k, ":", v)
		file.WriteString(k + " : " + v + "\n")
	}
	file.WriteString("total found " + fmt.Sprintf("%d", len(inputMap)) + " records")
	file.Close()
}

func printMap(inputMap map[string]string) {
	for k, v := range inputMap {
		fmt.Println(k, ":", v)
	}
	fmt.Println("total found ", len(inputMap), " records")
	fmt.Println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
}
