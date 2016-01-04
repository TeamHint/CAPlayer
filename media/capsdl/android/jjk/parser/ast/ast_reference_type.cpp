

#include "ast_reference_type.hpp"
#include "ast_identifier.hpp"
#include "ast_class.hpp"
#include "ast__context.hpp"

using namespace ast;

bool ReferenceType::is_string_type()
{
    if (0 == get_name()->compare("String")) {
        if (0 == _get_java_long_name()->compare("java.lang.String")) {
            return true;
        }
    }

    return false;
}

bfc::string_ptr ReferenceType::_get_java_long_name()
{
    Identifier *Identifier = Context::instance()->find_identifier(this, get_name());
    if (Identifier) {
        if (get_is_array()) {
            std::ostringstream os;
            os << Identifier->get_java_long_name();
            os << "[]";
            return bfc::string::make_ptr(os);
        } else {
            return Identifier->get_java_long_name();
        }
    }

    return bfc::string::make_ptr("<unknown>");
}

bfc::string_ptr ReferenceType::get_c_type()
{
    if (get_is_array())
        return bfc::string::make_ptr("jobjectArray");

    if (is_string_type())
        return bfc::string::make_ptr("jstring");

    return bfc::string::make_ptr("jobject");
}

bfc::string_ptr ReferenceType::get_c_sign_in_method()
{
    Identifier::pointer_type Identifier = Context::instance()->find_identifier(this, get_name());
    if (Identifier) {
        std::ostringstream os;
        if (get_is_array())
            os << "[";
        os << "L" << Identifier->get_c_jni_sign() << ";";
        return bfc::string::make_ptr(os);
    }

    return bfc::string::make_ptr("<unknown>");
}
