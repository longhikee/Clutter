package main

import (
	"bufio"
	"fmt"
	"net/http"
	"net/url"
	"os"
	"os/exec"
	"regexp"
	"strconv"
	"strings"
	"sync"
	"encoding/gob"
	"bytes"
)

const (
	FOLDER     = "/home/brantz/log-database/"
	RUN_FOLDER = "/home/brantz/HSS/ims_mt/"
	RUN_CMD    = "/home/brantz/HSS/ims_mt/scripts/robot/runCase.sh"
	MT_LOG     = "/home/brantz/HSS/ims_mt/logs/"
	SERVER_LOG = "/home/brantz/MT-Log-Search/records.log"
	CACHE      = "/home/brantz/log-database/data.gob"
)

// key-value: trace - file list
var LogMap map[string][]string
var pv uint32
var mutex sync.Mutex

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

func buildMapFromCache() {
	file, err := os.Open(CACHE)
	defer file.Close()
	if err != nil {
		return
	}
	d := gob.NewDecoder(file)
	d.Decode(&LogMap)
	fmt.Println("build  map from cache")
}

func cacheMap() {
	if 0 == len(LogMap) {
		return
	}
	b := new(bytes.Buffer)
	e := gob.NewEncoder(b)
	err := e.Encode(LogMap)
	if err != nil {
		return
	}

	file, _ := os.Create(CACHE)
	defer file.Close()
	file.Write(b.Bytes())
}

func initData() {
	if isFileExist(CACHE) {
		buildMapFromCache()
		if len(LogMap) != 0 {
			return
		}
	}

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

	cacheMap()
}

func getLogId(result string) string {
	re := regexp.MustCompile(`sut_pid\s*:\s*(\d+)`)
	match := re.FindStringSubmatch(result)
	if len(match) > 1 {
		id, _ := strconv.Atoi(strings.TrimSpace(match[1]))
		//fmt.Println(id)
		return strconv.Itoa(id)
	} else {
		return ""
	}
}

func isFileExist(file string) bool {
	_, err := os.Stat(file)
	if err == nil {
		return true
	}
	return false
}

func dumpMtLog(result string, caseName string) []byte {
	id := getLogId(result)
	if "" == id {
		return nil
	}

	var logFile string
	if strings.Contains(caseName, ".xml") {
		logFile = strings.TrimSuffix(caseName, ".xml")
	} else {
		logFile = caseName
	}

	logFile = MT_LOG + logFile + "." + id + ".log"
	//fmt.Println(logFile)
	if isFileExist(logFile) {
		data, _ := os.ReadFile(logFile)
		return data
	} else {
		return nil
	}
}

func search(key string) map[string]string {
	if "" == key {
		//fmt.Println("~~~~~~~~~~~~~~~~~~~~~~~key is empty~~~~~~~~~~~~~~~~~~~~")
		return nil
	}
	//key-value: file name - trace
	fileLogMap := make(map[string]string, 128)
	for log, _ := range LogMap {
		if strings.Contains(log, key) {
			list := LogMap[log]
			for _, fileName := range list {
				fileLogMap[fileName] = log
			}
		}
	}
	return fileLogMap
}

func setSize(input string, size string) string {
	return fmt.Sprintf("<font size='%spx'>%s</font>", size, input)
}

func setColor(input string, color string) string {
	return fmt.Sprintf("<font color='%s'>%s</font>", color, input)
}

func addTable(input string) string {
	style := `
<style>
table, th, td {
  border:1px solid black;
  border-collapse: collapse;
}
</style>`
	return style + "\n" + `<table border='1' style='width:100%'>` + "\n" + input + "\n</table>\n"
}

func addTr(input string) string {
	return fmt.Sprintf("<tr>\n%s</tr>\n", input)
}

func addTh(input string) string {
	return fmt.Sprintf("<th colspan='2'>%s</th>\n", input)
}

func addTd(input string, style_optional ...string) string {
	style := ""
	if len(style_optional) > 0 {
		style = style_optional[0]
	}

	if style != "" {
		return fmt.Sprintf("<td %s>%s</td>\n", style, input)
	} else {
		return fmt.Sprintf("<td>%s</td>\n", input)

	}
}

func addHref(input string) string {
	ref := fmt.Sprintf("http://10.67.30.50:9999/MT?=%s", input)
	return fmt.Sprintf("<a href=%s>%s</a>", ref, input)
}

func index(w http.ResponseWriter, r *http.Request) {
	html := `<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>MT Log DataBase</title>
</head>

<body>
<br>
<center>
    <h1><p style=color:#0000FF>MT SEARCH</p></h1>
</center>
    <div style="color:#0000FF">
    <h2>
        <center>
            <Form name="input" action="http://10.67.30.50:9999/search" method="get">
                Trace: <input type="text" name="log" maxlength=128 size=64 placeholder="key is trace in source code, case sensitive and support partial search">
                <input type="submit" value="search" style="color:#fff;background-color:#007bff;border-color:#007bff">
            </Form>
        </center>
        <br>
        <center>
            <h2><p style=color:#0000FF>RUN MT CASE</p></h2>
        </center>
        <center>
            <Form name="input" action="http://10.67.30.50:9999/run" method="get">
                Case: <input type="text" name="case" maxlength=128 size=64 placeholder="MT case name">
                <input type="submit" value="run" style="color:#fff;background-color:#007bff;border-color:#007bff">
            </Form>
        </center>
    </h2>
    </div>
    <div style="position:absolute;bottom:0;width:100%;text-align:center;color:#fff;background-color:#007bff;border-color:#007bff">By JIT Team</div>
</body>

</html>`

	w.Write([]byte(html))
}

