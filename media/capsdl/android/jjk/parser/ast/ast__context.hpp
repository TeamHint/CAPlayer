

#ifndef JJK_PARSER_AST__AST__CONTEXT__HPP
#define JJK_PARSER_AST__AST__CONTEXT__HPP

#include "ast__def.hpp"
#include "ast__namespace.hpp"
#include "ast_identifier.hpp"
#include <map>
#include <string>

NAMESPACE_AST_BEGIN

class QualifiedIdentifier;
class Class;

class Context
{
public:
    typedef std::vector<Namespace*> NamespaceStack;

    AST_PROPERTY_DEFINE(std::string,        h_file_path);
    AST_PROPERTY_DEFINE(std::string,        c_file_path);
    AST_PROPERTY_DEFINE(std::string,        java_class_dir);
    AST_PROPERTY_DEFINE(Namespace*,         global_name_space);

    Identifier *find_identifier(Node *node, const bfc::string_ptr& name);

    Namespace *get_local_namespace();
    void push_local_namespace(Namespace *local_namespace);
    void pop_local_namespace();

    bfc::string_ptr get_sign_in_method(bfc::string_ptr name);

private:
    Context() {
        Namespace *global_namespace = new Namespace();
        global_namespace->add_class_identifier(Identifier::parse("java.lang.Object"));
        global_namespace->add_class_identifier(Identifier::parse("java.lang.String"));
        set_global_name_space(global_namespace);
    }

public:
    static Context *instance() {
        if (!s_instance)
            s_instance = new Context();
        return s_instance;
    }

private:
    NamespaceStack m_namespace_stack;
    static Context *s_instance;
};

NAMESPACE_AST_END

#endif
