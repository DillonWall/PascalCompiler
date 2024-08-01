#pragma once
//**************************************
// cIfNode.h
//
// Defines a class to represent an if statement node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cStmtNode.h"
#include "cExprNode.h"

class cIfNode : public cStmtNode
{
    public:
        // IF expr THEN stmt [ELSE stmt]
        cIfNode(cExprNode* expr, cStmtNode* ifStmt, cStmtNode* elseStmt = nullptr) 
            : cStmtNode() 
        {
            AddChild(expr);
            AddChild(ifStmt);
            if (elseStmt != nullptr)
                AddChild(elseStmt);
        }

        virtual string NodeType() { return string("if"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
