package main

import (
	"fmt"
	"io"
	"net/http"
)

func main() {
	URL := "https://jsonplaceholder.typicode.com/posts/1"

	resp, err := http.Get(URL)
	if err != nil {
		fmt.Println("Error: ", err)
		return
	}

	defer resp.Body.Close()

	body, _ := io.ReadAll(resp.Body)
	fmt.Println(string(body))
}
