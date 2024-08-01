#pragma once
//*************************************************
// Visitor subclass which deals with AST node semantics
// 
// Author: Dillon Wall
// Email:  dillon.wall@oit.edu
//

#include "cVisitor.h"

class cSemantics : public cVisitor
{
    public:
        cSemantics() {}

        virtual void VisitAllNodes(cAstNode *node) { node->Visit(this); }

        // A visit method for every AST node
        //virtual void Visit(cArrayDeclNode *node);
        virtual void Visit(cAssignNode *node)
        {
            node->VisitAllChildren(this);
            if (node->HasSemanticError())
                return;
            
            cDeclNode* lValType = node->GetLValue()->GetType();
            cDeclNode* rValType = node->GetRValue()->GetType();

            if (lValType == nullptr)
                return;
            if (rValType == nullptr)
                return;

            // If not compatable, the rhs cannot be assigned to the lhs
            if (!lValType->IsCompatableWith(rValType))
            {
                string lValName = lValType->GetNameSymbol()->GetName();
                string rValName = rValType->GetNameSymbol()->GetName();
                node->SemanticError("Cannot assign " + rValName
                      + " to " + lValName);
                return;   
            }
        }
        //virtual void Visit(cAstNode *node);
        //virtual void Visit(cBaseTypeNode *node);
        //virtual void Visit(cBinaryExprNode *node);
        //virtual void Visit(cBlockNode *node);
        //virtual void Visit(cCompoundStmtNode *node);
        //virtual void Visit(cConstDeclNode *node);
        //virtual void Visit(cDeclNode *node);
        //virtual void Visit(cDeclsNode *node);
        //virtual void Visit(cExprListNode *node);
        //virtual void Visit(cExprNode *node);
        //virtual void Visit(cFuncDeclNode *node);
        virtual void Visit(cFuncExprNode *node)
        {
            node->VisitAllChildren(this);
            cSymbol* sym = node->GetNameSymbol();
            cDeclNode* decl = sym->GetDecl();
            
            // if the decl isnt found in the symbol, it doesnt have a type and is not
            //      declared
            if (decl == nullptr)
            {
                node->SemanticError(sym->GetName() + " is not declared");
                return;
            }
            // if the decl is not a function, this is a semantic error
            if (!decl->IsFunc())
            {
                node->SemanticError(sym->GetName() + " is not a function");
                return;
            }

            cFuncDeclNode* funcDecl = dynamic_cast<cFuncDeclNode*>(decl);
            // if the func decl doesnt have a block it wasnt defined
            if (funcDecl->GetBlock() == nullptr)
            {
                node->SemanticError(sym->GetName() + " is not fully defined");
                return;
            }
            // if the number of params are different between the expr node and the 
            //      decl node, we used the wrong number of arguments in the expra
            int numParams = node->GetNumParams();
            if (funcDecl->GetNumParams() != numParams)
            {
                node->SemanticError(sym->GetName() + 
                        " called with wrong number of arguments");
                return;
            }

            // Number params are the same,
            // Check that each param called is compatible with its decl equivalent
            for (int ii = 0; ii < numParams; ++ii)
            {
                // check if decl from each at this pos is the same
                cDeclNode* declDecl = funcDecl->GetParam(ii)->GetType();
                cDeclNode* exprDecl = node->GetParam(ii)->GetType();

                if (!declDecl->IsCompatableWith(exprDecl))
                {
                    string lValName = declDecl->GetNameSymbol()->GetName();
                    string rValName = exprDecl->GetNameSymbol()->GetName();
                    node->SemanticError("Cannot assign " + rValName
                          + " to " + lValName);
                    return;   
                }
            }
        }
        //virtual void Visit(cIdListNode *node);
        //virtual void Visit(cIfNode *node);
        //virtual void Visit(cIntExprNode *node);
        //virtual void Visit(cNilNode *node);
        //virtual void Visit(cOpNode *node);
        //virtual void Visit(cProcCallNode *node);
        //virtual void Visit(cProcDeclNode *node);
        //virtual void Visit(cProgramNode *node);
        //virtual void Visit(cRangeDeclNode *node);
        //virtual void Visit(cRealExprNode *node);
        //virtual void Visit(cRecordDeclNode *node);
        //virtual void Visit(cStmtNode *node);
        //virtual void Visit(cStmtsNode *node);
        //virtual void Visit(cSymbol *node);
        //virtual void Visit(cUnaryExprNode *node);
        //virtual void Visit(cVarDeclNode *node);
        //virtual void Visit(cVarDeclsNode *node);
        virtual void Visit(cVarExprNode *node)
        {
            node->VisitAllChildren(this);
            if (node->HasSemanticError())
                return;

            cDeclNode* type = node->GetType();
            cDeclNode* baseType = node->GetBaseType();

            // make sure the GetType didnt already throw an error
            if (node->HasSemanticError())
                return;

            // If there is no type associated with this varExpr,it hasnt been defined
            //      (also error if not a base type or function)
            if (type == nullptr)
            {
                node->SemanticError("Variable " + node->GetSymbol()->GetName() 
                        + " is not defined");
                return;
            }

            // if this is not an array (at its base), 
            //      then if there are expressions throw sem err
            else if (!baseType->IsArray() && node->GetNumExprLists() > 0)
            {
                node->SemanticError(node->GetSymbol()->GetName() 
                        + " is not an array");
                return;
            }
            else if (baseType->IsArray())
            {
                cArrayDeclNode* arrayDecl;
                int exprListNumChildren;
                // loop through exprs and check semantic errors
                for (int ii = 0; ii < node->GetNumExprLists(); ++ii)
                {
                    if (baseType->IsArray())
                    {
                        arrayDecl = dynamic_cast<cArrayDeclNode*>(baseType);
                        baseType = arrayDecl->GetMemberType();
                        cExprListNode* exprList = node->GetExprList(ii);
                        exprListNumChildren = exprList->GetNumChildren();

                        // Check if there isnt a pos for each range
                        if (arrayDecl->GetNumRanges() != exprListNumChildren)
                        {
                            string exprName = node->GetSymbol()->GetName();
                            node->SemanticError(exprName +
                                    " does not have the correct number of indexes");
                            return;
                        }

                        // Check each child and make sure it is either an int or char
                        for (int jj = 0; jj < exprListNumChildren; ++jj)
                        {
                            cDeclNode* exprType = exprList->GetExpr(jj)->GetType();
                            if (!(exprType->IsChar() || exprType->IsInt()))
                            {
                                string exprName = node->GetSymbol()->GetName();
                                node->SemanticError("Index of " + exprName +
                                        " is not an integer");
                                return;
                            }
                        }
                    }
                    else
                    {
                        //// Sub expression is not an array
                        //node->SemanticError(node->GetSymbol()->GetName() 
                        //        + " is not an array");
                        //return;
                    }
                }
            }
        }
        //virtual void Visit(cWhileNode *node);
        //virtual void Visit(cWriteNode *node);
};
