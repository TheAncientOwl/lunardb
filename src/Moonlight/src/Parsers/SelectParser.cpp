#include "QueryParser.hpp"

#include <unordered_set>

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{ "select" };

QueryData::Select::Order parseOrderBy(std::string_view str)
{
    QueryData::Select::Order out{};

    QueryExtractor extractor{ str };
    const auto [field_name, mode] = extractor.extractTuple<2>();
    if (!extractor.empty()) { throw Errors::buildError("Invalid order clause"); }

    out.field = Errors::assertNotEmpty(field_name, "field name");
    out.type = QueryData::Primitives::OrderType::toLiteral(mode);

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Select, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Select);

    const auto [select, from, structure, structure_name] = extractor.extractTuple<4>();

    Errors::assertKeywordEquals(select, "select");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(structure, "structure");

    out.from = Errors::assertNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    Utils::ltrim(extractor.unsafe_data());

    const auto [fields] = extractor.extractTuple<1>();
    Errors::assertKeywordEquals(fields, "fields");

    out.fields = extractor.extractList<std::string>([](std::string_view sv) {
        auto str = std::string(sv);
        Errors::assertValidIdentifier(str);
        return std::move(str);
        });
    if (out.fields.empty()) { throw Errors::buildMissingError("fields"); }

    if (!extractor.empty())
    {
        const auto [order, by] = extractor.extractTuple<2>();
        Errors::assertKeywordEquals(order, "order");
        Errors::assertKeywordEquals(by, "by");

        out.order_by = extractor.extractList<QueryData::Select::Order>(parseOrderBy);
        if (out.order_by.empty()) { throw Errors::buildMissingError("order by fields"); }

        std::unordered_set<std::string_view> order_fields{};
        for (const auto& order : out.order_by)
        {
            if (order_fields.find(order.field) != order_fields.end())
            {
                throw Errors::buildError("Field '", order.field, "' found in order clause twice");
            }
            order_fields.insert(order.field);
        }
    }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
