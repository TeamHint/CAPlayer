

#ifndef JJK_PARSER_AST__AST__NAMESPACE__HPP
#define JJK_PARSER_AST__AST__NAMESPACE__HPP

#include "ast__def.hpp"
#include "ast_identifier.hpp"

NAMESPACE_AST_BEGIN

class Namespace
{
public:
    typedef std::map<bfc::string_ptr, Identifier::pointer_type> IdentifierMap;
    typedef IdentifierMap::iterator iterator;

    AST_PROPERTY_DEFINE(Identifier::pointer_type, identifier);

    iterator begin() {return m_id_map.begin();}
    iterator end()   {return m_id_map.end();}

    void add_package_identifier(Identifier *package_identifier);
    void add_class_identifier(Identifier *class_identifier);
    template<class T>
    void add_class_identifiers(T begin, T end) {
        for (NULL; begin != end; ++begin) {
            add_class_identifier(*begin);
        }
    }

    Identifier *find_identifier(const bfc::string_ptr &name);

    void clear() {m_id_map.clear();}

private:
    IdentifierMap m_id_map;
};

NAMESPACE_AST_END

#endif
