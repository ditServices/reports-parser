  /*
   * This file is part of the Reports Parser Project (https://github.com/ditServices/reports-parser).
   * Copyright (c) 2020 Howard Colin.
   *
   * This program is free software: you can redistribute it and/or modify
   * it under the terms of the GNU General Public License as published by
   * the Free Software Foundation, version 3.
   *
   * This program is distributed in the hope that it will be useful, but
   * WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   * General Public License for more details.
   *
   * You should have received a copy of the GNU General Public License
   * along with this program. If not, see <http://www.gnu.org/licenses/>.
   */

%{
#include <stdio.h>
#include <string.h>
#include "ca_mu.tab.h"
#include "ca_reports.h"
char* duplicate_segment(const char* token, int token_length);
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
"cam_assistant"     return CAM_ASSIST;
"cam_index"         return CAM_INDEX;
"location"          return LOCATION;
"producing_company" return P_COMPANY;
"colorspace"        return C_SPACE;
"colourspace"       return C_SPACE;
"fps"               return FPS;
"shutter_angle"     return S_ANGLE;
"framelines"        return F_LINES;


"reel"              return REEL;
"scene"             return SCENE;
"slate"             return SLATE;

"exit"              return EXIT;
"END"               return END;


\"[^"\n]*["\n]              {yylval = duplicate_segment(yytext+1, yyleng -2); return META;}
[aA-aZ][0-9]+               {yylval = strdup(yytext); return REEL_ID;}
[aA-aZ][0-9]+:[0-9]{4}      {yylval = strdup(yytext); return REEL_ID;}
([0-9aA-zZ]*\/[0-9aA-zZ]*)  {yylval = strdup(yytext); return SCENE_ID;}
[0-9]+                      {yylval = strdup(yytext); return SLATE_ID;}
[0-9][aA-zZ]+               {yylval = strdup(yytext); return TAKE;}
[0-9]+-[0-9]+               {yylval = strdup(yytext); return MULTI_T;}
[0-9]+MM                    {yylval = strdup(yytext); return LENS;}
T[0-9]\.[0-9]+              {yylval = strdup(yytext); return STOP;}
"{"([^}]*)"}"               {yylval = duplicate_segment(yytext+1, yyleng -2); return FILTERS;}

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

char* duplicate_segment(const char* token, int token_length) {
  char* dup = malloc(token_length + 1);
  if (!dup) { /* handle memory allocation error */ }
  memcpy(dup, token, token_length);
  dup[token_length] = 0;
  return dup;
}
