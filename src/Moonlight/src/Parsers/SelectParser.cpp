#include "QueryParsers.hpp"
#include "Utils.hpp"

#include <unordered_set>

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "select" };

QueryData::Select::Order parseOrderBy(std::string_view str)
{
    QueryData::Select::Order out{};

    QueryExtractor extractor{ str };
    const auto [field_name, mode] = extractor.extractTuple<2>();
    if (!extractor.empty()) { throw Utils::buildError("Invalid order clause"); }

    out.field = Utils::checkNotEmpty(field_name, "field name");
    out.type = QueryData::Primitives::OrderType::toLiteral(mode);

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Select, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Select);

    const auto [select, from, structure, structure_name] = extractor.extractTuple<4>();

    Utils::checkKeywordEquals(select, "select");
    Utils::checkKeywordEquals(from, "from");
    Utils::checkKeywordEquals(structure, "structure");

    out.from = Utils::checkNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    Utils::ltrim(extractor.unsafe_data());

    const auto [fields] = extractor.extractTuple<1>();
    Utils::checkKeywordEquals(fields, "fields");

    out.fields = extractor.extractList<std::string>([](std::string_view sv) {
        auto str = std::string(sv);
        if (!Utils::isValidIdentifier(str)) { throw Utils::buildError("Invalid field identifier provided"); }
        return std::move(str);
        });
    if (out.fields.empty()) { throw Utils::buildMissingError("fields"); }

    if (!extractor.empty())
    {
        const auto [order, by] = extractor.extractTuple<2>();
        Utils::checkKeywordEquals(order, "order");
        Utils::checkKeywordEquals(by, "by");

        out.order_by = extractor.extractList<QueryData::Select::Order>(parseOrderBy);
        if (out.order_by->empty()) { throw Utils::buildMissingError("order by fields"); }

        std::unordered_set<std::string_view> order_fields{};
        for (const auto& order : *out.order_by)
        {
            if (order_fields.find(order.field) != order_fields.end())
            {
                throw Utils::buildError("Field '", order.field, "' found in order clause twice");
            }
            order_fields.insert(order.field);
        }
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
