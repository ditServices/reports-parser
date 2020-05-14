%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
extern int yylineno;
%}

%locations
%token PROD_TITL _DIR DOP DIT FORMAT CAMERA CODEC DATE EQUALS SEP
%token COLON REEL REEL_ID META AUTO SCENE SCENE_ID SLATE SLATE_ID
%token TAKE LENS STOP FILTERS MULTI_T

%%

input: input metadata
     | metadata
     ;

metadata: command op data {printf("metadata is valid.\n");}
        | data op data op data op data {printf("row data is valid\n");}
        ;

command: PROD_TITL
      |  _DIR
      |  DOP
      |  DIT
      |  FORMAT
      |  CAMERA
      |  CODEC
      |  DATE
      |  REEL
      |  SCENE
      |  SLATE
      ;

op: EQUALS
  | COLON
  | SEP
  ;

data: META
    | REEL_ID
    | SCENE_ID
    | SLATE_ID
    | TAKE
    | MULTI_T
    | LENS
    | STOP
    | FILTERS
    ;

%%

int main(void) {
  return yyparse();
}

void yyerror(char *s) {fprintf(stderr, "%s Line: %d\n", s, yylineno);}
