#pragma once
//**************************************
// cProcDeclNode.h
//
// Defines a class to represent a procedure declaration node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cExprListNode.h"
#include "cBlockNode.h"

class cProcDeclNode : public cDeclNode
{
    public:
        // symbol (exprList block) are added
        cProcDeclNode(cSymbol* header) : cDeclNode() 
        {
            cSymbol* newSym = InsertHeader(header);

            newSym->SetDecl(this);
            AddChild(newSym);
        }

        void AddVarDecls(cVarDeclsNode* decls)
        {
            AddChild(decls);
        }

        cVarDeclsNode* GetParams()
        {
            return dynamic_cast<cVarDeclsNode*>(GetChild(PARAMS_CHILD_POS));
        }

        void AddBlock(cBlockNode* block)
        {
            AddChild(block);
        }

        cBlockNode* GetBlock()
        {
            return dynamic_cast<cBlockNode*>(GetChild(BLOCK_CHILD_POS));
        }

        cSymbol* InsertHeader(cSymbol* sym)
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

        virtual string NodeType() { return string("proc"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
        static const int PARAMS_CHILD_POS = 1;
        static const int BLOCK_CHILD_POS = 2;
};
