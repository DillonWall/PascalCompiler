#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for a range declaration.
//
// Author: Dillon Wall 
// dillon.wall@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cRangeDeclNode : public cDeclNode
{
    public:
        // start end
        cRangeDeclNode(int start, int end) : cDeclNode()
        {
            m_start = start;
            m_end = end;
        }

        int GetStart() { return m_start; }
        int GetEnd() { return m_end; }

        virtual cSymbol* GetNameSymbol()
        {
            return nullptr;
        }

        virtual string AttributesToString() 
        {
            return " start=\"" + std::to_string(m_start) + "\" end=\"" + 
                std::to_string(m_end) + "\"";
        }
        virtual string NodeType() { return string("range"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_start;        // start value
        int m_end;          // end value
};
