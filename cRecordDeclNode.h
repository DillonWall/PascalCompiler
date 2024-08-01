#pragma once
//**************************************
// cRecordDeclNode.h
//
// Defines a class to represent a record declaration node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cDeclsNode.h"

class cRecordDeclNode : public cDeclNode
{
    public:
        // symbol decls
        cRecordDeclNode(cSymbol* name, cDeclsNode* vars) 
            : cDeclNode() 
        {
            AddChild(InsertHeader(name));
            AddChild(vars);
        }

        cSymbol* InsertHeader(cSymbol* sym)
        {
            // Dont use if nullptr
            if (sym == nullptr)
                return sym;

            string symName = sym->GetName();

            if (g_SymbolTable.GlobalLookup(symName) != nullptr)
                sym = new cSymbol(symName);

            sym->SetIsType(true);
            sym->SetDecl(this);
            g_SymbolTable.Insert(sym);

            return sym;
        }

        virtual cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        virtual bool IsType()
        {
            return true;
        }
        virtual string NodeType() { return string("record"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
};
