#include <ranges>
#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "LunarDB/Astral/QueryExecutors.hpp"

#include "LunarDB/Celestial/UsersCatalog.hpp"
#include "LunarDB/Selenity/SystemCatalog.hpp"

#include "LunarDB/Crescentum/Logger.hpp"
LUNAR_DECLARE_LOGGER_MODULE(MODULE_ASTRAL)

namespace LunarDB::Astral::Implementation {

namespace {
static void setStdInEcho(bool enable = false)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if (!enable)
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode);

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if (!enable)
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
} // namespace

void Auth::execute(Moonlight::API::ParsedQuery const& parsed_query)
{
    CLOG_VERBOSE("Auth::execute()");

    auto const& query = parsed_query.get<Common::QueryData::Auth>();

    auto& system_catalog{Selenity::API::SystemCatalog::Instance()};
    auto& users_catalog{Celestial::API::UsersCatalog::Instance()};

    for (auto const trial : std::ranges::iota_view{0u, 3u})
    {
        std::string password{};
        std::cout << "> Enter password (trial " << trial + 1 << "/3): ";

        setStdInEcho(false);
        std::getline(std::cin, password);
        setStdInEcho(true);

        std::cout << std::endl;

        auto const auth_result = users_catalog.authenticateUser(query.username, password);
        switch (auth_result.first)
        {
        case Celestial::API::Configuration::EAuthState::Authenticated:
            system_catalog.setCurrentUser(query.username);
            return;
        case Celestial::API::Configuration::EAuthState::UnknwonUser:
            throw std::runtime_error{"Unknown user"};
            break;
        case Celestial::API::Configuration::EAuthState::WrongPassword:
            if (trial == 2)
            {
                throw std::runtime_error{"Invalid password"};
            }
            break;
        default:
            throw std::runtime_error{"Unsupported operation"};
            break;
        }
    }
    throw std::runtime_error{"Authentications trials exceeded"};
}

} // namespace LunarDB::Astral::Implementation
