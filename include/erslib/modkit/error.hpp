#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_MODKIT_ERRORS(X) \
    X(ElementNotFound, "Element is not found") \
    X(TypeMismatch, "Element has another type")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, EModkitError, "modkit", ERS_MODKIT_ERRORS)

#undef ERS_MODKIT_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::EModkitError;
}
