#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_LUASCHEMA_ERRORS(X) \
    X(InvalidObject, "the object is not valid or nil") \
    X(UnexpectedType, "the object has an unexpected type") \
    X(ExpectedTable, "expected a table") \
    X(ExpectedArray, "expected an array table") \
    X(NoVariantMatched, "no variant alternative matched") \
    X(ExclusiveFields, "the field is exclusive with other fields") \
    X(InclusiveFields, "the field is inclusive with other fields") \
    X(OneOfRequired, "exactly one of the fields must be defined") \
    X(FieldRequired, "the field is required")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ELuaSchemaError, "luaschema", ERS_LUASCHEMA_ERRORS)

#undef ERS_LUASCHEMA_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ELuaSchemaError;
}
