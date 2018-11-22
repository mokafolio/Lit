#include <Lit/Lit.hpp>
#include <LukeLuaSol/LukeLuaSol.hpp>
#include <PaperLuaSol/PaperLuaSol.hpp>

namespace lit
{
using namespace stick;
namespace pls = paperLuaSol;
namespace lls = lukeLuaSol;
namespace cls = crunchLuaSol;

void registerLit(sol::state_view & _lua, const String & _namespace)
{
    _lua.open_libraries(sol::lib::base,
                        sol::lib::string,
                        sol::lib::package,
                        sol::lib::os,
                        sol::lib::math,
                        sol::lib::table);

    lls::registerLuke(_lua);
    cls::registerCrunch(_lua);
    pls::registerPaper(_lua);
}

} // namespace lit
