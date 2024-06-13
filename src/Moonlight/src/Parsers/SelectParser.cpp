#include <unordered_set>

#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace StringUtils = LunarDB::Common::CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"select"};

Common::QueryData::Select::Order parseOrderBy(std::string_view str)
{
    Common::QueryData::Select::Order out{};

    QueryExtractor extractor{str};
    auto const [field_name, mode] = extractor.extractTuple<2>();
    if (!extractor.empty())
    {
        throw Errors::buildError("Invalid order clause");
    }

    out.field = Errors::assertNotEmpty(field_name, "field name");
    out.type = Common::QueryData::Primitives::OrderType::toLiteral(mode);

    return out;
}

} // namespace

API::ParsedQuery Select::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Select::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Select>();
    auto& out = out_parsed_query.get<Common::QueryData::Select>();

    auto const [select, from, structure, structure_name] = extractor.extractTuple<4>();

    Errors::assertKeywordEquals(select, "select");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(structure, "structure");

    out.from = Errors::assertNotEmpty(structure_name, "structure name");

    out.where = Utils::extractWhereClause(extractor.unsafe_data());
    StringUtils::ltrim(extractor.unsafe_data());

    auto const [fields] = extractor.extractTuple<1>();
    Errors::assertKeywordEquals(fields, "fields");

    out.fields = extractor.extractList<std::string>([](std::string_view sv) {
        auto str = std::string(sv);
        Errors::assertValidIdentifier(str);
        return std::move(str);
    });
    if (out.fields.empty())
    {
        throw Errors::buildMissingError("fields");
    }

    if (!extractor.empty())
    {
        auto const [order, by] = extractor.extractTuple<2>();
        Errors::assertKeywordEquals(order, "order");
        Errors::assertKeywordEquals(by, "by");

        out.order_by = extractor.extractList<Common::QueryData::Select::Order>(parseOrderBy);
        if (out.order_by.empty())
        {
            throw Errors::buildMissingError("order by fields");
        }

        std::unordered_set<std::string_view> order_fields{};
        for (auto const& order : out.order_by)
        {
            if (order_fields.find(order.field) != order_fields.end())
            {
                throw Errors::buildError("Field '", order.field, "' found in order clause twice");
            }
            order_fields.insert(order.field);
        }
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
