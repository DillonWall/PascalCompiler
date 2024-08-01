#pragma once
//**************************************
// cWhileNode.h
//
// Defines a class to represent a while node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cExprNode.h"
#include "cStmtNode.h"

class cWhileNode : public cStmtNode
{
    public:
        // WHILE  expr DO  stmt
        cWhileNode(cExprNode* expr, cStmtNode* stmt) 
            : cStmtNode() 
        {
            AddChild(expr);
            AddChild(stmt);
        }

        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
