

#ifndef JJK_PARSER_AST__AST_ARGUMENT__HPP
#define JJK_PARSER_AST__AST_ARGUMENT__HPP

#include "ast__def.hpp"
#include "ast_type.hpp"

NAMESPACE_AST_BEGIN

class Argument: public Identifier
{
public:
    AST_CHILD_DEFINE(Type, type);

public:
    // @Override
    virtual void debug_print(int indent) override {
        get_type()->debug_print(0);
        printf(" %s", get_name()->c_str());
    }

public:
    AST_IMPLEMENT(Argument);
protected:
    explicit Argument(const bfc::string_ptr &name): Identifier(name) {;}
public:
    static pointer_type make_ptr(const bfc::string_ptr& name) {return pointer_type(new Argument(name));}
};

class ArgumentList: public NodeList<Argument>
{
public:
    // @Override
    virtual void debug_print(int indent) override {
        iterator begin = this->begin();
        iterator end   = this->end();

        if (begin != end) {
            (*begin)->debug_print(indent);
            ++begin;

            for (NULL; begin != end; ++begin) {
                printf(", ");
                (*begin)->debug_print(indent);
            }
        }
    }

public:
    AST_IMPLEMENT_ABSTRACT(ArgumentList);
protected:
    explicit ArgumentList() {;}
public:
    static pointer_type make_ptr() {return pointer_type(new ArgumentList());}
};

NAMESPACE_AST_END

#endif
