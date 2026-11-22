#pragma once

// std
#include <chrono>
#include <format>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

// ers
#include <erslib/core/exception.hpp>
#include <erslib/core/type/error_code.hpp>
#include <erslib/core/type/time.hpp>

// export
#include <erslib/export.hpp>


// Implementation --------------------------------------------------------------

// ESeverity

namespace ers::impl {
    enum class ESeverity {
        Debug,
        Info,
        Warning,
        Error,
        Crit
    };

    constexpr std::string_view severity_name(ESeverity value) noexcept {
        switch (value) {
            case ESeverity::Debug:   return "DEBUG";
            case ESeverity::Info:    return "INFO";
            case ESeverity::Warning: return "WARNING";
            case ESeverity::Error:   return "ERROR";
            case ESeverity::Crit:    return "CRIT";
        }

        return "UNKNOWN";
    }
}

namespace ers {
    using impl::ESeverity;
    using impl::severity_name;
}


// Diagnostic

#ifdef _HAS_CPPTRACE

// cpptrace
#include <cpptrace/cpptrace.hpp>

#endif


namespace ers::impl {
    class ERSLIB_EXPORT Diagnostic {
    public:
        // Member functions

        Diagnostic(
#ifdef _HAS_CPPTRACE
            ESeverity severity,
            std::error_code code,
            std::string message = {},
            timestamp_t timestamp = std::chrono::system_clock::now(),
            cpptrace::raw_trace trace = get_trace({ .skip = 1 })
#else
            ESeverity severity,
            std::error_code code,
            std::string message = {},
            timestamp_t timestamp = std::chrono::system_clock::now()
#endif
        );


        // Observers

        ESeverity severity() const noexcept { return m_severity; }
        std::error_code code() const noexcept { return m_code; }
        timestamp_t timestamp() const noexcept { return m_timestamp; }
        std::string_view message() const noexcept { return m_message; }
        std::string_view detail() const noexcept { return std::string_view(m_message).substr(m_detail_offset); }
#ifdef _HAS_CPPTRACE
        const cpptrace::raw_trace& stacktrace() const noexcept { return m_trace; }
#endif


        std::string to_string(bool trim = false) const;


        // Modifiers

        Diagnostic&& extend(std::string_view message) &&;

        template<typename... Args>
            requires (sizeof...(Args) >= 1)
        Diagnostic&& extend(std::format_string<Args...> fmt, Args&&... args) && {
            m_message += std::format(fmt, std::forward<Args>(args)...);
            return std::move(*this);
        }


        Diagnostic&& wrap(std::string context) && {
            m_context.push_back(std::move(context));
            return std::move(*this);
        }


    protected:
        ESeverity m_severity;
        std::error_code m_code;
        std::string m_message;
        size_t m_detail_offset = 0;
        std::vector<std::string> m_context;
        timestamp_t m_timestamp;
#ifdef _HAS_CPPTRACE
        cpptrace::raw_trace m_trace;
#endif


    private:
        std::string _build_message() const;
    };
}


// Formatters

#define ERS_DECLARE_DIAGNOSTIC(X) \
    X(make_debug, Debug); \
    X(make_info, Info); \
    X(make_warning, Warning); \
    X(make_error, Error); \
    X(make_crit, Crit);


#define ERS_X_FN_DIAGNOSTIC(NAME, SEVERITY) \
    struct NAME##_fn { \
        template<typename... Args> \
            requires (sizeof...(Args) >= 1) \
        Diagnostic operator()(std::error_code code, std::format_string<Args...> fmt, Args&&... args) const { \
            return Diagnostic(ers::ESeverity::SEVERITY, code, std::format(fmt, std::forward<Args>(args)...)); \
        } \
        \
        inline Diagnostic operator()(std::error_code code, std::string message) const { \
            return Diagnostic(ers::ESeverity::SEVERITY, code, std::move(message)); \
        } \
        \
        Diagnostic operator()(std::error_code code) const { \
            return Diagnostic(ers::ESeverity::SEVERITY, code); \
        } \
    }; \
    inline constexpr NAME##_fn NAME {}

namespace ers::impl {
    ERS_DECLARE_DIAGNOSTIC(ERS_X_FN_DIAGNOSTIC)
}

#undef ERS_X_FN_DIAGNOSTIC


// Exports ---------------------------------------------------------------------

#define ERS_X_USING_DIAGNOSTIC(NAME, SEVERITY) \
    using impl::NAME

namespace ers {
    using impl::Diagnostic;

    ERS_DECLARE_DIAGNOSTIC(ERS_X_USING_DIAGNOSTIC)
}

#undef ERS_X_USING_DIAGNOSTIC


#undef ERS_DECLARE_DIAGNOSTIC
