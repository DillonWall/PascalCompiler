#pragma once
//**************************************
// cFuncDeclNode.h
//
// Defines a class to represent a function declaration node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cExprListNode.h"
#include "cBlockNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        // symbol (decl vardecls block) added after
        cFuncDeclNode(cSymbol* header) : cDeclNode() 
        {
            cSymbol* newSym = InsertHeader(header);

            // Dont add child if we already have one (insert can add all children)
            if (GetNameSymbol() == nullptr)
                AddChild(newSym);
        }

        cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        void AddType(cDeclNode* type)
        {
            // If there was a prototype, this->GetType() shouldnt be nullptr
            cDeclNode* thisType = GetType();
            if (thisType != nullptr)
            {
                // If there was a prototype, check for same type
                if (thisType != type)
                {
                    SemanticParseError(GetNameSymbol()->GetName() + 
                            " previsously declared with different return type");
                }

                SetChild(TYPE_CHILD_POS, type);
            }
            // Else, not a prototype, so add it as normal
            else
                AddChild(type);
        }

        virtual cDeclNode* GetType()
        {   
            // Type node is the second node (pos 1)
            return dynamic_cast<cDeclNode*>(GetChild(TYPE_CHILD_POS));
        }

        void AddParams(cVarDeclsNode* vars)
        {
            cVarDeclsNode* thisVars = GetParams();

            // If there was a prototype, this->GetParams() shouldnt be nullptr
            if (thisVars == nullptr)
            {
                if (vars == nullptr)
                    vars = new cVarDeclsNode(nullptr, nullptr);
                AddChild(vars);
            }
            // If they dont have the same num of vars
            else if (thisVars->GetNumChildren() != vars->GetNumChildren())
            {
                SemanticParseError(GetNameSymbol()->GetName() + 
                        " redeclared with different number of parameters");
            }
            // Else if there already is a params node, set it to the new one
            //  **We technically dont need to do this 
            else
                SetChild(PARAMS_CHILD_POS, vars);
        }

        int GetNumParams()
        {
            cVarDeclsNode* params = GetParams();
            if (params == nullptr)
                return 0;
            return params->GetNumChildren();
        }

        cVarDeclsNode* GetParams()
        {
            return dynamic_cast<cVarDeclsNode*>(GetChild(PARAMS_CHILD_POS));
        }

        cVarDeclNode* GetParam(int pos)
        {
            return dynamic_cast<cVarDeclNode*>(GetParams()->GetVarDecl(pos));
        }

        void AddBlock(cBlockNode* block)
        {

            // Check if block exists already, if so we double declared
            if (GetBlock() != nullptr && block != nullptr)
            {
                SemanticParseError(GetNameSymbol()->GetName() + 
                        " already has a definition");
            }
            // Ensure forward doesnt add block that doesnt exist
            else if (block == nullptr)
                SetChild(BLOCK_CHILD_POS, nullptr);
            // Else, add the block as normal
            else
                AddChild(block);
        }

        cBlockNode* GetBlock()
        {
            return dynamic_cast<cBlockNode*>(GetChild(BLOCK_CHILD_POS));
        }

        cSymbol* InsertHeader(cSymbol* sym)
        {
            // Dont use if nullptr
            if (sym == nullptr)
                return sym;

            string symName = sym->GetName();

            if (g_SymbolTable.GlobalLookup(symName) != nullptr)
            {
                // Check for error if is in local. If so, check if its decl was a func
                sym = g_SymbolTable.LocalLookup(symName); 
                if (sym != nullptr)
                {
                    // Get if the decl is a function or not
                    bool isFunc = false;
                    if (sym->GetDecl() != nullptr)
                        isFunc = sym->GetDecl()->IsFunc();
                    
                    // If the previous symbol is not a function, its been declared
                    //  as a different type
                    if (!isFunc)
                    {
                        SemanticParseError("Symbol " + symName + 
                            " already exists in current scope");
                    }
                    // Else, steal the children of the previous decl
                    else
                    {
                        AddAllChildren(sym->GetDecl());
                    }
                }
                else
                {
                    // The function was in the global but not local, therefore, we are
                    //      in a "new" function so create a new symbol
                    sym = new cSymbol(symName);
                }
            }
            else
            {
                g_SymbolTable.Insert(sym);
            }

            sym->SetDecl(this);

            return sym;
        }
       
        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
                retVal += " offset=\"" + std::to_string(m_offset) + "\"";
            }

            return retVal;
        }

        virtual bool IsFunc() { return true; }
        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
        static const int TYPE_CHILD_POS = 1;
        static const int PARAMS_CHILD_POS = 2;
        static const int BLOCK_CHILD_POS = 3;
};
