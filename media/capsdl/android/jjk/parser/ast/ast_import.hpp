

#ifndef JJK_PARSER_AST__AST_IMPORT__HPP
#define JJK_PARSER_AST__AST_IMPORT__HPP

#include "ast__def.hpp"
#include "ast_node.hpp"
#include "ast_identifier.hpp"

NAMESPACE_AST_BEGIN

class ImportList: public NodeList<Identifier>
{
public:
    // @Override
    virtual void debug_print(int indent) override {
        if (size() > 0) {
            printf("\n");

            iterator begin = this->begin();
            iterator end   = this->end();

            for (NULL; begin != end; ++begin) {
                printf("import ");
                (*begin)->debug_print(indent);
                printf(";\n");
            }
        }
    }

public:
    AST_IMPLEMENT(ImportList);
protected:
    explicit ImportList() {;}
public:
    static pointer_type make_ptr() {return pointer_type(new ImportList());}
};

NAMESPACE_AST_END

#endif
