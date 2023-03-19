debug:
	pglr --debug compile grammar.txt

parser: build
	gcc -Wall parser.c ../utils/utils.c -o build/parser

build:
	mkdir build