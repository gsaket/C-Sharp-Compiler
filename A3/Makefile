bin/sharpie: build/lex.yy.c build/sharpie.tab.c build/sharpie.tab.h
	g++ build/sharpie.tab.c build/lex.yy.c -lfl -o bin/sharpie
	chmod +x ./bin/parser
	g++ postprocessing/gen_html.cpp -o bin/gen_html

build/sharpie.tab.c build/sharpie.tab.h: src/sharpie.y
	bison -d src/sharpie.y
	mv sharpie.tab.c build
	mv sharpie.tab.h build

build/lex.yy.c: src/sharpie.l build/sharpie.tab.h
	flex src/sharpie.l
	mv lex.yy.c build

clean:
	rm build/*.tab.c bin/sharpie build/*.yy.c build/*.tab.h bin/gen_html html/* build/*.raw

