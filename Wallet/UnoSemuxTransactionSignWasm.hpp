#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

class UnoSemuxTransactionSignWasm
{
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxTransactionSignWasm)

public:
    using STDSP = std::shared_ptr<UnoSemuxTransactionSignWasm>;

public:
                            UnoSemuxTransactionSignWasm     (void) noexcept;
                            UnoSemuxTransactionSignWasm     (UnoSemuxTransactionSign&& aSign) noexcept;
                            ~UnoSemuxTransactionSignWasm    (void) noexcept;

    emscripten::val         data                            (void) const;
    emscripten::val         hash                            (void) const;
    emscripten::val         sign                            (void) const;
    emscripten::val         public_key                      (void) const;
    emscripten::val         encode                          (void) const;

private:
    UnoSemuxTransactionSign iSign;
};

}//namespace UnoSemux
