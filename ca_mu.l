%{
#include <stdio.h>
#include <string.h>
#include "ca_mu.tab.h"
%}

%option yylineno

%%

"production_title"  return PROD_TITL;
"director"          return _DIR;
"DOP"               return DOP;
"DIT"               return DIT;
"format"            return FORMAT;
"camera"            return CAMERA;
"codec"             return CODEC;
"date"              return DATE;
"_auto"             return AUTO;

"reel"              return REEL;
"scene"             return SCENE;
"slate"             return SLATE;

"exit"              exit(EXIT_SUCCESS);
"END"               return END;


\"[^"\n]*["\n]              {yylval = strdup(yytext); return META;}
[aA-aZ][0-9]+               {yylval = strdup(yytext); return REEL_ID;}
([0-9aA-zZ]*\/[0-9aA-zZ]*)  {yylval = strdup(yytext); return SCENE_ID;}
[0-9]+                      {yylval = strdup(yytext); return SLATE_ID;}
[0-9][aA-zZ]+               {yylval = strdup(yytext); return TAKE;}
[0-9]+-[0-9]+               {yylval = strdup(yytext); return MULTI_T;}
[0-9]+MM                    {yylval = strdup(yytext); return LENS;}
T[0-9]\.[0-9]+              {yylval = strdup(yytext); return STOP;}
"{"([^}]*)"}"               {yylval = strdup(yytext); return FILTERS;}

=                   return EQUALS;
:                   return COLON;
,                   return SEP;

[ \t\n]                     ;
"/*"([^*]|\*+[^*/])*\*+"/"  ;

 .                   printf("unrecognized input: %s\n", yytext);

%%

int yywrap(void) {
  return 1;
}
