%{
//**************************************
// pascal.l
//
// Scanner for Pascal language for Compilers labs
//
// Author: Dillon Wall 
// dillon.wall@oit.edu
//
// Date: Jan. 20, 2020
//

#include <string>
#include <algorithm>
#include "lex.h"
#include "astnodes.h"
#include "cSymbolTable.h"
#include "pascalparse.h"

    // comment out the other line to generate debug info
#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);
string ToLower(string input);
void DoBegin();
void DoEnd();
int ProcessIndentifier(string input);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. PUNCTUATION is an example. */
PUNCTUATION          [()\[\];,\.+\-*=\^<>/:]
DIGIT                [0-9]

%%

    /* token definitions go here. */
"{"[^}]*"}"                 /* Do nothing when comment */
{PUNCTUATION}               DO_RETURN(yytext[0]);
"<="                        DO_RETURN(LE);
">="                        DO_RETURN(GE);
":="                        DO_RETURN(ASSIGN);
"<>"                        DO_RETURN(NOT_EQUAL);
[a-zA-Z][a-zA-Z0-9]*        DO_RETURN(ProcessIndentifier(yytext));
{DIGIT}+                    {
                                yylval.int_val = std::atoi(yytext);
                                DO_RETURN(INT_VAL);
                            }
{DIGIT}+\.{DIGIT}+          {
                                yylval.real_val = std::atof(yytext);
                                DO_RETURN(REAL_VAL);
                            }
[ \t\n]+                    /* Do nothing on space, tab, newline */
.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

// This function converts a string to lower case
string ToLower(string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

// Processes any indentifiers and keywords
int ProcessIndentifier(string input)
{
    string txt = ToLower(input);

    //Does it exist in the whole table? If not, treat as IDENTIFIER
    yylval.symbol = g_SymbolTable.GlobalLookup(txt);
    if (yylval.symbol == nullptr)
    {
        yylval.symbol = new cSymbol(txt); // assign yylval.symbol to use later
        return IDENTIFIER;
    }

    if (yylval.symbol->IsType())
    {
        yylval.decl_node = yylval.symbol->GetDecl();
        return TYPE_ID;
    }

    return yylval.symbol->GetTokenType();
}
