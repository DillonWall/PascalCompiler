#pragma once
//**************************************
// cConstDeclNode.h
//
// Defines an AST node for a const declaration
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"
#include "cExprNode.h"
#include "cSymbol.h"

class cConstDeclNode : public cDeclNode
{
    public:
        // symbol exprnode
        cConstDeclNode(cSymbol* name, cExprNode* expr) : cDeclNode()
        {
            AddChild(InsertSymbol(name));
            AddChild(expr);
        }

        cSymbol* InsertSymbol(cSymbol* sym)
        {
            // Dont use if nullptr
            if (sym == nullptr)
                return sym;

            string symName = sym->GetName();

            if (g_SymbolTable.GlobalLookup(symName) != nullptr)
                sym = new cSymbol(symName);

            sym->SetDecl(this);
            g_SymbolTable.Insert(sym);

            return sym;
        }

        virtual cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        virtual string NodeType() { return string("const_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
};
