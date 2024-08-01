#pragma once
//**************************************
// cBaseTypeNode.h
//
// Defines a class to represent a variable's base type.
//
// Author: Dillon Wall
// dillon.wall@oit.edu
//

#include <string>
#include "cAstNode.h"
#include "cDeclNode.h"
#include "lex.h"

class cBaseTypeNode : public cDeclNode
{
    public:
        cBaseTypeNode(string name, int size, bool isFloat) : cDeclNode() 
        {
            m_name = name;
            m_size = size;
            m_isFloat = isFloat;
        }

        virtual cSymbol* GetNameSymbol()
        {
            if (IsChar())
                return g_SymbolTable.GlobalLookup("char");
            else if (IsInt())
                return g_SymbolTable.GlobalLookup("integer");
            else if (IsReal()) 
                return g_SymbolTable.GlobalLookup("real");
            
            return nullptr;
        }
        virtual bool IsChar()
        {
            return m_name == string("char");
        }
        virtual bool IsInt()
        {
            return m_name == string("integer");
        }
        virtual bool IsReal()
        {
            return m_name == string("real");
        }
        virtual bool IsType()
        {
            return true;
        }
        virtual string AttributesToString()
        {
            string result(" name=\"");
            result += m_name;
            result += "\" size=\"";
            result += std::to_string(m_size);
            result += "\" isFloat=\"";
            result += std::to_string(m_isFloat);
            result += "\"";

            return result;
        }
        virtual string NodeType() { return string("type"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        string m_name;          // the type name of the Base Type
        bool m_isFloat;         // is float
};
