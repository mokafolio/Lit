#include <LitCore/LitCore.hpp>
#include <LukeLuaSol/LukeLuaSol.hpp>
#include <PaperLuaSol/PaperLuaSol.hpp>

#include <GL/gl3w.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace litCore
{

using namespace stick;
using namespace crunch;

namespace pls = paperLuaSol;
namespace lls = lukeLuaSol;
namespace cls = crunchLuaSol;

STICK_API static void clearWindow(const crunch::ColorRGBA & _color)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

STICK_API static Error saveFrame(const char * _name, UInt32 _x, UInt32 _y, UInt32 _w, UInt32 _h)
{
    stick::DynamicArray<unsigned char> frameData;
    frameData.resize(_w * _h * 4);
    glReadPixels(_x, _y, _w, _h, GL_RGBA, GL_UNSIGNED_BYTE, &frameData[0]);
    int res = stbi_write_png(_name, _w, _h, 4, frameData.ptr(), _w * 4);
    if (res == 0)
    {
        //@TODO: Better error code?
        return Error(ec::InvalidOperation, "Failed to save frame", STICK_FILE, STICK_LINE);
    }
    return Error();
}

STICK_API static Error saveFrameWithSize(const char * _name, const Vec2f & _size)
{
    return saveFrame(_name, 0, 0, (UInt32)_size.x, (UInt32)_size.y);
}

void registerLitCore(sol::state_view _lua, sol::table _table)
{
    stbi_flip_vertically_on_write(1);

    lls::registerLuke(_lua, _table);
    cls::registerCrunch(_lua, _table);
    pls::registerPaper(_lua, _table);

    _table.set_function("clearWindow", clearWindow);
    _table.set_function("saveFrame", sol::overload(saveFrame, saveFrameWithSize));
}

void registerLitCore(sol::state_view _lua, const String & _namespace)
{
    registerLitCore(_lua, cls::ensureNamespaceTable(_lua, _lua.globals(), _namespace));
}

} // namespace litCore

extern "C" {

int luaopen_LitCore(lua_State * L)
{
    sol::state_view sv(L);
    sol::table tbl = sv.create_table();
    litCore::registerLitCore(sv, tbl);
    tbl.push();
    return 1;
}
}
