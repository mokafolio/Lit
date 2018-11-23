#include <Lit/Lit.hpp>
#include <LukeLuaSol/LukeLuaSol.hpp>
#include <PaperLuaSol/PaperLuaSol.hpp>

#include <GL/gl3w.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace lit
{

using namespace stick;

namespace pls = paperLuaSol;
namespace lls = lukeLuaSol;
namespace cls = crunchLuaSol;

static void clearWindow(luke::Window & _window, const crunch::ColorRGBA & _color)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

static Error saveFrame(const char * _name, UInt32 _x, UInt32 _y, UInt32 _w, UInt32 _h)
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

void registerLit(sol::state_view & _lua, const String & _namespace)
{
    stbi_flip_vertically_on_write(1);

    sol::table tbl = _lua.globals();
    if (!_namespace.isEmpty())
    {
        auto tokens = path::segments(_namespace, '.');
        for (const String & token : tokens)
            tbl = tbl[token.cString()] = tbl.get_or(token.cString(), _lua.create_table());
    }

    lls::registerLuke(_lua, _namespace);
    cls::registerCrunch(_lua, _namespace);
    pls::registerPaper(_lua, _namespace);

    tbl.set_function("clearWindow", clearWindow);
    tbl.set_function("saveFrame", saveFrame);
}

} // namespace lit
