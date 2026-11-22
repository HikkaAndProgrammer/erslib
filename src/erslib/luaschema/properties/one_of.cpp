#include "erslib/luaschema/properties/one_of.hpp"

// std
#include <optional>
#include <utility>

// ers
#include <erslib/core/formatter/range.hpp>
#include <erslib/luaschema/error_code.hpp>


ers::impl::luaschema::OneOfProperty::OneOfProperty(std::vector<std::string> names) :
    _names(std::move(names)) {
}

ers::Status ers::impl::luaschema::OneOfProperty::verify(sol::table table) const {
    std::vector<std::string_view> present;

    present.reserve(_names.size());
    for (const auto& n : _names) {
        if (table.get<std::optional<sol::object>>(n))
            present.push_back(n);
    }

    if (present.size() > 1) {
        return make_error(ELuaSchemaError::OneOfRequired, "Exactly one of fields {} must be defined, but several are: {}",
            _names, present);
    }

    if (present.empty()) {
        return make_error(ELuaSchemaError::OneOfRequired, "Exactly one of fields {} must be defined, but none is",
            _names);
    }

    return ok;
}


ers::impl::luaschema::Descriptor ers::impl::luaschema::properties::one_of(std::initializer_list<std::string_view> il) {
    std::vector<std::string> names;

    names.reserve(il.size());
    for (const auto& it : il)
        names.emplace_back(it);

    return make_descriptor<OneOfProperty>(std::move(names));
}
