#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_CONVERT_ERRORS(X) \
    X(CastFailed, "the value could not be cast") \
    X(ParseFailed, "the text could not be parsed") \
    X(MalformedTimestamp, "malformed timestamp") \
    X(MalformedDate, "malformed date") \
    X(OutOfRange, "the value is out of range")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, EConvertError, "convert", ERS_CONVERT_ERRORS)

#undef ERS_CONVERT_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::EConvertError;
}
