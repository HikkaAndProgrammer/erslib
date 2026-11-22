#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_LOCALIZATION_ERRORS(X) \
    X(NoLocales, "there are no locales") \
    X(DuplicateLocale, "a locale is listed twice") \
    X(UnknownLocale, "unknown locale") \
    X(UnknownFallback, "the fallback locale is not among the locales") \
    X(DuplicateKey, "a key is defined twice") \
    X(DuplicateDomain, "a domain is defined twice") \
    X(InvalidKey, "invalid key") \
    X(InvalidReference, "invalid reference") \
    X(ReferenceCycle, "reference cycle") \
    X(ReferenceTooDeep, "references are nested too deep") \
    X(UnresolvedReference, "a reference has no text") \
    X(BadBundle, "invalid bundle") \
    X(BadPath, "invalid path") \
    X(Io, "cannot read the file") \
    X(Failed, "localization failed")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ELocalizationError, "localization", ERS_LOCALIZATION_ERRORS)

#undef ERS_LOCALIZATION_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ELocalizationError;
}
