#pragma once
//**************************************
// cVarExprNode.h
//
// Defines a class to represent a variable expression reference.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cSymbol.h"
#include "cExprNode.h"
#include "cExprListNode.h"
#include "cArrayDeclNode.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol* symbol = nullptr) 
            : cExprNode()
        {
            if (symbol != nullptr)
                AddChild(symbol);
        }

        cSymbol* GetSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(SYM_CHILD_POS));
        }

        void AddVariable(cVarExprNode* varExpr)
        {
            AddSymbol(varExpr->GetSymbol());
        }

        int GetNumExprLists()
        {
            return NumChildren() - 1;
        }

        cExprListNode* GetExprList(int pos)
        {
            return dynamic_cast<cExprListNode*>(
                    GetChild(ACCESS_CHILD_POS_START + pos));
        }

        void AddExprList(cExprListNode* exprList)
        {
            AddChild(exprList);
        }

        void AddSymbol(cSymbol* symbol)
        {
            AddChild(symbol);
        }

        cDeclNode* GetVarDecl()
        {
            return GetSymbol()->GetDecl();
        }

        cDeclNode* GetBaseType()
        {
            cDeclNode* varDecl = GetSymbol()->GetDecl();

            if (varDecl == nullptr)
                return nullptr;

            return varDecl->GetType();
        }

        virtual cDeclNode* GetType()
        {
            cDeclNode* type = GetBaseType();
            // check for edge case
            if (type == nullptr)
                return nullptr;
            type = type->GetType();
            
            // check if its an array, if so, should return based on exprList
            if (type != nullptr && type->IsArray())
            {
                type = GetArrayExprType(type);
            }

            return type;
        }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
                retVal += " offset=\"" + std::to_string(m_offset) + "\"";

                if (GetBaseType()->GetType()->IsArray())
                {
                    retVal += " rowsizes=\"";
                    // add the first one
                    retVal += std::to_string(m_rowsizes.at(0));
                    for (unsigned int ii = 1; ii < m_rowsizes.size(); ++ii)
                    {
                        retVal += " " + std::to_string(m_rowsizes.at(ii));
                    }
                    retVal += "\"";

                    retVal += " startindexes=\"";
                    // add the first one
                    retVal += std::to_string(m_startindexes.at(0));
                    for (unsigned int ii = 1; ii < m_startindexes.size(); ++ii)
                    {
                        retVal += " " + std::to_string(m_startindexes.at(ii));
                    }
                    retVal += "\"";
                }
            }

            return retVal;
        }
        virtual bool IsVarExpr() { return true; }
        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int GetSize() { return m_size; }
        void SetSize(int value) { m_size = value; }
        int GetOffset() { return m_offset; }
        void SetOffset(int value) { m_offset = value; }
        void SetRowsizes(std::vector<int> value) { m_rowsizes = value; }
        void SetStartindexes(std::vector<int> value) { m_startindexes = value; }

    protected:
        static const int SYM_CHILD_POS = 0;
        static const int ACCESS_CHILD_POS_START = 1;

        int m_size;
        int m_offset;
        std::vector<int> m_rowsizes;
        std::vector<int> m_startindexes;

        // ---------------- HELPER FUNCTIONS ----------------- //
        cDeclNode* GetArrayExprType(cDeclNode* type)
        {
            // Check for setting array member, if so, lhs should change type
            cArrayDeclNode* arrayDecl;
            for (int ii = 0; ii < GetNumExprLists(); ++ii)
            {
                // check if this type is an array, then we are accessing
                //      a member from it
                if (type->IsArray())
                {
                    arrayDecl = dynamic_cast<cArrayDeclNode*>(type);
                    type = arrayDecl->GetMemberType();
                }
                else
                {
                    return nullptr;
                }
            }

            return type;
        }
};
