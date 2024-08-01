#pragma once
//**************************************
// lex.h
//
// Defines global symbols used the the flex generated lexer 
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//
// Modified By: Dillon Wall
// dillon.wall@oit.edu
//

#include "cSymbolTable.h"
#include "cAstNode.h"
#include <string>

int yyparse();                          // parsing function
int yylex();                            // scanning function
extern char *yytext;                    // text of current token
extern int yylineno;                    // line number of input file
extern int yynerrs;                     // Num of compile errors
extern FILE *yyin;                      // FILE pointer for input
extern cAstNode *yyast_root;            // root of AST
extern cSymbolTable g_SymbolTable;      // global symbol table
