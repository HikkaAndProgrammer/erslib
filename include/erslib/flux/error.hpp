#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_QUERY_ERRORS(X) \
    X(InvalidIdentifier, "invalid identifier") \
    X(InvalidName, "invalid function, aggregate or type name") \
    X(MissingOrdering, "the aggregate needs an ordering") \
    X(RawPlaceholderMismatch, "raw SQL placeholders do not match the arguments") \
    X(NullSlot, "null slot") \
    X(UnknownAnchor, "the anchor slot is not in the layout") \
    X(DuplicateSlot, "the slot is already in the layout") \
    X(ForeignSlot, "the slot is not part of this statement") \
    X(SlotConflict, "the slots can not be used together") \
    X(NegativeBound, "negative bound") \
    X(EmptyColumns, "the slot needs at least one column") \
    X(EmptyValues, "the slot needs at least one value") \
    X(PlaceholderMismatch, "the slot markers do not match the values") \
    X(InvalidSetItem, "only assignments are allowed here") \
    X(Failed, "the statement could not be built")

#define ERS_MIGRATION_ERRORS(X) \
    X(ReservedSchema, "the schema is reserved for flux") \
    X(UnrecordedSchema, "the schema has tables but flux has no records of it") \
    X(ClaimsUndeclared, "the migration claims something not declared in code") \
    X(DropsDeclared, "the migration drops something still declared in code") \
    X(UnknownDirective, "unknown directive") \
    X(MisplacedDirective, "the directive is not allowed here") \
    X(BadName, "not a migration name") \
    X(ForbiddenStatement, "the statement is not allowed in a migration") \
    X(DuplicateVersion, "the version is used by more than one migration") \
    X(StepFailed, "a migration step failed") \
    X(SchemaCreateFailed, "creating the schema failed") \
    X(Mismatch, "the database does not match the code")

#define ERS_CONNECTION_ERRORS(X) \
    X(ConnectionLost, "connection lost") \
    X(StatementFailed, "the statement failed") \
    X(PoolTimeout, "timed out acquiring a pooled connection") \
    X(Failed, "the database call failed")


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
