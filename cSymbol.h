#pragma once
//*********************************************************
// cSymbol.h
//
// cSymbol class declaration.
// cSymbols are objects that represent identifiers and other such strings in 
// the compiler.
//
// Author: Phil Howard
// phil.howard@oit.edu
// 
// Modified by: Dillon Wall
// dillon.wall@oit.edu
//

#include <string>
#include <utility>
#include "cAstNode.h"
#include "pascalparse.h"
#include "cVisitor.h"

using std::string;

class cSymbol : public cAstNode
{
    public:
        cSymbol(string name, int id = -1, bool isType = false, 
                cDeclNode* decl = nullptr)
        {
            if (id == -1)
            {
                m_id = ++nextId;
                m_tokenType = IDENTIFIER;
            }
            else
            {
                m_id = id;
                m_tokenType = id;
            }

            m_name = name;
            m_isType = isType;
            m_decl = decl;
        }

        // Used to print cSymbols
        string ToString()
        {
            string result("<sym id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\" />";

            return result;
        }

        // return the name of the cSymbol
        string GetName() { return m_name; }

        void SetIsType(bool val) { m_isType = val; }
        bool IsType() { return m_isType; }

        // Set the decl
        void SetDecl(cDeclNode* decl) { m_decl = decl; }
        // Get the decl
        cDeclNode* GetDecl() { return m_decl; }

        // return the token type
        int GetTokenType() { return m_tokenType; }
        // setter for token type (used for type id's)
        void SetTokenType(int tokenType) { m_tokenType = tokenType; }


        virtual string AttributesToString()
        {
            // Code snippet from Phil Howard. returns id and name as string
            //  in the format for the xml file
            string result(" id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\"";
            return result;                     
        }
        virtual string NodeType() { return string("sym"); }
        virtual void Visit(cVisitor* visitor) { visitor->Visit(this); }
    protected:
        static long long nextId;    // used to generate unique IDs
        long long m_id;             // ID for this cSymbol
        string m_name;              // name for this cSymbol
        int m_tokenType;            // returns what token this is to yylex()
        bool m_isType;              // used to return TYPE_ID in scanner
        cDeclNode* m_decl;    // decl of the type
};
