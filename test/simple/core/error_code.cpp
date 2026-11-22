// catch2
#include <catch2/catch_test_macros.hpp>

// std
#include <string>

// ers
#include <erslib/core/type/diagnostic.hpp>

// test
#include "support/test_case.hpp"


// Details ---------------------------------------------------------------------

#define TEST_ERRORS(X) \
    X(First, "the first") \
    X(Second, "the second")

#define OTHER_ERRORS(X) \
    X(First, "other first")

ERS_MAKE_ERROR_CODES(test_ns, ETestError, "test", TEST_ERRORS)
ERS_MAKE_ERROR_CODES(test_ns, EOtherError, "other", OTHER_ERRORS)


// Tests -----------------------------------------------------------------------

ERS_TEST_CASE("error code round trip", "[core]") {
    const std::error_code code = test_ns::ETestError::First;

    REQUIRE(code);
    REQUIRE(code == test_ns::ETestError::First);
    REQUIRE(code != test_ns::ETestError::Second);
    REQUIRE(std::string(code.category().name()) == "test");
    REQUIRE(code.message() == "the first");
    REQUIRE(ers::code_to_enum<test_ns::ETestError>(code) == test_ns::ETestError::First);
}

ERS_TEST_CASE("domains do not mix", "[core]") {
    REQUIRE(std::error_code(test_ns::ETestError::First) != std::error_code(test_ns::EOtherError::First));
}

ERS_TEST_CASE("diagnostic carries its code", "[core]") {
    const auto diag = ers::make_error(test_ns::ETestError::Second, "boom {}", 1);

    REQUIRE(diag.code() == test_ns::ETestError::Second);
    REQUIRE(diag.detail() == "boom 1");
    REQUIRE(diag.message() == "the second: boom 1");
    REQUIRE(diag.to_string().contains("[test]"));
}
