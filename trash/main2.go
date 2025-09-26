package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	// var fileName string = "main.c"

	// content, err := os.ReadFile(fileName)
	// if err != nil {
	// 	fmt.Printf("cannot read file %s\n", err)
	// 	return
	// }
	//
	// fmt.Printf("%s\n", content)

	if len(os.Args) < 2 || len(strings.ReplaceAll(os.Args[1], " ","")) < 3 {
		fmt.Printf("no file name provided\n")
		return
	}

	fileName := os.Args[1]
	bytes, err := os.ReadFile(fileName)
	if err != nil {
		fmt.Println("error occured readinf file\n", err)
		return
	}

	fmt.Printf("%s\n", bytes)
}
