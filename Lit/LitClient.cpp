#include <Lit/Lit.hpp>

using namespace stick;

#define RETURN_ON_ERR(_err) if(_err){ printf("Error: %s\n", _err.message().cString()); return EXIT_FAILURE; }

int main(int _argc, const char * _args[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::package,
                       sol::lib::os, sol::lib::math, sol::lib::table);

    lit::registerLit(lua);

    lua.script("package.path = package.path .. ';../Scripts/?.lua'");

    return EXIT_SUCCESS;
}
