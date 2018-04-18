bin/sharpie: build/lex.yy.c build/sharpie.tab.c build/sharpie.tab.h include/attr.h bin/codegen
	g++ -std=c++11 build/sharpie.tab.c build/lex.yy.c -lfl -o bin/sharpie

bin/codegen: src/CodeGeneration.cpp
	g++ -std=c++11 src/CodeGeneration.cpp -o bin/codegen
	chmod +x bin/csharp

build/sharpie.tab.c build/sharpie.tab.h: src/sharpie.y include/attr.h
	bison -d src/sharpie.y
	mv sharpie.tab.c build
	mv sharpie.tab.h build

build/lex.yy.c: src/sharpie.l build/sharpie.tab.h
	flex src/sharpie.l
	mv lex.yy.c build

clean:
	rm build/*.tab.c bin/sharpie build/*.yy.c build/*.tab.h bin/codegen
