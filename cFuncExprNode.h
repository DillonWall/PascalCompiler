#pragma once
//**************************************
// cFuncExprNode.h
//
// Defines a class to represent a function call node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cSymbol.h"
#include "cExprNode.h"
#include "cExprListNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        // symbol ( exprList ) ;
        cFuncExprNode(cSymbol* funcName, cExprListNode* exprList = nullptr) 
            : cExprNode(), m_paramSize(0)
        {
            AddChild(funcName);
            AddChild(exprList);
        }

        cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        int GetNumParams()
        {
            cExprListNode* params = GetParams();
            if (params == nullptr)
                return 0;
            return params->GetNumChildren();
        }

        cExprListNode* GetParams()
        {
            return dynamic_cast<cExprListNode*>(GetChild(PARAMS_CHILD_POS));
        }

        cExprNode* GetParam(int pos)
        {
            return dynamic_cast<cExprNode*>(GetParams()->GetExpr(pos));
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
        virtual cDeclNode* GetType()
        {
           // symbol contains cFuncDeclNode* as its decl. Call GetDecl
           // From this, call GetType() and virtual override will call funcDecl's GetType
           cDeclNode* decl = GetNameSymbol()->GetDecl();
           cFuncDeclNode* funcDecl = dynamic_cast<cFuncDeclNode*>(decl);
           if (funcDecl == nullptr)
               return nullptr;
           return funcDecl->GetType();
        }
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
        static const int PARAMS_CHILD_POS = 1;
        int m_paramSize;
};
