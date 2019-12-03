%{
    #include <iostream>
    #include "parser.tab.h"
    using namespace std;
    bool inside_comment = false;

%}

%option noyywrap

CHARACTERS [,'.">?!\-_/\\\:\;\[\]\(\)\{\}\+\=\*\@\#\$\%\^\&\~\`a-zA-Z0-9]

%%

[ \t\n] ;                      {
                                    if(inside_comment)
                                    {
                                        yylval.sval = strdup(yytext);
                                        return STRING;
                                    }
                               }


\<\!\-\-                       {
                                    inside_comment = true;
                                    yylval.sval = strdup(yytext);
                                    return TAG_START;
                               }




\-\-\>                         {
                                    inside_comment = false;
                                    return TAG_END;
                               }



\<\![Dd][Oo][Cc][Tt][Yy][Pp][Ee]([^>])*\> {
                                    yylval.sval = strdup(yytext);
                                    if(inside_comment)return STRING;
                                    else return TAG_START_END;
                               }




(\<[Ii][Mm][Gg]([^>])*\/\>)|(\<[Bb][Rr]([^>])*\>)      {
                                    yylval.sval = strdup(yytext);
                                    if(inside_comment)return STRING;
                                    else return TAG_START_END;
                             }









\<[^/!]([^>])*\/\>             {
                                    yylval.sval = strdup(yytext);
                                    if(inside_comment)return STRING;
                                    else return TAG_START_END;
                               }




\<[^/!]([^>])*\>                {
                                    yylval.sval = strdup(yytext);
                                    if(inside_comment)return STRING;
                                    else return TAG_START;
                               }



\<\/([^>])+\>                  {
                                    if(inside_comment)
                                    {
                                        yylval.sval = strdup(yytext);
                                        return STRING;
                                    }
                                    else return TAG_END;
                               }




{CHARACTERS}+                  {
                                    yylval.sval = strdup(yytext);
                                    return STRING;
                               }
. ;
%%

/*int main(int, char** files)
{
    FILE *htmlfile = fopen(files[1], "r");

    if(!htmlfile)
    {
        cout << "Could not open the given file!" << endl;
        return -1;
    }

    yyin = htmlfile;
    while(yylex());
}*/
