package main

import (
	"fmt"
	"os"
	"strings"
)

var spaceDelimiter = " "

type Raw struct {
	token string
}

type Token struct {
	value   int
	literal string
}

func lineParser(s string) ([]Token, error) {
	bytes, err := os.ReadFile(s)
	if err != nil {
		return []Token{}, err
	}

	literals := strings.Split(string(bytes), spaceDelimiter)

	var tokens []Token
	var rawTokens []Raw
	for _, l := range literals {
		r := Raw{token: l}
		rawTokens = append(rawTokens, r)
	}

	for _, r := range rawTokens {
		t := r.Factory()
		tokens = append(tokens, t)
	}
	return tokens, nil
}

func (r *Raw) Factory() Token {
	return Token{}
}

func main() {
	fmt.Println("How would i parse lines in go??")

	if len(os.Args) < 2 {
		fmt.Printf("Create input stream\n")
		return
	}

	tokens, err := lineParser(os.Args[1])
	if err != nil {
		fmt.Print(err)
	}

	_ = tokens

}
