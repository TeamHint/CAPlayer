

#include "ast_property_accessor.hpp"
#include "ast_class.hpp"

using namespace ast;

bfc::string_ptr PropertyGetter::get_c_call_api()
{
    if (is_static()) {
        return get_field()->get_type()->get_c_get_static_field_api();
    } else {
        return get_field()->get_type()->get_c_get_instance_field_api();
    }
}

bfc::string_ptr PropertyGetter::get_c_call_method_id()
{
    std::ostringstream os;
    os << get_this_class()->get_c_jni_class_instance() << "." << get_field()->get_c_jni_id_name();
    return bfc::string::make_ptr(os);
}



bfc::string_ptr PropertySetter::get_c_call_api()
{
    if (is_static()) {
        return get_field()->get_type()->get_c_set_static_field_api();
    } else {
        return get_field()->get_type()->get_c_set_instance_field_api();
    }
}

bfc::string_ptr PropertySetter::get_c_call_method_id()
{
    std::ostringstream os;
    os << get_this_class()->get_c_jni_class_instance() << "." << get_field()->get_c_jni_id_name();
    return bfc::string::make_ptr(os);
}
