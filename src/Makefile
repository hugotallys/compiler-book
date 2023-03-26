run: compiler
	./build/compiler "../test/program.txt"

compiler: build
	gcc -Wall main.c lex/lex.c parser/parser.c utils/utils.c -o build/compiler

build:
	mkdir build