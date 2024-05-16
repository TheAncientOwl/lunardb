#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"truncate"};

} // namespace

API::ParsedQuery Truncate::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Parsing 'truncate' query");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Truncate>();
    auto& out = out_parsed_query.get<Common::QueryData::Truncate>();

    auto const [truncate, structure, structure_name] = extractor.extractTuple<3>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(truncate, "truncate");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
