

#ifndef JJK_PARSER_AST__AST_CONSTRUCTOR__HPP
#define JJK_PARSER_AST__AST_CONSTRUCTOR__HPP

#include "ast__def.hpp"
#include "ast_method.hpp"
#include "ast_field.hpp"

NAMESPACE_AST_BEGIN

class Constructor: public Method
{
public:
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,   c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,   c_jni_id_name);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,   c_jni_method_name);

    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,   c_call_api);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,   c_call_object_id);
    AST_GETTER_DECL_OVERRIDE(bool,              c_call_need_this);

public:
    virtual void debug_print(int indent) override {
        print_space(indent);

        get_modifier_set()->debug_print(0);
        printf("%s(", get_name()->c_str());
        get_argument_list()->debug_print(0);
        printf(");\n");
    }

public:
    AST_IMPLEMENT(Constructor);
protected:
    explicit Constructor(const bfc::string_ptr &name): Method(name) {;}
public:
    static pointer_type make_ptr(const bfc::string_ptr& name) {return pointer_type(new Constructor(name));}
};

NAMESPACE_AST_END

#endif
