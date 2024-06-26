#include "Errors.hpp"
#include "LunarDB/Moonlight/QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"delete"};

} // namespace

API::ParsedQuery Delete::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Delete::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Delete>();
    auto& out = out_parsed_query.get<Common::QueryData::Delete>();

    auto const [delete_, from, structure, structure_name] = extractor.extractTuple<4>();
    if (extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(delete_, "delete");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(structure, "structure");

    out.from = Errors::assertNotEmpty(structure_name, "structure name");
    out.where = Utils::extractWhereClause(extractor.unsafe_data());

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
