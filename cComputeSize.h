#pragma once
//*************************************************
// Visitor subclass which deals with AST node sizes and offsets
// 
// Author: Dillon Wall
// Email:  dillon.wall@oit.edu
//

#include "cVisitor.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : m_offset(0) {}

        virtual void VisitAllNodes(cAstNode *node) 
        {
            node->Visit(this); 
        }

        // A visit method for every AST node
        virtual void Visit(cArrayDeclNode *node)
        {
            node->VisitAllChildren(this);

            // Make sure this hasnt been computed already
            if (node->HasRowsizes())
                return;

            // Cycle through all ranges
            int running_mult = node->GetMemberType()->GetSize();
            for (int ii = 0; ii < node->GetNumRanges(); ++ii)
            {
                node->AddRowsize(running_mult);
                
                cRangeDeclNode* range = node->GetRange(ii);

                node->AddStartindex(range->GetStart());

                int range_diff = range->GetEnd() - range->GetStart() + 1;
                running_mult *= range_diff;
            }

            node->SetSize(running_mult);
        }
        //virtual void Visit(cAssignNode *node);
        //virtual void Visit(cAstNode *node);
        //virtual void Visit(cBaseTypeNode *node);
        //virtual void Visit(cBinaryExprNode *node)
        virtual void Visit(cBlockNode *node)
        {
            node->VisitAllChildren(this);

            GoToNextBound();
            node->SetSize(m_offset);
        }
        //virtual void Visit(cCompoundStmtNode *node);
        //virtual void Visit(cConstDeclNode *node);
        //virtual void Visit(cDeclNode *node);
        //virtual void Visit(cDeclsNode *node);
        //virtual void Visit(cExprListNode *node)    
        //virtual void Visit(cExprNode *node)
        virtual void Visit(cFuncDeclNode *node)
        {
            int start = m_offset;

            // Compute size
            node->SetSize(node->GetType()->GetSize());
            // Set offset to 0
            node->SetOffset(0);
            
            // Setup for args
            m_doArgs = true;
            m_offset = ARGS_START_OFFSET;
            cVarDeclsNode* params = node->GetParams();
            // Visit the params
            if (params != nullptr)
                params->Visit(this);

            // Go back to initial values and visit the block
            m_doArgs = false;
            m_offset = node->GetSize();
            cBlockNode* block = node->GetBlock();
            // Visit the block
            if (block != nullptr)
                block->Visit(this);
            
            // Go back to the original offset
            m_offset = start;
        }
        virtual void Visit(cFuncExprNode *node)
        {
            node->VisitAllChildren(this);

            cFuncDeclNode* funcDecl = 
                dynamic_cast<cFuncDeclNode*>(node->GetNameSymbol()->GetDecl());
            
            node->SetParamsize(funcDecl->GetParams()->GetSize());
        }
        //virtual void Visit(cIdListNode *node);
        //virtual void Visit(cIfNode *node);
        //virtual void Visit(cIntExprNode *node);
        //virtual void Visit(cNilNode *node);
        //virtual void Visit(cOpNode *node);
        virtual void Visit(cProcCallNode *node)
        {
            node->VisitAllChildren(this);

            cProcDeclNode* procDecl = 
                dynamic_cast<cProcDeclNode*>(node->GetNameSymbol()->GetDecl());
            
            node->SetParamsize(procDecl->GetParams()->GetSize());
        }
        virtual void Visit(cProcDeclNode *node)
        {
            int start = m_offset;

            // Compute size
            //node->SetSize(node->GetType()->GetSize());
            // Set offset to 0
            //node->SetOffset(0);
            
            // Setup for args
            m_doArgs = true;
            m_offset = ARGS_START_OFFSET;
            cVarDeclsNode* params = node->GetParams();
            // Visit the params
            if (params != nullptr)
                params->Visit(this);

            // Go back to initial values and visit the block
            m_doArgs = false;
            m_offset = node->GetSize();
            cBlockNode* block = node->GetBlock();
            // Visit the block
            if (block != nullptr)
                block->Visit(this);
            
            // Go back to the original offset
            m_offset = start;
        }
        //virtual void Visit(cProgramNode *node);
        //virtual void Visit(cRangeDeclNode *node);
        //virtual void Visit(cRealExprNode *node);
        //virtual void Visit(cRecordDeclNode *node);
        //virtual void Visit(cStmtNode *node);
        //virtual void Visit(cStmtsNode *node);
        //virtual void Visit(cSymbol *node);
        //virtual void Visit(cUnaryExprNode *node);
        virtual void Visit(cVarDeclNode *node)
        {
            cDeclNode* type = node->GetType();
            int size = type->GetSize();
         
            if (m_doArgs)
            {
                GoToNextBound();
                node->SetOffset(-m_offset); 
            }
            else
            {
                CheckAndGoToNextBound(size);
                node->SetOffset(m_offset); 
            }

            node->SetSize(size);
            
            IncrementOffset(size);
        }
        virtual void Visit(cVarDeclsNode *node)
        {
            int start = m_offset;

            node->VisitAllChildren(this);
            GoToNextBound();

            int offset_diff = std::abs(m_offset - start);
            node->SetSize(offset_diff);
        }
        virtual void Visit(cVarExprNode *node)
        {
            node->VisitAllChildren(this);

            cDeclNode* type = node->GetVarDecl();
        
            if (type == nullptr)
                return;

            if (type->GetType()->IsArray())
            {
                node->SetSize(node->GetType()->GetSize());

                cArrayDeclNode* arrDecl = 
                    dynamic_cast<cArrayDeclNode*>(type->GetType());

                node->SetRowsizes(arrDecl->GetRowsizes());
                node->SetStartindexes(arrDecl->GetStartindexes());
            }
            else
                node->SetSize(type->GetSize());

            node->SetOffset(type->GetOffset()); 
        }
        //virtual void Visit(cWhileNode *node);
        //virtual void Visit(cWriteNode *node);
        
    protected:
        static const int WORD_SIZE = 4;
        static const int ARGS_START_OFFSET = 12;
        int m_offset;
        bool m_doArgs;

        int ToNextBound()
        {
            int to_next_bound = 4 - (m_offset % WORD_SIZE);
            // if still 4, actually is 0 to next bound
            if (to_next_bound == 4)
                to_next_bound = 0;

            return to_next_bound;
        }

        void GoToNextBound()
        {
            m_offset += ToNextBound();
        }

        void CheckAndGoToNextBound(int size)
        {
            int to_next_bound = ToNextBound();

            // Check for if it will cross a word boundary
            //  If so, increment offset to next word boundary
            if (to_next_bound <= size)
                m_offset += to_next_bound;
        }

        void IncrementOffset(int size)
        {
            // now just increment offset by size
            m_offset += size;
        }
};
