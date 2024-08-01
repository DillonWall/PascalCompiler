#pragma once
//**************************************
// cVarDeclNode.h
//
// Defines a class to represent a variable declaration section.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cVisitor.h" //to get cSymbol w/o circular dependencies
#include "cBaseTypeNode.h"
#include "cDeclNode.h"
#include "lex.h"

class cVarDeclNode : public cDeclNode
{
    public:
        // Each var decl has a symbol and a type node
        cVarDeclNode(cSymbol* sym, cDeclNode* type) 
            : cDeclNode() 
        {
            cSymbol* newSym = InsertSymbol(sym);

            AddChild(type);
            AddChild(newSym); // cAstNode will handle this correctly if nullptr
        }

        // Detect if the symbol is in global scope, if not we created a new
        //      one, so just insert it.
        // If it is in global, it shouldnt be in local (else error) so make
        //      a new cSymbol from the old one's name
        cSymbol* InsertSymbol(cSymbol* sym)
        {
            // Dont use if nullptr
            if (sym == nullptr)
                return sym;

            string symName = sym->GetName();

            if (g_SymbolTable.GlobalLookup(symName) != nullptr)
            {
                // Check for error if is in local
                if (g_SymbolTable.LocalLookup(symName) != nullptr)
                {
                    SemanticParseError("Symbol " + symName + 
                            " already exists in current scope");
                }
                sym = new cSymbol(symName);
            }

            // Set this new symbol's type to the passed in type
            sym->SetDecl(this);
            g_SymbolTable.Insert(sym);

            return sym;
        }

        virtual cDeclNode* GetType()
        {
            return dynamic_cast<cDeclNode*>(GetChild(TYPE_CHILD_POS));
        }

        virtual cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
                retVal += " offset=\"" + std::to_string(m_offset) + "\"";
            }

            return retVal;
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int TYPE_CHILD_POS = 0;
        static const int NAME_CHILD_POS = 1;
};
