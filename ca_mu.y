%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
void check_command(int command_val);
extern int yylineno;
int v_val = 0;
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

metadata: command op data {   printf("%s is valid.\n", v_val, $3);
                              check_command(v_val);
                              free($3);
                          }
        | data op data op data op data {  printf("row data is valid\n\t %s %s %s %s\n", $1, $3, $5, $7);
                                          free($1); free($3); free($5); free($7);
                                        }
        ;

command: PROD_TITL {v_val = PROD_TITL;}
      |  _DIR      {v_val = _DIR;}
      |  DOP       {v_val = DOP; }
      |  DIT       {v_val = DIT; }
      |  FORMAT    {v_val = FORMAT; }
      |  CAMERA    {v_val = CAMERA; }
      |  CODEC     {v_val = CODEC; }
      |  DATE      {v_val = DATE; }
      |  REEL      {v_val = REEL;}
      |  SCENE     {v_val = SCENE; }
      |  SLATE     {v_val = SLATE; }
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

void check_command(int command_val) {
  switch(command_val) {
    case PROD_TITL:
      printf("TEST\n");
  }
}

void yyerror(char *s) {fprintf(stderr, "%s Line: %d\n", s, yylineno);}
