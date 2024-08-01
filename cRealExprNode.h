#pragma once
//**************************************
// cRealExprNode.h
//
// Defines an AST node for a real constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cAstNode.h"
#include "cExprNode.h"

class cRealExprNode : public cExprNode
{
    public:
        // param is the value of the real constant
        cRealExprNode(double value) : cExprNode()
        {
            m_value = value;
        }

        virtual cDeclNode* GetType()
        {
            // Lookup symbol for "real" and return decl from it
            return g_SymbolTable.GlobalLookup("real")->GetDecl();
        }
        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("REAL"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        double m_value;        // value of real constant (literal)
};
