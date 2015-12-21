

#ifndef JJK_PARSER_AST__AST__FORWARD__HPP
#define JJK_PARSER_AST__AST__FORWARD__HPP

#include <cassert>
#include "bfc/bfc.h"

#define NAMESPACE_AST_BEGIN namespace ast {
#define NAMESPACE_AST_END   }

NAMESPACE_AST_BEGIN

// https://docs.oracle.com/javase/specs/jls/se7/html/jls-18.html
class Annotation;
class Annotations;
class Argument;
class ArgumentList;
class BasicType;
class Class;
class ClassIdentifier;
class CompilationUnit;
class Constructor;
class Field;
class Identifier;
class ImportList;
class MemberList;
class Method;
class MethodList;
class ModifierSet;
class Node;
class PackageIdentifier;
class ReferenceType;
class Type;

NAMESPACE_AST_END

#endif
