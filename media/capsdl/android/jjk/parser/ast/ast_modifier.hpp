

#ifndef JJK_PARSER_AST__AST_MODIFIER__HPP
#define JJK_PARSER_AST__AST_MODIFIER__HPP

#include <set>
#include "ast__def.hpp"
#include "ast_node.hpp"

NAMESPACE_AST_BEGIN

class ModifierSet: public Node
{
public:
    typedef std::set<int>::iterator iterator;

    iterator begin() {return m_modifier_set.begin();}
    iterator end()   {return m_modifier_set.end();}

    size_t size() {return m_modifier_set.size();}
    bool   has_token(int token) {return m_modifier_set.find(token) != end();}
    void   insert_token(int token) {
        switch (token) {
            case T_PUBLIC:
            case T_PRIVATE:
            case T_PROTECTED:
                if (has_token(T_PUBLIC) || has_token(T_PRIVATE) || has_token(T_PROTECTED)) {
                    printf("[Error]: multiple public/private/protected modifier!\n");
                }
                break;
        }
        m_modifier_set.insert(token);
    }

    bool is_public()    {return has_token(T_PUBLIC);}
    bool is_private()   {return has_token(T_PRIVATE);}
    bool is_protected() {return has_token(T_PROTECTED);}
    bool is_static()    {return has_token(T_STATIC);}
    bool is_final()     {return has_token(T_FINAL);}

public:
    std::set<int> m_modifier_set;

public:
    // @Override
    virtual void debug_print(int indent) override {
        print_space(indent);

        if (is_public())
            printf("public ");
        else if (is_protected())
            printf("protected ");
        else if (is_private())
            printf("private ");

        if (is_static())
            printf("static ");
        if (is_final())
            printf("final ");
    }

public:
    AST_IMPLEMENT(ModifierSet);
protected:
    explicit ModifierSet() {;}
    explicit ModifierSet(ModifierSet *other): Node(other), m_modifier_set(other->m_modifier_set) {;}
public:
    static pointer_type make_ptr() {return pointer_type(new ModifierSet());}
};

NAMESPACE_AST_END

#endif
