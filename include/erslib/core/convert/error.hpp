#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_CONVERT_ERRORS(X) \
    X(CastFailed, "Value could not be cast") \
    X(ParseFailed, "Text could not be parsed") \
    X(MalformedTimestamp, "Malformed timestamp") \
    X(MalformedDate, "Malformed date") \
    X(OutOfRange, "Value is out of range")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, EConvertError, "convert", ERS_CONVERT_ERRORS)

#undef ERS_CONVERT_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::EConvertError;
}
