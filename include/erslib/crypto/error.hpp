#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_CRYPTO_ERRORS(X) \
    X(CannotRead, "Cannot read the file") \
    X(ReadFailed, "Reading the file failed")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ECryptoError, "crypto", ERS_CRYPTO_ERRORS)

#undef ERS_CRYPTO_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ECryptoError;
}
