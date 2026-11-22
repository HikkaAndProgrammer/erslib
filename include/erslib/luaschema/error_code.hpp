#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_LUASCHEMA_ERRORS(X) \
    X(InvalidObject, "Object is not valid or nil") \
    X(UnexpectedType, "Object has an unexpected type") \
    X(ExpectedTable, "Table was expected") \
    X(ExpectedArray, "Array table was expected") \
    X(NoVariantMatched, "Variant alternative is not matched") \
    X(ExclusiveFields, "Field is exclusive with other fields") \
    X(InclusiveFields, "Field is inclusive with other fields") \
    X(OneOfRequired, "Exactly one of the fields must be defined") \
    X(FieldRequired, "The field is required")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ELuaSchemaError, "luaschema", ERS_LUASCHEMA_ERRORS)

#undef ERS_LUASCHEMA_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ELuaSchemaError;
}
