bison -d parser.y;
flex lexer.l;
g++ parser.tab.c lex.yy.c;
./a.exe $1 $2