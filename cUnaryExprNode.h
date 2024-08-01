#pragma once
//**************************************
// cUnaryExprNode.h
//
// Defines unary expressions
//
// Modified By: Dillon Wall
// dillon.wall@oit.edu
//

#include "cExprNode.h"

class cUnaryExprNode : public cExprNode
{
    public:
        cUnaryExprNode(cOpNode* op, cExprNode* expr) : cExprNode() 
        {
            AddChild(op);
            AddChild(expr);
        }

        cExprNode* GetExpr()
        {
            return dynamic_cast<cExprNode*>(GetChild(EXPR_CHILD_POS));
        }

        virtual cDeclNode* GetType()
        {
            // Get the type of the expr node and return it
            cExprNode* expr = GetExpr();
            if (expr == nullptr)
                return nullptr;
            return expr->GetType();
        }
        virtual string NodeType() { return string("unaryExpr"); }
        virtual void Visit(cVisitor* visitor) { visitor->Visit(this); }

    protected:
        static const int EXPR_CHILD_POS = 1;
};
