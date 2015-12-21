

#include "ast__context.hpp"

#include "ast.hpp"

using namespace ast;

Context *Context::s_instance;

Namespace *Context::get_local_namespace()
{
    assert(!m_namespace_stack.empty());
    return m_namespace_stack.back();
}

void Context::push_local_namespace(Namespace *local_namespace)
{
    m_namespace_stack.push_back(local_namespace);
}

void Context::pop_local_namespace()
{
    assert(!m_namespace_stack.empty());
    m_namespace_stack.pop_back();
}

Identifier *Context::find_identifier(Node *node, const bfc::string_ptr& name)
{
    Identifier *qid = NULL;

    CompilationUnit *this_compilation_unit = node->get_this_compilation_unit();
    if (this_compilation_unit) {
        // before AST build
        Class *this_class = node->get_this_class();
        while (this_class) {
            qid = this_class->get_local_namespace()->find_identifier(name);
            if (qid)
                return qid;

            if (!this_class->get_parent())
                break;

            this_class = this_class->get_parent()->get_this_class();
        }

        qid = this_compilation_unit->get_local_namespace()->find_identifier(name);
        if (qid)
            return qid;
    } else {
        // after AST build
        NamespaceStack::reverse_iterator rbegin = m_namespace_stack.rbegin();
        NamespaceStack::reverse_iterator rend   = m_namespace_stack.rend();

        for (NULL; rbegin != rend; ++rbegin) {
            qid = (*rbegin)->find_identifier(name);
            if (qid)
                return qid;
        }
    }

    qid = get_global_name_space()->find_identifier(name);
    return qid;
}
