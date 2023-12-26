#include "QueryParsers.hpp"
#include "Utils.hpp"

#include "simdjson/simdjson.hpp"

namespace LunarDB::Moonlight::Implementation {

using namespace Utils;
using namespace std::literals;

namespace {

constexpr auto c_query_prefix{ "insert" };

QueryData::Insert::Object::type recursiveParseObject(simdjson::ondemand::value element)
{
    QueryData::Insert::Object::type out{};

    switch (element.type())
    {
    case simdjson::ondemand::json_type::array: {
        std::vector<std::string> strings{};
        std::vector<QueryData::Insert::Object> objects{};

        for (auto value : element.get_array())
        {
            if (value.type() == simdjson::ondemand::json_type::object)
            {
                objects.push_back(std::get<QueryData::Insert::Object>(recursiveParseObject(value.value())));
            }
            else if (value.type() == simdjson::ondemand::json_type::string)
            {
                strings.push_back(std::get<std::string>(recursiveParseObject(value.value())));
            }
            else
            {
                throw Utils::buildParseJSONObjectError("Invalid array type");
            }
        }

        if (strings.size() != 0 && objects.size() != 0) { throw Utils::buildParseJSONObjectError("mixed arrays are not allowed"); }

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
            throw Utils::buildMissingError("objects");
        }

        break;
    }
    case simdjson::ondemand::json_type::object: {
        auto obj = QueryData::Insert::Object{};
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
        throw Utils::buildParseJSONObjectError("only syntax allowed types are arrays, objects and strings");
        break;
    }
    }

    return out;
}

std::vector<QueryData::Insert::Object> parseObjects(std::string_view str)
{
    Utils::trim(str);
    if (str.front() != '[') { throw Utils::buildParseJSONObjectError("["); }
    if (str.back() != ']') { throw Utils::buildParseJSONObjectError("]"); }
    str.remove_prefix(1);
    str.remove_suffix(1);
    Utils::trim(str);
    Utils::checkNotEmpty(str, "objects");

    std::vector<QueryData::Insert::Object> out{};

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
                    obj.entries.emplace(field.unescaped_key().value(), recursiveParseObject(field.value()));
                }
            }
            else
            {
                throw Utils::buildParseJSONObjectError("invalid object syntax");
            }
        }
    }
    catch (const std::exception& e)
    {
        throw Utils::buildParseJSONObjectError(e.what());
    }

    return out;
}

} // namespace

PROVIDE_QUERY_PARSER_IMPL(Insert, c_query_prefix)
{
    DECLARE_PARSED_QUERY(Insert);

    const auto [insert, into, structure_name, objects] = extractor.extractTuple<4>();

    Utils::checkKeywordEquals(insert, "insert");
    Utils::checkKeywordEquals(into, "into");
    Utils::checkKeywordEquals(objects, "objects");

    out.into = Utils::checkNotEmpty(structure_name, "structure name");
    out.objects = parseObjects(extractor.data());

    if (objects.empty()) { throw Utils::buildMissingError("objects"); }

    RETURN_PARSED_QUERY;
}

} // namespace LunarDB::Moonlight::Implementation
