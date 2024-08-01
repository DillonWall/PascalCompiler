#pragma once
//**************************************
// cIdListNode.h
//
// Defines an ID list of cSymbols
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cSymbol.h"
#include "cAstNode.h"

class cIdListNode : public cAstNode
{
    public:
        cIdListNode(cSymbol* symbol = nullptr) 
        {
            if (symbol != nullptr)
                AddChild(symbol);
        }

        void AddSymbol(cSymbol* symbol)
        {
            if (symbol != nullptr)
                AddChild(symbol);
        }

        cSymbol* GetSymbol(int pos)
        {
            return dynamic_cast<cSymbol*>(GetChild(pos));
        }

        int GetNumChildren()
        {
            return NumChildren();
        }

        virtual string NodeType() { return string("IdList"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
