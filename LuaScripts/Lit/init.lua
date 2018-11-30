local lit = require("LitCore") -- the native library (LitCore.so on unix systems)
lit.util = require("Lit.Utilities") -- the lua utility files
lit.promote = function(_self, _toTable)
    local toTbl = _toTable or _G
    for k, v in pairs(_self) do
        toTbl[k] = v
    end
end
return lit
