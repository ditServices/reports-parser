%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
extern int yylineno;
%}

%locations
%token PROD_TITL _DIR DOP DIT FORMAT CAMERA CODEC DATE EQUALS COLON REEL REEL_ID META AUTO SCENE SCENE_ID

%%

input: input metadata
     | metadata
     ;

metadata: command op data {printf("Metadata is valid @ %d\n", yylineno);}
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
      ;

op: EQUALS
  | COLON
  ;

data: META
    | REEL_ID
    | SCENE_ID
    ;

%%

int main(void) {
  return yyparse();
}

void yyerror(char *s) {fprintf(stderr, "%s Line: %d\n", s, yylineno);}
