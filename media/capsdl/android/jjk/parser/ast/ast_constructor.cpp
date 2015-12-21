

#include "ast_constructor.hpp"
#include "ast_class.hpp"

using namespace ast;

bfc::string_ptr Constructor::get_c_jni_sign()
{
    std::ostringstream os;
    os << "(";

    ArgumentList::iterator begin = get_argument_list()->begin();
    ArgumentList::iterator end   = get_argument_list()->end();
    for (NULL; begin != end; ++begin) {
        os << (*begin)->get_type()->get_c_sign_in_method();
    }

    os << ")V";
    return bfc::string::make_ptr(os);
}

bfc::string_ptr Constructor::get_c_jni_id_name()
{
    std::ostringstream os;
    os << "constructor_" << get_name();
    return bfc::string::make_ptr(os);
}

bfc::string_ptr Constructor::get_c_jni_method_name()
{
    return bfc::string::make_ptr("<init>");
}

bfc::string_ptr Constructor::get_c_call_api()
{
    return bfc::string::make_ptr("NewObject");
}

bfc::string_ptr Constructor::get_c_call_object_id()
{
    return get_this_class()->get_c_jni_id();
}

bool Constructor::get_c_call_need_this()
{
    return false;
}
