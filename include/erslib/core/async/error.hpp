#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_ASYNC_ERRORS(X) \
    X(SchedulerStopped, "Scheduler is stopped") \
    X(BulkheadFull, "Bulkhead is full") \
    X(Cancelled, "Job was cancelled") \
    X(Dropped, "Job was dropped before it finished") \
    X(TaskThrew, "Task threw an exception") \
    X(SyncWaitIncomplete, "`sync_wait` did not finish") \
    X(AlreadyStarted, "The runtime was already started") \
    X(PeriodicFailed, "Periodic task failed") \
    X(ServiceStartFailed, "Service failed to start")

#define ERS_PROCESS_ERRORS(X) \
    X(EmptyCommand, "Process command is empty") \
    X(ExecutableNotFound, "Executable was not found") \
    X(StartFailed, "Process could not be started") \
    X(ReadFailed, "Process output could not be read") \
    X(Cancelled, "Process was cancelled") \
    X(TimedOut, "Process timed out")


// Implementation --------------------------------------------------------------

ERS_MAKE_ERROR_CODES(ers::impl, EAsyncError, "async", ERS_ASYNC_ERRORS)
ERS_MAKE_ERROR_CODES(ers::impl, EProcessError, "process", ERS_PROCESS_ERRORS)

#undef ERS_ASYNC_ERRORS
#undef ERS_PROCESS_ERRORS


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::EAsyncError;
    using impl::EProcessError;
}
