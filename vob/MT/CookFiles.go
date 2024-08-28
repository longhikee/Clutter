package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

const (
	RAWLOG_FOLDER = "/home/brantz/mt_log"
	TARGET_FOLDER = "/home/brantz/log-database"
)

func renameLogFile(fname *string) string {
	result := strings.Split(*fname, ".")
	targetFname := TARGET_FOLDER + "/" + strings.Join(result[:len(result)-2], ".") + ".xml"
	*fname = RAWLOG_FOLDER + "/" + *fname
	fmt.Println("cook file   : ", *fname)
	return targetFname
}

func removeTimeStamp(trace *string) {
	*trace = strings.Join(strings.Split(*trace, " ")[1:], " ") + "\n"
}

func filterTrace(trace string) bool {
	return strings.Contains(trace, "[INFO]") || strings.Contains(trace, "[ENTER]") || strings.Contains(trace, "[EXIT]") || strings.Contains(trace, "[ERR]") || strings.Contains(trace, "[WAR]")
}

func cookLogs(oldFile *os.File, newFile *os.File) {
	fileScanner := bufio.NewScanner(oldFile)
	fileScanner.Split(bufio.ScanLines)
	uniqueLogMap := make(map[string]int, 1024)
	for fileScanner.Scan() {
		trace := string(fileScanner.Text())
		if filterTrace(trace) {
			removeTimeStamp(&trace)
			uniqueLogMap[trace] = 0
		}
	}
	for trace, _ := range uniqueLogMap {
		newFile.WriteString(trace)
	}
}

func cookFiles(fname string) {
	targetFname := renameLogFile(&fname)
	targetFile, err := os.Create(targetFname)
	if err != nil {
		fmt.Println("create file failed", err)
		return
	}

	rawFile, err := os.Open(fname)
	if err != nil {
		fmt.Println("open file failed", err)
		return
	}

	cookLogs(rawFile, targetFile)

	targetFile.Close()
	rawFile.Close()
}

func main() {
	var file *os.File
	var err error
	file, err = os.Open(RAWLOG_FOLDER)
	if err != nil {
		return
	}

	var fileList []string
	fileList, err = file.Readdirnames(0)

	for _, fname := range fileList {
		cookFiles(fname)
	}

	file.Close()
}
