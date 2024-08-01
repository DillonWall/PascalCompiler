#pragma once
//**************************************
// cProcCallNode.h
//
// Defines a class to represent a procedure call node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cSymbol.h"
#include "cStmtNode.h"
#include "cExprListNode.h"

class cProcCallNode : public cStmtNode
{
    public:
        // symbol ( exprList ) ;
        cProcCallNode(cSymbol* procName, cExprListNode* exprList = nullptr) 
            : cStmtNode(), m_paramSize(0)
        {
            AddChild(procName);
            AddChild(exprList);
        }

        cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        void SetParamsize(int value) { m_paramSize = value; }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_paramSize != 0)
            {
                retVal += " paramSize=\"" + std::to_string(m_paramSize) + "\"";
            }

            return retVal;
        }

        virtual string NodeType() { return string("procCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
        int m_paramSize;
};
