

#ifndef JJK_PARSER_AST__AST_ANNOTATION__HPP
#define JJK_PARSER_AST__AST_ANNOTATION__HPP

#include "ast__def.hpp"
#include "ast_identifier.hpp"

NAMESPACE_AST_BEGIN

class Annotation: public Identifier
{
public:
    AST_PROPERTY_DEFINE(bfc::string_ptr, value);

    // @Override
    virtual void debug_print(int indent) override {
        if (get_value().is_null())
            printf("@%s\n", get_name()->c_str());
        else
            printf("@%s(%s)\n", get_name()->c_str(), get_value()->c_str());
    }

public:
    AST_IMPLEMENT(Annotation);
protected:
    explicit Annotation(const bfc::string_ptr &name): Identifier(name) {;}
    explicit Annotation(const bfc::string_ptr &name, const bfc::string_ptr& value): Identifier(name), AST_PROPERTY(value)(value) {;}
public:
    static pointer_type make_ptr(const bfc::string_ptr& name) {return pointer_type(new Annotation(name));}
    static pointer_type make_ptr(const bfc::string_ptr& name, const bfc::string_ptr& value) {return pointer_type(new Annotation(name, value));}
};

class Annotations: public IdentifierMap<Annotation>
{
public:
    // @Override
    virtual void debug_print(int indent) override {
        iterator begin = this->begin();
        iterator end   = this->end();

        for (NULL; begin != end; ++begin) {
            begin->second->debug_print(indent);
        }
    }

public:
    AST_IMPLEMENT(Annotations);
protected:
    explicit Annotations() {;}
public:
    static pointer_type make_ptr() {return pointer_type(new Annotations());}
};

NAMESPACE_AST_END

#endif
