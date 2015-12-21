

#ifndef JJK_PARSER_AST__AST_FIELD__HPP
#define JJK_PARSER_AST__AST_FIELD__HPP

#include "ast__def.hpp"
#include "ast_member.hpp"

NAMESPACE_AST_BEGIN

class Field: public Member
{
public:
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_id_name);

public:
    // class Member
    virtual void build_c_func_decl(std::ostream &os) override;
    // virtual void build_c_class_decl(std::ostream &os) override {;}
    virtual void build_c_member_id_decl(std::ostream &os) override;
    virtual void build_c_member_id_load(std::ostream &os) override;
    virtual void build_c_func_impl(std::ostream &os) override;

    // class Node
    // @Override
    virtual void debug_print(int indent) override {
        print_space(indent);

        get_modifier_set()->debug_print(0);
        get_type()->debug_print(0);
        printf(" %s;\n", get_name()->c_str());
    }

public:
    AST_IMPLEMENT(Field);
protected:
    explicit Field(const bfc::string_ptr &name): Member(name) {;}
public:
    static pointer_type make_ptr(const bfc::string_ptr& name) {return pointer_type(new Field(name));}
};

NAMESPACE_AST_END

#endif
