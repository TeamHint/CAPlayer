

#include "ast_identifier.hpp"

using namespace ast;

Identifier::pointer_type Identifier::get_outer_class_identifier()
{
    Identifier::pointer_type prefix = get_prefix();
    if (!prefix)
        return NULL;

    if (prefix->is_class_identifier())
        return prefix;

    return prefix->get_outer_class_identifier();
}

bfc::string_ptr Identifier::get_java_long_name()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_java_long_name();
        os << ".";
    }

    os << get_name();
    return bfc::string::make_ptr(os);
}

bfc::string_ptr Identifier::get_c_long_name()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_long_name();
        os << "_";
    }

    os << get_name();
    return bfc::string::make_ptr(os);
}

bfc::string_ptr Identifier::get_c_jni_sign()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_jni_sign();
        os << "/";
    }

    os << get_name();
    return bfc::string::make_ptr(os);
}

bfc::string_ptr Identifier::get_fs_long_path()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_fs_long_path();
        os << "/";
    }

    os << get_name();
    return bfc::string::make_ptr(os);
}



bfc::string_ptr ClassIdentifier::get_c_jni_sign()
{
    std::ostringstream os;

    Identifier::pointer_type prefix = get_prefix();
    if (prefix) {
        os << prefix->get_c_jni_sign();
        if (get_outer_class_identifier())
            os << "$";
        else
            os << "/";
    }

    os << get_name();
    return bfc::string::make_ptr(os);
}
