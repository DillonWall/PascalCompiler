#pragma once
//**************************************
// cAssignNode.h
//
// Defines a class to assign a var expr to some expr.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cStmtNode.h"
#include "cVarExprNode.h"
#include "cExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        cAssignNode(cVarExprNode* varExpr = nullptr, cExprNode* expr = nullptr) 
            : cStmtNode()
        {
            if (varExpr != nullptr)
                AddChild(varExpr);
            if (expr != nullptr)
                AddChild(expr);
        }

        cVarExprNode* GetLValue()
        {
            return dynamic_cast<cVarExprNode*>(GetChild(LVAL_CHILD_POS));
        }

        cExprNode* GetRValue()
        {
            return dynamic_cast<cExprNode*>(GetChild(RVAL_CHILD_POS));
        }

        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    protected:
        static const int LVAL_CHILD_POS = 0;
        static const int RVAL_CHILD_POS = 1;
};
