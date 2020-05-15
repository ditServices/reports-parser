%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
extern int yylineno;
%}

%define api.value.type {char *}

%locations
%token PROD_TITL _DIR DOP DIT FORMAT CAMERA CODEC DATE EQUALS SEP
%token COLON REEL REEL_ID META AUTO SCENE SCENE_ID SLATE SLATE_ID
%token TAKE LENS STOP FILTERS MULTI_T

%%

input: input metadata
     | metadata
     ;

metadata: command op data {printf("%s is valid.\n", $3);}
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

data: META            { printf("read: %s\n", $1); }
    | REEL_ID         { printf("read: %s\n", $1); }
    | SCENE_ID        { printf("read: %s\n", $1); }
    | SLATE_ID        { printf("read: %s\n", $1); }
    | TAKE            { printf("read: %s\n", $1); }
    | MULTI_T         { printf("read: %s\n", $1); }
    | LENS            { printf("read: %s\n", $1); }
    | STOP            { printf("read: %s\n", $1); }
    | FILTERS         { printf("read: %s\n", $1); }
    ;

%%

int main(void) {
  return yyparse();
}

void yyerror(char *s) {fprintf(stderr, "%s Line: %d\n", s, yylineno);}
