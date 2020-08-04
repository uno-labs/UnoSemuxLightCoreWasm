#pragma once

#include "../GpCore2/GpCore.hpp"
#include "../GpCryptoCore/GpCryptoCore.hpp"
#include "../UnoSemuxLightCore/UnoSemuxLightCore.hpp"

#if !defined(__EMSCRIPTEN__)
#   error This library can be build only with EMSCRIPTEN
#endif

#include <emscripten.h>
#include <emscripten/bind.h>

