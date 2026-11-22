#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_SPLIT_ERRORS(X) \
    X(TrailingBackslash, "Trailing backslash") \
    X(UnterminatedQuote, "Unterminated quote")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ESplitError, "split", ERS_SPLIT_ERRORS)

#undef ERS_SPLIT_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ESplitError;
}
