#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"drop"};

} // namespace

API::ParsedQuery Drop::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Drop::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Drop>();
    auto& out = out_parsed_query.get<Common::QueryData::Drop>();

    auto const [drop, structure, structure_name, cascade] = extractor.extractTuple<4>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    }

    Errors::assertKeywordEquals(drop, "drop");
    Errors::assertKeywordEquals(structure, "structure");

    out.structure_name = Errors::assertNotEmpty(structure_name, "structure name");

    if (cascade.empty())
    {
        out.cascade = false;
    }
    else
    {
        Errors::assertKeywordEquals(cascade, "cascade");
        out.cascade = true;
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
