#pragma once
//**************************************
// cBinaryExprNode.h
//
// Defines binary expressions
//
// Modified By: Dillon Wall
// dillon.wall@oit.edu
//

#include "cExprNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        cBinaryExprNode(cExprNode* expr1, cOpNode* op, cExprNode* expr2) 
            : cExprNode() 
        {
            AddChild(expr1);
            AddChild(op);
            AddChild(expr2);
        }

        virtual cDeclNode* GetType()
        {
            // Get the type of both expr nodes
            cDeclNode* type1 = dynamic_cast<cExprNode*>(GetChild(0))->GetType();
            cDeclNode* type2 = dynamic_cast<cExprNode*>(GetChild(2))->GetType();

            // Else if either are a real, return real
            if (type1->IsReal())
                return type1;
            if (type2->IsReal())
                return type2;

            // Else if either are integer, return integer
            if (type1->IsInt())
                return type1;
            if (type2->IsInt())
                return type2;

            // Else if either are char, return char
            if (type1->IsChar())
                return type1;
            if (type2->IsChar())
                return type2;

            // Else semantic error "I can't do this operation"
            SemanticParseError("Invalid operation");
            return nullptr;
        }
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor* visitor) { visitor->Visit(this); }
};
