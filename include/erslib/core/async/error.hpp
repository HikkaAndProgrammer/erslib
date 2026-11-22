#pragma once

// ers
#include <erslib/core/type/error_code.hpp>


// Macros ----------------------------------------------------------------------

#define ERS_ASYNC_ERRORS(X) \
    X(SchedulerStopped, "the scheduler is stopped") \
    X(BulkheadFull, "the bulkhead is full") \
    X(Cancelled, "the job was cancelled") \
    X(Dropped, "the job was dropped before it finished") \
    X(TaskThrew, "the task threw an exception") \
    X(SyncWaitIncomplete, "sync_wait did not finish") \
    X(AlreadyStarted, "the runtime was already started") \
    X(PeriodicFailed, "a periodic task failed") \
    X(ServiceStartFailed, "a service failed to start")

#define ERS_PROCESS_ERRORS(X) \
    X(EmptyCommand, "the process command is empty") \
    X(ExecutableNotFound, "the executable was not found") \
    X(StartFailed, "the process could not be started") \
    X(ReadFailed, "the process output could not be read") \
    X(Cancelled, "the process was cancelled") \
    X(TimedOut, "the process timed out")


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
