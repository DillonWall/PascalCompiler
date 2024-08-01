#pragma once
//**************************************
// cVarDeclNode.h
//
// Defines a class to represent a variable declaration section.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cDeclsNode.h"
#include "cVarDeclNode.h"
#include "cIdListNode.h"
#include "cBaseTypeNode.h"

class cVarDeclsNode : public cDeclsNode
{
    public:
        // Each var decls takes in a IdList and base type 
        //      and creates a child for each id
        // Then, cVarDecls lists are added to each other to create 
        //      one cVarDecls list with all vars (in the parser)
        cVarDeclsNode(cIdListNode* idList, cDeclNode* type) 
            : cDeclsNode(), m_size(0)
        {
            if (idList != nullptr)
            {
                // Get the next child from idList, 
                //      then add a new var decl with this
                cSymbol* child;
                for (int ii = 0; ii < idList->GetNumChildren(); ++ii)
                {
                    child = idList->GetSymbol(ii);
                    AddChild(new cVarDeclNode(child, type));
                }
            }
        }

        void AddVarDecl(cVarDeclNode* decl)
        {
            AddChild(decl);
        }

        void AddVarDecls(cVarDeclsNode* decls)
        {
            AddAllChildren(decls);
        }

        cVarDeclNode* GetVarDecl(int pos)
        {
            return dynamic_cast<cVarDeclNode*>(GetChild(pos));
        }

        int GetSize() { return m_size; }
        void SetSize(int value) { m_size = value; }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
            }

            return retVal;
        }
        virtual string NodeType() { return string("var_decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        int m_size;
};
