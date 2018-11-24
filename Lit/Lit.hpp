#ifndef LIT_LIT_HPP
#define LIT_LIT_HPP

#include <Stick/String.hpp>
#include <sol/sol.hpp>

namespace lit
{

STICK_API void registerLit(sol::state_view _lua, const stick::String & _namespace = "");
STICK_API void registerLit(sol::state_view _lua, sol::table _table);

}

/* to load the library with Lua's require function/luarocks */
extern "C" {

// name of this function is not flexible
int luaopen_Lit(lua_State * L);

}

#endif // LIT_LIT_HPP
