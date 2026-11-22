#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_QUERY_ERRORS(X) \
    X(InvalidIdentifier, "Invalid identifier") \
    X(InvalidName, "Invalid function, aggregate or type name") \
    X(MissingOrdering, "Aggregate needs an ordering") \
    X(RawPlaceholderMismatch, "Raw SQL placeholders do not match the arguments") \
    X(NullSlot, "Null slot") \
    X(UnknownAnchor, "Anchor slot is not in the layout") \
    X(DuplicateSlot, "Slot is already in the layout") \
    X(ForeignSlot, "Slot is not part of this statement") \
    X(SlotConflict, "Slots can not be used together") \
    X(NegativeBound, "Negative bound") \
    X(EmptyColumns, "Slot needs at least one column") \
    X(EmptyValues, "Slot needs at least one value") \
    X(PlaceholderMismatch, "Slot markers do not match the values") \
    X(InvalidSetItem, "Only assignments are allowed here") \
    X(Failed, "Statement could not be built")

#define ERS_MIGRATION_ERRORS(X) \
    X(ReservedSchema, "Schema is reserved for flux") \
    X(UnrecordedSchema, "Schema has tables but flux has no records of it") \
    X(ClaimsUndeclared, "Migration claims something not declared in code") \
    X(DropsDeclared, "Migration drops something still declared in code") \
    X(UnknownDirective, "Unknown directive") \
    X(MisplacedDirective, "Directive is not allowed here") \
    X(BadName, "Migration name doesn't exist") \
    X(ForbiddenStatement, "Statement is not allowed in a migration") \
    X(DuplicateVersion, "Version is used by more than one migration") \
    X(StepFailed, "Migration step failed") \
    X(SchemaCreateFailed, "Creating the schema failed") \
    X(Mismatch, "Database does not match the code")

#define ERS_CONNECTION_ERRORS(X) \
    X(ConnectionLost, "Connection lost") \
    X(StatementFailed, "Statement failed") \
    X(PoolTimeout, "Timed out acquiring a pooled connection") \
    X(Failed, "Database call failed")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(flux::impl, EQueryError, "query", ERS_QUERY_ERRORS)
ERS_MAKE_ERROR_CODES(flux::impl, EMigrationError, "migration", ERS_MIGRATION_ERRORS)
ERS_MAKE_ERROR_CODES(flux::impl, EConnectionError, "connection", ERS_CONNECTION_ERRORS)

#undef ERS_QUERY_ERRORS
#undef ERS_MIGRATION_ERRORS
#undef ERS_CONNECTION_ERRORS


// Exports ---------------------------------------------------------------------

namespace flux {
    using impl::EQueryError;
    using impl::EMigrationError;
    using impl::EConnectionError;
}
