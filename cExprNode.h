#pragma once
//**************************************
// cExprNode.h
//
// Defines base class for all expressions
//
// Author: Phil Howard 
// phil.howard@oit.edu
// 
// Modified by: Dillon Wall
// dillon.wall@oit.edu
//

#include "cStmtNode.h"

class cExprNode : public cStmtNode
{
    public:
        cExprNode() : cStmtNode() {}

        virtual cDeclNode* GetType() { return nullptr; }
        virtual bool IsVarExpr() { return false; }
};
