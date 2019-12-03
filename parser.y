%{
    #include<iostream>
    #include<fstream>
    #include<cstdio>
    #include<vector>
    #include<stack>
    #include<string>
    #include<cstring>
    #include "HTML_AST.h"
    #include "LATEX_AST.h"
    #include "LATEX_generator.h"
    using namespace std;

    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;

    void yyerror(const char *s);

    extern HTML_AST_node root_tag;
    extern status tag_status;
    extern LATEX_AST_node LATEX_root_tag;
    extern vector<string> preamble;

%}

%union{
    char* sval;
}


%token<sval> TAG_START
%token<sval> TAG_START_END
%token<sval> STRING
%token TAG_END

%%
file:            tag_content
                 {
                    if(!tag_sequence.empty())
                    {
                        root_tag = tag_sequence.top();
                        tag_sequence.pop();
                    }
                 }




tag_content:     tag_content tag_start tag_content tag_end
               | tag_start tag_content tag_end
               | tag_content tag_start_end
               | tag_start_end
               | tag_content tag_start tag_end
               | tag_start tag_end
               | tag_content string
               | string
                 ;




tag_start:       TAG_START
                 {
                    tag_status = TAG_S;
                    string s = "";
                    int i = 0;
                    while(i < strlen($1))
                        s += $1[i++];
                    s += '>';
                    initialize_the_tag(s);
                 }
                 ;




tag_start_end:   TAG_START_END
                 {
                    tag_status = TAG_S_E;
                    string s = "";
                    int i = 0;
                    while(i < strlen($1))
                        s += $1[i++];
                    s += '>';
                    initialize_the_tag(s);
                 }
                 ;




tag_end:         TAG_END
                 {
                    tag_status = TAG_E;
                    end_the_tag();
                 }
                 ;




string:          STRING
                 {
                    string s = "";
                    //cout << $1 << endl;
                    int i = 0;
                    while(i < strlen($1))
                        s += $1[i++];
                    add_string_on_top(s);
                 }
                 ;

%%

int main(int, char** files)
{
    FILE *htmlfile = fopen(files[1], "r");
    if(!htmlfile)
    {
        cout << "Could not open the given file" << endl;
        return -1;
    }
    yyin = htmlfile;
    yyparse();
    HTML_AST_node N;
    N.label = "NULL";
    LATEX_AST_node latex_root = build_LATEX_AST(root_tag, N);
    ofstream fout;
    fout.open(files[2]);
    fout << "\\documentclass{article}" << endl;
    for(int i = 0; i < preamble.size(); i++)
    {
        fout << preamble[i] << endl;
    }
    fout << generate_LATEX_from_AST(latex_root) << endl;
}


void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}
