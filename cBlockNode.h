#pragma once
//**************************************
// cBlockNode.h
//
// Defines AST node for a block of code (stuff inside {})
//
// Since blocks can take the place of statements, this class inherits from 
// cStmtNode
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclsNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

class cBlockNode : public cStmtNode
{
    public:
        // params are the decls and statements contained in the block
        cBlockNode(cDeclsNode *decls, cStmtsNode *statements)
            : cStmtNode(), m_size(0)
        {
            AddChild(decls);
            AddChild(statements);
        }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
            }

            return retVal;
        }


        virtual string NodeType() { return string("block"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

        int GetSize() { return m_size; }
        void SetSize(int value) { m_size = value; }

    protected:
        int m_size;
};
