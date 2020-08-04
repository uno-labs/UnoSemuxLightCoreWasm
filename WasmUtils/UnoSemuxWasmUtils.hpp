#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

emscripten::val WasmExceptionCatcher    (std::function<emscripten::val()> aFn);
emscripten::val WasmJsonApiError        (std::string_view aMessage);

}//namespace UnoSemux
