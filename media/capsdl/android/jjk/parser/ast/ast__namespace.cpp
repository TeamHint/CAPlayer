

#include "ast__namespace.hpp"
#include <dirent.h>
#include <cstring>
#include "ast__context.hpp"
#include "ast_class.hpp"

using namespace ast;

void Namespace::add_package_identifier(Identifier *package_identifier)
{
    DIR *d;
    struct dirent *dir;

    assert(package_identifier);
    d = opendir(Context::instance()->get_java_class_dir().c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            const char *ext = strchr(dir->d_name, '.');
            if (ext && 0 == strcmp(ext, ".java")) {
                bfc::string_ptr class_name = bfc::string::make_ptr(dir->d_name, ext - dir->d_name);
                add_class_identifier(package_identifier->make_by_join(class_name).get());
            }
        }
        closedir(d);
    }
}

void Namespace::add_class_identifier(Identifier *class_identifier)
{
    bfc::string_ptr name        = class_identifier->get_name();
    bfc::string_ptr full_name   = class_identifier->get_java_long_name();
    m_id_map[name]      = class_identifier;
    m_id_map[full_name] = class_identifier;

    Identifier::pointer_type outer_class = class_identifier->get_outer_class_identifier();
    if (!outer_class)
        return;

    Identifier::pointer_type inner_identifier = Identifier::make_ptr(class_identifier->get_name());
    Identifier::pointer_type outer_identifier = inner_identifier;
    while (outer_class) {
        outer_identifier->set_prefix(Identifier::make_ptr(outer_class->get_name()));
        outer_identifier = outer_identifier->get_prefix();

        bfc::string_ptr          relative_name       = inner_identifier->get_java_long_name();
        Identifier::pointer_type relative_identifier = Identifier::parse(relative_name->c_str());
        m_id_map[relative_name] = relative_identifier;

        outer_class = outer_class->get_outer_class_identifier();
    }
}

Identifier *Namespace::find_identifier(const bfc::string_ptr &name)
{
    IdentifierMap::iterator find = m_id_map.find(name);
    return find == m_id_map.end() ? NULL : find->second.get();
}
