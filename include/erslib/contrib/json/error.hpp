#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_JSON_ERRORS(X) \
    X(Malformed, "Malformed JSON") \
    X(Io, "Cannot read the file") \
    X(InvalidSchema, "Invalid JSON schema") \
    X(ValidationFailed, "JSON validation failed") \
    X(Mismatch, "JSON does not match the type")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(utl::impl, EJsonError, "json", ERS_JSON_ERRORS)

#undef ERS_JSON_ERRORS
