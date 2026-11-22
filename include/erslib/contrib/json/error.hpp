#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_JSON_ERRORS(X) \
    X(Malformed, "malformed JSON") \
    X(Io, "cannot read the file") \
    X(InvalidSchema, "invalid JSON schema") \
    X(ValidationFailed, "JSON validation failed") \
    X(Mismatch, "the JSON does not match the type")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, EJsonError, "json", ERS_JSON_ERRORS)

#undef ERS_JSON_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::EJsonError;
}
