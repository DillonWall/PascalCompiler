#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl = nullptr) : cAstNode()
        {
            if (decl != nullptr) AddChild(decl);
        }

        // Copy all the decls from another node into this one
        void AddDecls(cDeclsNode *decls) { AddAllChildren(decls); }

        // Add another decl to the list
        void AddDecl(cDeclNode *decl) { AddChild(decl); }

        // Returns how many children. Useful for deciding whether or not
        //      to show the decls tag
        int GetNumChildren() { return NumChildren(); }

        cDeclNode* GetDecl(int pos)
        {
            return dynamic_cast<cDeclNode*>(GetChild(pos));
        }

        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
