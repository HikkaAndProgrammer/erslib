#include "erslib/luaschema/properties/inclusive_with.hpp"

// std
#include <optional>
#include <utility>

// ers
#include <erslib/luaschema/error_code.hpp>


ers::impl::luaschema::InclusiveWithProperty::InclusiveWithProperty(std::vector<std::string> mandatory_fields) :
    IVerifier(1),
    _mandatory_fields(std::move(mandatory_fields)) {
}


ers::Status ers::impl::luaschema::InclusiveWithProperty::exec([[maybe_unused]] verify_context& ctx, sol::table table, std::string_view field) const {
    if (!table.get<std::optional<sol::object>>(field))
        return ok;


    std::vector<std::string_view> absent;

    for (const auto& it : _mandatory_fields) {
        if (!table.get<std::optional<sol::object>>(it))
            absent.push_back(it);
    }


    if (!absent.empty()) {
        return make_error(ELuaSchemaError::InclusiveFields, "'{}' with {}",
            field, absent);
    }


    return ok;
}


ers::impl::luaschema::Verifier ers::impl::luaschema::properties::inclusive_with(std::string_view field) {
    return inclusive_with({ field });
}

ers::impl::luaschema::Verifier ers::impl::luaschema::properties::inclusive_with(std::initializer_list<std::string_view> il) {
    std::vector<std::string> mandatory_fields;

    mandatory_fields.reserve(il.size());
    for (const auto& it : il)
        mandatory_fields.emplace_back(it);

    return make_verifier<InclusiveWithProperty>(std::move(mandatory_fields));
}
