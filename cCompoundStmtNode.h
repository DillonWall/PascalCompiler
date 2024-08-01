#pragma once
//**************************************
// cCompoundStmtNode.h
//
// Defines a class to represent a compound statment node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cStmtsNode.h"
#include "cStmtNode.h"

class cCompoundStmtNode : public cStmtNode
{
    public:
        // OPEN stmts CLOSE
        cCompoundStmtNode(cStmtsNode* stmts) 
            : cStmtNode() 
        {
            AddAllChildren(stmts);
        }
        
        virtual string NodeType() { return string("compound"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
