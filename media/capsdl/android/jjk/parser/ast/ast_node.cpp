

#include "ast_node.hpp"
#include "ast_compilation_unit.hpp"

using namespace ast;

Method *Node::get_this_method()
{
    if (!get_parent())
        return NULL;

    return get_parent()->get_this_method();
}

CompilationUnit *Node::get_this_compilation_unit()
{
    if (!get_parent())
        return NULL;

    return get_parent()->get_this_compilation_unit();
}

Class *Node::get_this_class()
{
    if (!get_parent())
        return NULL;

    return get_parent()->get_this_class();
}

Identifier *Node::get_this_package()
{
    if (!get_this_compilation_unit())
        return NULL;

    return get_this_compilation_unit()->get_package();
}
