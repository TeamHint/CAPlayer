

#ifndef JJK_PARSER_AST__AST__DEF__HPP
#define JJK_PARSER_AST__AST__DEF__HPP

#include "parser.hpp"
#include "jni.bison.tab.hpp"
#include "ast__forward.hpp"

#define AST_PROPERTY(name)              mm_##name
#define AST_MEMBER_DEFINE(type, name)   type AST_PROPERTY(name);

#define AST_GETTER_DECL_0(type, name)           virtual type get_##name() = 0;
#define AST_GETTER_DECL(type, name)             virtual type get_##name();
#define AST_GETTER_DECL_OVERRIDE(type, name)    virtual type get_##name() override;
#define AST_GETTER_IMPL(type, name)             virtual type get_##name()           {return AST_PROPERTY(name);}
#define AST_GETTER_IMPL_OVERRIDE(type, name)    virtual type get_##name() override  {return AST_PROPERTY(name);}
#define AST_GETTER_DEFINE(type, name)           public: AST_GETTER_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name); public:
#define AST_GETTER_DEFINE_OVERRIDE(type, name)  public: AST_GETTER_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name); public:

#define AST_SETTER_DECL(type, name)             virtual void set_##name(type name);
#define AST_SETTER_DECL_OVERRIDE(type, name)    virtual void set_##name(type name) override;
#define AST_SETTER_IMPL(type, name)             virtual void set_##name(type name)          {AST_PROPERTY(name) = name;}
#define AST_SETTER_IMPL_OVERRIDE(type, name)    virtual void set_##name(type name) override {AST_PROPERTY(name) = name;}
#define AST_SETTER_DEFINE(type, name)           public: AST_SETTER_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name); public:
#define AST_SETTER_DEFINE_OVERRIDE(type, name)  public: AST_SETTER_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name); public:

#define AST_PROPERTY_DECL(type, name)               AST_GETTER_DECL(type, name);          AST_SETTER_DECL(type, name);
#define AST_PROPERTY_DECL_OVERRIDE(type, name)      AST_GETTER_DECL_OVERRIDE(type, name); AST_SETTER_DECL_OVERRIDE(type, name);
#define AST_PROPERTY_IMPL(type, name)               AST_GETTER_IMPL(type, name);          AST_SETTER_IMPL(type, name);
#define AST_PROPERTY_IMPL_OEVRRIDE(type, name)      AST_GETTER_IMPL_OVERRIDE(type, name); AST_SETTER_IMPL_OVERRIDE(type, name);
#define AST_PROPERTY_DEFINE(type, name)             public: AST_PROPERTY_IMPL(type, name);          private: AST_MEMBER_DEFINE(type, name); public:
#define AST_PROPERTY_DEFINE_OVERRIDE(type, name)    public: AST_PROPERTY_IMPL_OVERRIDE(type, name); private: AST_MEMBER_DEFINE_OVERRIDE(type, name); public:



#define AST_CHILD_SETTER_DECL(type, name)           virtual void set_##name(type *name);
#define AST_CHILD_SETTER_DECL_OVERRIDE(type, name)  virtual void set_##name(type *name) override;
#define AST_CHILD_SETTER_IMPL(type, name)           virtual void set_##name(type *name)          {AST_PROPERTY(name).assign(name); name->set_parent(this);}
#define AST_CHILD_SETTER_IMPL_OVERRIDE(type, name)  virtual void set_##name(type *name) override {AST_PROPERTY(name).assign(name); name->set_parent(this);}
#define AST_CHILD_GETTER_DECL(type, name)           virtual type *get_##name();
#define AST_CHILD_GETTER_DECL_OVERRIDE(type, name)  virtual type *get_##name() override;
#define AST_CHILD_GETTER_IMPL(type, name)           virtual type *get_##name()          {return AST_PROPERTY(name).get();}
#define AST_CHILD_GETTER_IMPL_OVERRIDE(type, name)  virtual type *get_##name() override {return AST_PROPERTY(name).get();}
#define AST_CHILD_DECL(type, name)                  AST_CHILD_GETTER_DECL(type, name);          AST_CHILD_SETTER_DECL(type, name);
#define AST_CHILD_DECL_OVERRIDE(type, name)         AST_CHILD_GETTER_DECL_OVERRIDE(type, name); AST_CHILD_SETTER_DECL_OVERRIDE(type, name);
#define AST_CHILD_IMPL(type, name)                  AST_CHILD_GETTER_IMPL(type, name);          AST_CHILD_SETTER_IMPL(type, name);
#define AST_CHILD_IMPL_OVERRIDE(type, name)         AST_CHILD_GETTER_IMPL_OVERRIDE(type, name); AST_CHILD_SETTER_IMPL_OVERRIDE(type, name);
#define AST_CHILD_DEFINE(type, name)                public: AST_CHILD_IMPL(type, name);          private: type::pointer_type AST_PROPERTY(name); public:
#define AST_CHILD_DEFINE_OVERRIDE(type, name)       public: AST_CHILD_IMPL_OVERRIDE(type, name); private: type::pointer_type AST_PROPERTY(name); public:



#define AST_FUNC_TRACE()    do {printf("%s\n", __func__);} while(0)



#define AST_IMPLEMENT_ABSTRACT(class__) \
public: \
    typedef bfc::rc_ptr<class__> pointer_type;

#define AST_IMPLEMENT(class__) \
public: \
    AST_IMPLEMENT_ABSTRACT(class__)

#endif
