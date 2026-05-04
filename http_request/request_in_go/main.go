package main

import (
	"fmt"
	"net/http"
)

func main() {
	URL := "https://aleatori.cat/random"

	catImgUrl, err := GetCatImgLink(URL)
	if err != nil {
		fmt.Printf("Error: %s\n", err)
		return
	}

	fmt.Printf("Cat image: %s\n", catImgUrl)
}

func MakeGetRequest(url string) (*http.Response, error) {
	resp, err := http.Get(url)

	if err != nil {
		fmt.Println("Error: ", err)
		return nil, err
	}
	defer resp.Body.Close()

	return resp, nil
}

func GetCatImgLink(url string) (string, error) {
	resp, err := MakeGetRequest(url)
	if err != nil {
		fmt.Println("Error: ", err)
		return "", err
	}

	return resp.Request.URL.String(), nil
}
