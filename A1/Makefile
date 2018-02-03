bin/lexer: build/lex.yy.c build/sharpie.tab.c build/sharpie.tab.h
	g++ build/sharpie.tab.c build/lex.yy.c -lfl -o bin/lexer

build/sharpie.tab.c build/sharpie.tab.h: src/sharpie.y
	bison -d src/sharpie.y
	mv sharpie.tab.c build
	mv sharpie.tab.h build

build/lex.yy.c: src/sharpie.l build/sharpie.tab.h
	flex src/sharpie.l
	mv lex.yy.c build

clean:
	rm build/*.tab.c bin/lexer build/*.yy.c build/*.tab.h

