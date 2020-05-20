%{
#include <stdio.h>
#include <stdlib.h>
#include "t_Count.h"
#include "ca_reports.h"

int yylex();
void yyerror(char *s);
void check_command(int command_val, char *data);

extern int yylineno;
int v_val = 0;

CA_REPORT *report;

%}

%define api.value.type {char *}

%locations
%token PROD_TITL _DIR DOP DIT FORMAT CAMERA CODEC DATE EQUALS SEP END
%token COLON REEL REEL_ID META AUTO SCENE SCENE_ID SLATE SLATE_ID
%token TAKE LENS STOP FILTERS MULTI_T

%%

input: input metadata
     | metadata
     ;

metadata: command op data               {
                                          check_command(v_val, $3);
                                          free($3);
                                        }

        | data op data op data op data  { printf("\t\t\t %s %s %s %s\n", $1, $3, $5, $7);
                                          ca_add_tablerow(report, $1, $3, $5, $7);
                                          free($1); free($3); free($5); free($7);
                                        }

        | END                           { printf("Total reels: %d\n", t_ls.t_Reels);
                                          printf("Total pages: %d\n", report->newpage);
                                          ca_save_report(report);
                                          ca_free(report);
                                          exit(EXIT_SUCCESS);
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
      |  REEL      {v_val = REEL; t_ls.t_Reels++;}
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
  t_ls.t_Reels = 0;
  report = new_report();
  return yyparse();
}

void check_command(int command_val, char *data) {
  switch(command_val) {
    case PROD_TITL:
      printf("Production Title: %s\n", data);
      ca_add_pt(report, data);
      break;
    case _DIR:
      printf("Director: %s\n", data);
      ca_add_dir(report, data);
      break;
    case DOP:
      printf("DOP: %s\n", data);
      ca_add_dop(report, data);
      break;
    case DIT:
      printf("DIT: %s\n", data);
      ca_add_dit(report, data);
      break;
    case FORMAT:
      printf("Format: %s\n", data);
      ca_add_frmt(report, data);
      break;
    case CAMERA:
      printf("Camera: %s\n", data);
      ca_add_cam(report, data);
      break;
    case CODEC:
      printf("Codec: %s\n", data);
      ca_add_codec(report, data);
      break;
    case DATE:
      printf("Date: %s\n", data);
      ca_add_date(report, data);
      break;
    case REEL:
      printf("\nReel: %s\n", data);
      break;
    case SCENE:
      printf("\tScene: %s\n", data);
      break;
    case SLATE:
      printf("\t\tSlate: %s\n", data);
      break;
  }
}

void yyerror(char *s) {fprintf(stderr, "%s Line: %d\n", s, yylineno);}
