// Implement the cSymbolTable header file. This is required to circumvent
// circular dependencies with cVarDeclNode.h

#include "cSymbolTable.h"
#include "pascalparse.h"
#include "cBaseTypeNode.h"
#include "cVarDeclNode.h"

cSymbolTable::cSymbolTable()
{
    m_symbolTables = 
        std::vector<std::unordered_map<string, cSymbol*>>();

    // Setup Global scope symbol table with IncreaseScope()
    IncreaseScope();

    // Add Keywords
    AddKeywords();
}

// Carry out actions when increasing scope
void cSymbolTable::IncreaseScope()
{
    //Create new symbol table for this scope
    m_symbolTables.push_back(
            std::unordered_map<string, cSymbol*>()
            );
}

// Carry out actions when decreasing scope
void cSymbolTable::DecreaseScope()
{
    //remove the symbol table, but dont free memory
    m_symbolTables.pop_back();
}

// Used to insert a new symbol
cSymbol* cSymbolTable::Insert(string symbol, int tokenType)
{
    //create a new cSymbol, insert pointer into current table, return
    cSymbol* temp = new cSymbol(symbol, tokenType);
    m_symbolTables.back().insert(std::pair<string, cSymbol*>(
                symbol, temp));
    return temp;
}

// Used to insert a new symbol that was already created
cSymbol* cSymbolTable::Insert(cSymbol* symbol)
{
    //create a new cSymbol, insert pointer into current table, return
    m_symbolTables.back().insert(std::pair<string, cSymbol*>(
                symbol->GetName(), symbol));
    return symbol;
}

// Performs a default lookup (on the first table)
// Returns cSymbol* if found, otherwise nullptr
cSymbol* cSymbolTable::LocalLookup(string symbol)
{
    auto search = m_symbolTables.back().find(symbol);
    if (search != m_symbolTables.back().end())
        return m_symbolTables.back()[symbol];
    return nullptr;
}

// Performs a lookup on a given symbol
// Returns the cSymbol* if found, otherwise nullptr
cSymbol* cSymbolTable::GlobalLookup(string symbol)
{
    // Reverse iterate over symbol tables
    for (auto it = m_symbolTables.rbegin(); 
            it != m_symbolTables.rend(); ++it)
    {
        auto search = (*it).find(symbol);
        if (search != (*it).end())
            return (*it)[symbol];
    }

    return nullptr;       //Symbol not found
}

// Adds all keywords to the symbol table which allows case insensitivity
void cSymbolTable::AddKeywords()
{

    Insert(new cSymbol("char", -1, true, 
                new cBaseTypeNode("char", 1, false)));
    Insert(new cSymbol("integer", -1, true, 
                new cBaseTypeNode("integer", 4, false)));
    Insert(new cSymbol("real", -1, true, 
                new cBaseTypeNode("real", 8, true)));
    Insert(new cSymbol("or", OR));
    Insert(new cSymbol("div", DIV));
    Insert(new cSymbol("mod", MOD));
    Insert(new cSymbol("and", AND));
    Insert(new cSymbol("not", NOT));
    Insert(new cSymbol("program", PROGRAM));
    Insert(new cSymbol("procedure", PROCEDURE));
    Insert(new cSymbol("function", FUNCTION));
    Insert(new cSymbol("begin", OPEN));
    Insert(new cSymbol("end", CLOSE));
    Insert(new cSymbol("if", IF));
    Insert(new cSymbol("then", THEN));
    Insert(new cSymbol("else", ELSE));
    Insert(new cSymbol("while", WHILE));
    Insert(new cSymbol("repeat", REPEAT));
    Insert(new cSymbol("until", UNTIL));
    Insert(new cSymbol("for", FOR));
    Insert(new cSymbol("do", DO));
    Insert(new cSymbol("to", TO));
    Insert(new cSymbol("downto", DOWNTO));
    Insert(new cSymbol("forward", FORWARD));
    Insert(new cSymbol("const", CONST));
    Insert(new cSymbol("type", TYPE));
    Insert(new cSymbol("var", VAR));
    Insert(new cSymbol("array", ARRAY));
    Insert(new cSymbol("record", RECORD));
    Insert(new cSymbol("of", OF));
    Insert(new cSymbol("nil", NIL));
    Insert(new cSymbol("write", WRITE));
    // Insert(new cSymbol("", ));
}