func saveRecord(r *http.Request) {
	query := r.URL.Path + r.URL.RawQuery + "'    '" + r.RemoteAddr
	cmdStr := "date \"+%Y-%m-%d %R\" | xargs echo -n >> "+ SERVER_LOG + ";" + "echo " + "'    '" + query + " >> " + SERVER_LOG

	mutex.Lock()
	pv++
	cmd := exec.Command("sh", "-c", cmdStr)
	_ = cmd.Run()
	mutex.Unlock()
}

func dumpMt(caseName string) string {
	cmdStr := "find /home/brantz/HSS/ims_hss1/moduletest/testcases/ -name " + caseName + " | head -1 | xargs -i cat {} | sed '1,2d'"
	cmd := exec.Command("sh", "-c", cmdStr)
	out, err := cmd.CombinedOutput()
	if err != nil {
		return "404"
	}
	return string(out)
}

func handler(w http.ResponseWriter, r *http.Request) {
	go saveRecord(r)

	//:9999/search?log=key
	query := r.URL.RawQuery[4:]
	if 0 == len(query) {
		w.Write([]byte("search key is empty"))
		return
	}

	key, _ := url.QueryUnescape(query)
	resultMap := search(key)

	var th string
	var td1 string
	var td2 string
	var tds string

	if len(resultMap) > 1 {
		th = "Total found " + fmt.Sprintf("%d", len(resultMap)) + " records"
	} else {
		th = "Total found " + fmt.Sprintf("%d", len(resultMap)) + " record"
	}
	th = addTr(addTh(setSize(th, "5")))

	setWidth := false
	for k, v := range resultMap {
		if !setWidth {
			td1 = addTd(setColor(addHref(k), "blue"), `style="width:0%"`)
			td2 = addTd(strings.ReplaceAll(v, key, setColor(key, "red")), `style="width:100%"`)
			setWidth = true
		} else {
			td1 = addTd(setColor(addHref(k), "blue"))
			td2 = addTd(strings.ReplaceAll(v, key, setColor(key, "red")))
		}
		tds += addTr(td1 + td2)
	}

	table := addTable(th + tds)
	w.Write([]byte(table))
}

func counter(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte(fmt.Sprintf("%d\n", pv)))
}

func isEnvOccupied() bool {
	return isFileExist("/home/brantz/MT-Log-Search/Pause")
}

func runMt(w http.ResponseWriter, r *http.Request) {
	go saveRecord(r)

	if isEnvOccupied() {
		occupy := `Sorry, Out of Service.

Brant is using the build env coding. Service will be back soon.
Trace searching service is always online.
`
		w.Write([]byte(occupy))
		return
	}

	//:9999/run?case=
	caseName := r.URL.RawQuery[5:]
	if 0 == len(caseName) {
		w.Write([]byte("MT case name is empty"))
		return
	}

	w.Write([]byte(">>>> " + caseName + " running ...\n"))
	w.(http.Flusher).Flush()

	cmd := exec.Command(RUN_CMD, caseName)
	out, err := cmd.CombinedOutput()
	if err != nil {
		//case run fail
		w.Write(out)
		return
	} else {
		w.Write(out)
		w.Write([]byte("\n\n"))
		w.(http.Flusher).Flush()

		log := dumpMtLog(string(out), caseName)
		if nil == log {
			w.Write([]byte("log file not exist\n"))
		} else {
			w.Write(log)
		}
	}
}

func catMt(w http.ResponseWriter, r *http.Request) {
	go saveRecord(r)

	//:9999/MT?=
	caseName := r.URL.RawQuery[1:]
	if 0 == len(caseName) {
		w.Write([]byte("404"))
		return
	}
	xmlFormat := dumpMt(caseName)
	//htmlFormat := "<html><body><xmp>" + xmlFormat + "</xmp></body></html>"
	w.Header().Set("Content-Type", "application/xml; charset=utf-8")
	w.Write([]byte(xmlFormat))
}

func startHttpServer() {
	os.Chdir(RUN_FOLDER)
	http.HandleFunc("/", index)
	http.HandleFunc("/search", handler)
	http.HandleFunc("/counter", counter)
	http.HandleFunc("/run", runMt)
	http.HandleFunc("/MT", catMt)
	err := http.ListenAndServe(":9999", nil)
	if err != nil {
		fmt.Println(err)
		return
	}
}

func main() {
	fmt.Println("start init ...")
	LogMap = make(map[string][]string, 2048)
	pv = 0
	initData()

	fmt.Println("... init finished")
	fmt.Println("Log Map size: ", len(LogMap))

	startHttpServer()
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
