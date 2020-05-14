/* A Bison parser, made by GNU Bison 3.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CA_MU_TAB_H_INCLUDED
# define YY_YY_CA_MU_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROD_TITL = 258,               /* PROD_TITL  */
    _DIR = 259,                    /* _DIR  */
    DOP = 260,                     /* DOP  */
    DIT = 261,                     /* DIT  */
    FORMAT = 262,                  /* FORMAT  */
    CAMERA = 263,                  /* CAMERA  */
    CODEC = 264,                   /* CODEC  */
    DATE = 265,                    /* DATE  */
    EQUALS = 266,                  /* EQUALS  */
    SEP = 267,                     /* SEP  */
    COLON = 268,                   /* COLON  */
    REEL = 269,                    /* REEL  */
    REEL_ID = 270,                 /* REEL_ID  */
    META = 271,                    /* META  */
    AUTO = 272,                    /* AUTO  */
    SCENE = 273,                   /* SCENE  */
    SCENE_ID = 274,                /* SCENE_ID  */
    SLATE = 275,                   /* SLATE  */
    SLATE_ID = 276,                /* SLATE_ID  */
    TAKE = 277,                    /* TAKE  */
    LENS = 278,                    /* LENS  */
    STOP = 279,                    /* STOP  */
    FILTERS = 280,                 /* FILTERS  */
    MULTI_T = 281                  /* MULTI_T  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef char * YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_CA_MU_TAB_H_INCLUDED  */
