#ifndef LIT_LIT_HPP
#define LIT_LIT_HPP

#include <sol/sol.hpp>
#include <Stick/String.hpp>

namespace lit
{
    
STICK_API void registerLit(sol::state_view & _lua, const stick::String & _namespace = "");

}

#endif // LIT_LIT_HPP
