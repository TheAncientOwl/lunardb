#pragma once

#define LUNAR_PROVIDE_GETTER(field, getter_name) \
    inline auto getter_name() const              \
    {                                            \
        return m_##field;                        \
    }

#define LUNAR_PROVIDE_REF_GETTER(field, getter_name) \
    inline auto& get##getter_name()                  \
    {                                                \
        return m_##field;                            \
    }

#define LUNAR_PROVIDE_CONST_GETTER(field, getter_name) \
    inline auto const& get##getter_name() const        \
    {                                                  \
        return m_##field;                              \
    }

#define LUNAR_PROVIDE_SETTER(field, setter_name)   \
    inline void set##setter_name(auto new_##field) \
    {                                              \
        m_##field = std::move(new_##field);        \
    }

#define LUNAR_PROVIDE_GET_SET(field, setter_name) \
    LUNAR_PROVIDE_GETTER(field, setter_name)      \
    LUNAR_PROVIDE_SETTER(field, setter_name)

#define LUNAR_PROVIDE_REF_GET_SET(field, setter_name) \
    LUNAR_PROVIDE_CONST_GETTER(field, setter_name)    \
    LUNAR_PROVIDE_SETTER(field, setter_name)

#define LUNAR_PROVIDE_DEFAULT_EQUALITY_CHECK(type) bool operator==(type const&) const = default;

#define LUNAR_PROVIDE_DEFAULT_CONSTRUCT_DESTRUCT(type) \
    type() = default;                                  \
    ~type() = default;

#define LUNAR_PROVIDE_DEFAULT_COPY(type) \
    type(type const&) = default;         \
    type& operator=(type const&) = default;

#define LUNAR_PROVIDE_DEFAULT_MOVE(type) \
    type(type&&) noexcept = default;     \
    type& operator=(type&&) noexcept = default;

#define LUNAR_PROVIDE_DEFAULT_LIFE_CYCLE_OF(type)  \
    LUNAR_PROVIDE_DEFAULT_CONSTRUCT_DESTRUCT(type) \
    LUNAR_PROVIDE_DEFAULT_COPY(type)               \
    LUNAR_PROVIDE_DEFAULT_MOVE(type)
