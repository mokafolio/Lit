#ifndef LIT_LITCORE_HPP
#define LIT_LITCORE_HPP

#include <Stick/String.hpp>
#include <sol/sol.hpp>

namespace litCore
{

STICK_API void registerLitCore(sol::state_view _lua, const stick::String & _namespace = "");
STICK_API void registerLitCore(sol::state_view _lua, sol::table _table);

} // namespace lit

/* to load the library with Lua's require function/luarocks */
extern "C" {

// name of this function is not flexible
int luaopen_LitCore(lua_State * L);
}

#endif // LIT_LITCORE_HPP
