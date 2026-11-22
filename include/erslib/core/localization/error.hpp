#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_LOCALIZATION_ERRORS(X) \
    X(NoLocales, "There are no locales") \
    X(DuplicateLocale, "Locale is listed twice") \
    X(UnknownLocale, "Unknown locale") \
    X(UnknownFallback, "Fallback locale is not among the locales") \
    X(DuplicateKey, "Key is defined twice") \
    X(DuplicateDomain, "Domain is defined twice") \
    X(InvalidKey, "Invalid key") \
    X(InvalidReference, "Invalid reference") \
    X(ReferenceCycle, "Reference cycle") \
    X(ReferenceTooDeep, "References are nested too deep") \
    X(UnresolvedReference, "Reference has no text") \
    X(BadBundle, "Invalid bundle") \
    X(BadPath, "Invalid path") \
    X(Io, "Cannot read the file") \
    X(Failed, "Localization failed")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, ELocalizationError, "localization", ERS_LOCALIZATION_ERRORS)

#undef ERS_LOCALIZATION_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ELocalizationError;
}
