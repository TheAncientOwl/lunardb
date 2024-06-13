#include "Errors.hpp"
#include "LunarDB/Common/Simdjson/simdjson.hpp"
#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_MOONLIGHT)

namespace LunarDB::Moonlight::Implementation {

namespace StringUtils = LunarDB::Common::CppExtensions::StringUtils;

namespace {

constexpr auto c_query_prefix{"insert"};

Common::QueryData::Insert::Object::type recursiveParseObject(simdjson::ondemand::value element)
{
    Common::QueryData::Insert::Object::type out{};

    switch (element.type())
    {
    case simdjson::ondemand::json_type::array: {
        std::vector<std::string> strings{};
        std::vector<Common::QueryData::Insert::Object> objects{};

        for (auto value : element.get_array())
        {
            if (value.type() == simdjson::ondemand::json_type::object)
            {
                objects.push_back(
                    std::get<Common::QueryData::Insert::Object>(recursiveParseObject(value.value())));
            }
            else if (value.type() == simdjson::ondemand::json_type::string)
            {
                strings.push_back(std::get<std::string>(recursiveParseObject(value.value())));
            }
            else
            {
                throw Errors::buildParseJSONObjectError("Invalid array type");
            }
        }

        if (strings.size() != 0 && objects.size() != 0)
        {
            throw Errors::buildParseJSONObjectError("mixed arrays are not allowed");
        }

        if (strings.size() != 0)
        {
            return std::move(strings);
        }
        else if (objects.size() != 0)
        {
            return std::move(objects);
        }
        else
        {
            throw Errors::buildMissingError("objects");
        }

        break;
    }
    case simdjson::ondemand::json_type::object: {
        auto obj = Common::QueryData::Insert::Object{};
        for (auto field : element.get_object())
        {
            obj.entries.emplace(field.unescaped_key().value(), recursiveParseObject(field.value()));
        }
        out = std::move(obj);
        break;
    }
    case simdjson::ondemand::json_type::string: {
        out = std::string(element.get_string().value());
        break;
    }
    default: {
        throw Errors::buildParseJSONObjectError(
            "only syntax allowed types are arrays, objects and strings");
        break;
    }
    }

    return out;
}

std::vector<Common::QueryData::Insert::Object> parseObjects(std::string_view str)
{
    StringUtils::trim(str);
    if (str.front() != '[')
    {
        throw Errors::buildParseJSONObjectError("[");
    }
    if (str.back() != ']')
    {
        throw Errors::buildParseJSONObjectError("]");
    }
    str.remove_prefix(1);
    str.remove_suffix(1);
    StringUtils::trim(str);
    Errors::assertNotEmpty(str, "objects");

    std::vector<Common::QueryData::Insert::Object> out{};

    try
    {
        simdjson::padded_string padded_str = str;
        simdjson::ondemand::parser parser{};
        simdjson::ondemand::document_stream docs = parser.iterate_many(padded_str);
        for (auto doc : docs)
        {
            auto& obj = out.emplace_back();

            auto value = doc.get_value();
            if (value.type() == simdjson::ondemand::json_type::object)
            {
                auto json_obj = doc.get_object();
                for (auto field : json_obj)
                {
                    obj.entries.emplace(
                        field.unescaped_key().value(), recursiveParseObject(field.value()));
                }
            }
            else
            {
                throw Errors::buildParseJSONObjectError("invalid object syntax");
            }
        }
    }
    catch (std::exception const& e)
    {
        throw Errors::buildParseJSONObjectError(e.what());
    }

    return out;
}

} // namespace

API::ParsedQuery Insert::parse(QueryExtractor extractor)
{
    CLOG_VERBOSE("Insert::parse()");

    auto out_parsed_query = API::ParsedQuery::make<Common::QueryData::Insert>();
    auto& out = out_parsed_query.get<Common::QueryData::Insert>();

    auto const [insert, into, structure_name, objects] = extractor.extractTuple<4>();

    Errors::assertKeywordEquals(insert, "insert");
    Errors::assertKeywordEquals(into, "into");
    Errors::assertKeywordEquals(objects, "objects");

    out.into = Errors::assertNotEmpty(structure_name, "structure name");
    out.objects = parseObjects(extractor.data());

    if (objects.empty())
    {
        throw Errors::buildMissingError("objects");
    }

    return out_parsed_query;
}

} // namespace LunarDB::Moonlight::Implementation
