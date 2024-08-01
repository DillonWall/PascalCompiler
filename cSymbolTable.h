#pragma once
//***********************************
// cSymbolTable.h
//
// Defines global symbol table which uses the "Stack of Tables" implementation.
// Therefore, each table is made with a hash map of string,cSymbol* pairs, and 
// are stored in a vector to simulate stack behavior.
//
//  Author: Dillon Wall
//  dillon.wall@oit.edu
//

#include <vector>
#include <unordered_map>
#include <string>
#include "cSymbol.h"

using std::string;


class cSymbolTable
{
    public:
        cSymbolTable();

        // Carry out actions when increasing scope
        void IncreaseScope();

        // Carry out actions when decreasing scope
        void DecreaseScope();

        // Used to insert a new symbol
        cSymbol* Insert(string symbol, int tokenType = -1);

        // Used to insert a new symbol that was already created
        cSymbol* Insert(cSymbol* symbol);

        // Performs a default lookup (on the first table)
        // Returns cSymbol* if found, otherwise nullptr
        cSymbol* LocalLookup(string symbol);

        // Performs a lookup on a given symbol
        // Returns the cSymbol* if found, otherwise nullptr
        cSymbol* GlobalLookup(string symbol);

        // Adds all keywords to the symbol table which allows case insensitivity
        void AddKeywords();
    protected:
        // "stack" of tables. Using a vector as a stack by using size to get top
        std::vector<std::unordered_map<string, cSymbol*>> m_symbolTables;

};

//extern cSymbolTable g_SymbolTable;
