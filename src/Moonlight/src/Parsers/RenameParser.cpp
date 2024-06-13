#include "Errors.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace {

constexpr auto c_query_prefix{"rename"};

} // namespace

API::ParsedQuery Rename::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Rename::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Rename>();
    auto& out = out_parsed_query.get<Common::QueryData::Rename>();

    auto const [rename, type, from, old_name, to, new_name] = extractor.extractTuple<6>();
    if (!extractor.empty())
    {
        throw Errors::buildInvalidQueryFormatError(c_query_prefix);
    };

    Errors::assertKeywordEquals(rename, "rename");
    Errors::assertKeywordEquals(from, "from");
    Errors::assertKeywordEquals(to, "to");

    out.type = Common::QueryData::Primitives::RenameType::toLiteral(
        Errors::assertNotEmpty(type, "rename type"));
    out.old_name = Errors::assertNotEmpty(old_name, "old name");
    out.new_name = Errors::assertNotEmpty(new_name, "new name");

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
