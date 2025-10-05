package goimp

type Tokenizer func(token *Token) bool


func callBacks(s *Raw, t Tokenizer){}


func testDeez(){
	callBacks()
}
