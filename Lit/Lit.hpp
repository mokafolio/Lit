#ifndef LIT_LIT_HPP
#define LIT_LIT_HPP

#include <Stick/Platform.hpp>

namespace lit
{
    
STICK_API void registerLit(sol::state_view & _lua, const stick::String & _namespace = "");

}

#endif // LIT_LIT_HPP
