

#ifndef JJK_PARSER_AST__AST_CLASS__HPP
#define JJK_PARSER_AST__AST_CLASS__HPP

#include "ast__def.hpp"
#include "ast__namespace.hpp"
#include "ast_member.hpp"

NAMESPACE_AST_BEGIN

class Class: public Member
{
public:
    AST_PROPERTY_DEFINE(Namespace*,     local_namespace);
    AST_PROPERTY_DEFINE(bool,           is_interface);

    AST_CHILD_DEFINE(MemberList,        member_list);

    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_sign);
    AST_GETTER_DECL_OVERRIDE(bfc::string_ptr,    c_jni_id_name);

public:
    bfc::string_ptr get_c_jni_class_instance() {
        std::ostringstream os;
        os << "class_" << get_c_class_name();
        return bfc::string::make_ptr(os);
    }

    bool is_simple_c_class_name() {
        return get_annotation_at("SimpleCClassName") != NULL;
    }

    bool is_include_util() {
        return get_annotation_at("IncludeUtil") != NULL;   
    }

public:
    // class Member
    // @Override
    virtual void build_c_func_decl(std::ostream &os) override;
    // @Override
    virtual void build_c_class_decl(std::ostream &os) override;
    // @Override
    // virtual void build_c_member_id_decl(std::ostream &os) override;
    // @Override
    virtual void build_c_member_id_load(std::ostream &os) override;
    // @Override
    virtual void build_c_func_impl(std::ostream &os) override;

    // class Identifier
    virtual bfc::string_ptr get_java_long_name() override {
        if (get_parent()) {
            std::ostringstream os;
            if (get_parent()->get_this_class()) {
                // inner class
                os << get_parent()->get_this_class()->get_java_long_name();
                os << "$";
            } else {
                os << get_parent()->get_this_package()->get_java_long_name();
                os << ".";
            }
            os << get_name();
            return bfc::string::make_ptr(os);
        } else {
            return Member::get_java_long_name();
        }
    }

    // class Node
    // @Override
    virtual Class *get_this_class() override {return this;}

    bfc::string_ptr get_c_class_name() {
        std::ostringstream os;
        if (get_parent()->get_this_class()) {
            // inner class
            os << get_parent()->get_this_class()->get_c_class_name();
            os << "__";
        } else if (!is_simple_c_class_name()) {
            os << "JJKC_";
            os << get_this_package()->get_c_long_name();
            os << "_";
        } else {
            os << "JJKC_";
        }
        os << get_name();
        return bfc::string::make_ptr(os);
    }

    // @Override
    virtual void debug_print(int indent) override {
        get_annotations()->debug_print(indent);
        get_modifier_set()->debug_print(indent);
        if (get_is_interface()) {
            printf("class ");
        } else {
            printf("interface ");
        }
        printf("%s {\n", get_name()->c_str());
        get_member_list()->debug_print(indent + 4);
        print_space(indent); printf("};\n");
    }

public:
    AST_IMPLEMENT(Class);
protected:
    // FIXME:: implement copy-constructor
    explicit Class(Identifier *other): Member(other) {init(other);}
    explicit Class(Class *other): Member(other) {init(other);}
private:
    void init(Node *other) {
        set_is_interface(false);
        set_local_namespace(new Namespace());
    }
public:
    static pointer_type make_ptr(Identifier *identifier) {return pointer_type(new Class(identifier));}
};



NAMESPACE_AST_END

#endif
