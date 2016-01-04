

#ifndef JJK_PARSER_AST__AST_METHOD__HPP
#define JJK_PARSER_AST__AST_METHOD__HPP

#include "ast__def.hpp"
#include "ast_member.hpp"
#include "ast_argument.hpp"

NAMESPACE_AST_BEGIN

class Method: public Member
{
public:
    AST_CHILD_DEFINE(ArgumentList,      argument_list);

    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_id_name);
    AST_GETTER_DECL(bfc::string_ptr,    c_jni_method_name);

    AST_GETTER_DECL(bfc::string_ptr,    c_call_api);
    AST_GETTER_DECL(bfc::string_ptr,    c_call_object_id);
    AST_GETTER_DECL(bfc::string_ptr,    c_call_method_id);
    AST_GETTER_DECL(bool,               c_call_need_this);

private:
    static const int FLAG_NORMAL;
    static const int FLAG_CATCH_ALL;
    static const int FLAG_WITH_C_STRING;
    static const int FLAG_AS_GLOBAL_REF;
    static const int FLAG_AS_C_BUFFER;

    bool _has_string_arg();

    void _build_class_id(std::ostream &os);
    void _build_c_call_jni_statement(std::ostream &os, int flags);
    void _build_c_func_name(std::ostream &os, int flags);
    void _build_c_func_decl_statement(std::ostream &os, int flags);
    void _build_c_func_call_statement(std::ostream &os, int flags);
    void _build_c_func_string_argument_cast_statements(std::ostream &os, int flags);
    void _build_c_func_string_argument_release_statements(std::ostream &os, int flags);
    void _build_c_func_impl_void_type_statement(std::ostream &os, int flags);
    void _build_c_func_impl_reference_type_statement(std::ostream &os, int flags);
    void _build_c_func_impl_basic_type_statement(std::ostream &os, int flags);

public:
    virtual void build_c_func_decl(std::ostream &os) override;
    // virtual void build_c_class_decl(std::ostream &os);
    virtual void build_c_member_id_decl(std::ostream &os) override;
    virtual void build_c_member_id_load(std::ostream &os) override;
    virtual void build_c_func_impl(std::ostream &os) override;

    // class Node
    // @Override
    virtual Method *get_this_method() override {return this;}
    // @Override
    virtual void debug_print(int indent) override {
        print_space(indent);

        get_modifier_set()->debug_print(0);
        get_type()->debug_print(0);
        printf(" %s(", get_name()->c_str());
        get_argument_list()->debug_print(0);
        printf(");\n");
    }

public:
    AST_IMPLEMENT(Method);
protected:
    explicit Method(const bfc::string_ptr &name): Member(name) {;}
public:
    static pointer_type make_ptr(const bfc::string_ptr& name) {return pointer_type(new Method(name));}
};

NAMESPACE_AST_END

#endif
