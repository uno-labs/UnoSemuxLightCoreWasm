#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

emscripten::val WasmExceptionCatcher(std::function<emscripten::val()> aFn);

}//namespace UnoSemux
