#pragma once
//**************************************
// cArrayDeclNode.h
//
// Defines a class to represent an array declaration node.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include "cDeclNode.h"
#include "cSymbol.h"
#include "cDeclsNode.h"
#include "cRangeDeclNode.h"
#include <vector>

class cArrayDeclNode : public cDeclNode
{
    public:
        // symbol decl decls
        cArrayDeclNode(cSymbol* name, cDeclNode* type, cDeclsNode* ranges) 
            : cDeclNode(), m_rowsizes(), m_startindexes()
        {
            AddChild(InsertHeader(name));
            AddChild(type);
            AddChild(ranges);
        }

        cSymbol* InsertHeader(cSymbol* sym)
        {
            // Dont use if nullptr
            if (sym == nullptr)
                return sym;

            string symName = sym->GetName();

            if (g_SymbolTable.GlobalLookup(symName) != nullptr)
                sym = new cSymbol(symName);

            sym->SetIsType(true);
            sym->SetDecl(this);
            g_SymbolTable.Insert(sym);

            return sym;
        }

        cDeclNode* GetMemberType()
        {
            return dynamic_cast<cDeclNode*>(GetChild(TYPE_CHILD_POS));
        }

        int GetNumRanges()
        {
            return GetRanges()->GetNumChildren();
        }

        cDeclsNode* GetRanges()
        {
            return dynamic_cast<cDeclsNode*>(GetChild(RANGES_CHILD_POS));
        }

        cRangeDeclNode* GetRange(int pos)
        {
            return dynamic_cast<cRangeDeclNode*>(GetRanges()->GetDecl(pos));
        }

        int GetRowsize(int pos) { return m_rowsizes.at(pos); }
        void AddRowsize(int size) { m_rowsizes.push_back(size); }
        std::vector<int> GetRowsizes() { return m_rowsizes; }
        int GetStartindex(int pos) { return m_startindexes.at(pos); }
        void AddStartindex(int index) { m_startindexes.push_back(index); }
        std::vector<int> GetStartindexes() { return m_startindexes; }

        bool HasRowsizes() { return !m_rowsizes.empty(); }

        virtual string AttributesToString()
        {
            string retVal = "";

            if (m_size != 0)
            {
                retVal += " size=\"" + std::to_string(m_size) + "\"";
                //retVal += " offset=\"" + std::to_string(m_offset) + "\"";
                
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

            return retVal;
        }

        virtual cSymbol* GetNameSymbol()
        {
            return dynamic_cast<cSymbol*>(GetChild(NAME_CHILD_POS));
        }

        virtual bool IsArray()
        {
            return true;
        }
        virtual bool IsType()
        {
            return true;
        }
        virtual string NodeType() { return string("array"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        static const int NAME_CHILD_POS = 0;
        static const int TYPE_CHILD_POS = 1;
        static const int RANGES_CHILD_POS = 2;

        std::vector<int> m_rowsizes;
        std::vector<int> m_startindexes;
};
