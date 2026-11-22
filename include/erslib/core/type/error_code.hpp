#pragma once

// std
#include <concepts>
#include <cstddef>
#include <iterator>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>

// ers
#include <erslib/core/type/general.hpp>


// Details ---------------------------------------------------------------------

namespace ers::impl {
    template<typename E>
    struct error_domain;

    template<typename E>
    concept ErrorEnum = std::is_enum_v<E> && requires {
        { error_domain<E>::name } -> std::convertible_to<std::string_view>;
        { error_domain<E>::describe(E {}) } -> std::convertible_to<std::string_view>;
    };
}


// Implementation --------------------------------------------------------------

namespace ers::impl {
    template<ErrorEnum E>
    class error_category_t final : public std::error_category {
    public:
        const char* name() const noexcept override {
            return error_domain<E>::name.data();
        }

        std::string message(int value) const override {
            return std::string(error_domain<E>::describe(static_cast<E>(value - 1)));
        }
    };

    template<ErrorEnum E>
    [[gnu::visibility("default")]]
    const std::error_category& error_category_of() noexcept {
        static const error_category_t<E> instance;
        return instance;
    }

    template<ErrorEnum E>
    std::error_code make_code(E what) noexcept {
        return { static_cast<int>(what) + 1, error_category_of<E>() };
    }

    template<ErrorEnum E>
    constexpr E code_to_enum(const std::error_code& code) noexcept {
        return static_cast<E>(code.value() - 1);
    }
}


// Macros ----------------------------------------------------------------------

#define ERS_IMPL_ERROR_ENUMERATOR(NAME, MESSAGE) NAME,
#define ERS_IMPL_ERROR_MESSAGE(NAME, MESSAGE) MESSAGE,


// Declares an error enum together with its std::error_code integration and category. Use it at global scope:
//
//     #define MY_ERRORS(X)
//         X(NotFound, "not found")
//         X(Broken, "broken")
//
//     ERS_MAKE_ERROR_CODES(my::ns, EMyError, "my", MY_ERRORS)
//
// After that make_error(EMyError::NotFound, "...") and 'diagnostic.code() == EMyError::NotFound' should work.
#define ERS_MAKE_ERROR_CODES(NS, ENUM, DOMAIN, LIST) \
    namespace NS { \
        enum class ENUM : ::ers::u8 { LIST(ERS_IMPL_ERROR_ENUMERATOR) }; \
    } \
    \
    template<> \
    struct ers::impl::error_domain<NS::ENUM> { \
        static constexpr std::string_view name = DOMAIN; \
        \
        static constexpr std::string_view describe(NS::ENUM what) noexcept { \
            constexpr std::string_view messages[] = { LIST(ERS_IMPL_ERROR_MESSAGE) }; \
            auto index = static_cast<size_t>(what); \
            return index < std::size(messages) ? messages[index] : std::string_view("unknown"); \
        } \
    }; \
    \
    template<> \
    struct std::is_error_code_enum<NS::ENUM> : std::true_type {}; \
    \
    namespace NS { \
        inline std::error_code make_error_code(ENUM what) noexcept { \
            return ::ers::impl::make_code(what); \
        } \
    }


// Exports ---------------------------------------------------------------------

namespace ers {
    using impl::ErrorEnum;
    using impl::code_to_enum;
}
