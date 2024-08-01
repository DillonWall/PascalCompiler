#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
// 
// Modified by: Dillon Wall
// dillon.wall@oit.edu
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode(), m_size(0), m_offset(0) {}

        virtual bool IsReal()  { return false; }
        virtual bool IsInt()   { return false; }
        virtual bool IsChar()  { return false; }
        virtual bool IsType()  { return false; }
        virtual bool IsFunc()  { return false; }
        virtual bool IsArray() { return false; }
        virtual cDeclNode* GetType() { return this; }
        virtual cSymbol* GetNameSymbol() = 0;
        
        bool IsCompatableWith(cDeclNode* otherType)
        {
            if (IsChar())
            {
                // char cant be assigned an int
                if (otherType->IsInt())
                {
                    return false;
                }
                // char cant be assigned a real
                else if(otherType->IsReal())
                {
                    return false;
                }
            }
            // int cant be assigned a real
            else if (IsInt() && otherType->IsReal())
            {
                return false;
            }

            // If lval is a type but not an int, real, or char
            //      Get type and get the name of it
            bool lValIsType = !IsChar() 
                    && !IsInt()
                    && !IsReal()
                    && IsType();
            bool rValIsType = !otherType->IsChar() 
                    && !otherType->IsInt()
                    && !otherType->IsReal()
                    && otherType->IsType(); 
            if (lValIsType || rValIsType)
            {
                // lval is custom type, check if the symbol is the same as rhs
                cSymbol* lValSym = GetNameSymbol();
                cSymbol* rValSym = otherType->GetNameSymbol();

                if (lValSym == nullptr)
                    return false;
                if (rValSym == nullptr)
                    return false;

                if (lValSym != rValSym)
                {                    
                    return false;
                }
            }

            return true;
        }

        int GetSize() { return m_size; }
        void SetSize(int value) { m_size = value; }
        int GetOffset() { return m_offset; }
        void SetOffset(int value) { m_offset = value; }

    protected:
        int m_size;
        int m_offset;
};
