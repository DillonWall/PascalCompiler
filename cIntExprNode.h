#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Modified by: Dillon Wall
// dillon.wall@oit.edu
//

#include "cAstNode.h"
#include "cExprNode.h"

class cIntExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cIntExprNode(int value) : cExprNode()
        {
            m_value = value;
        }

        static bool IsInCharRange(int num)
        {
            if (num >= -128 && num <= 127)
                return true;

            return false;
        }

        virtual cDeclNode* GetType()
        {
            // Check if it should return char or int
            if (IsInCharRange(m_value))
            {
                // Lookup symbol for "char" and return decl from it
                return g_SymbolTable.GlobalLookup("char")->GetDecl();
            }
            // Else
            // Lookup symbol for "integer" and return decl from it
            return g_SymbolTable.GlobalLookup("integer")->GetDecl();
        }
        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        virtual string NodeType() { return string("INTEGER"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        int m_value;        // value of integer constant (literal)
};
