#pragma once

#include "UnoSemuxTransactionSignWasm.hpp"
#include "UnoSemuxTransactionWasm.hpp"

namespace UnoSemux {

class UnoSemuxAddrWasm
{
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxAddrWasm)

public:
    using STDSP = std::shared_ptr<UnoSemuxAddrWasm>;

public:
                                        UnoSemuxAddrWasm        (void) noexcept;
                                        UnoSemuxAddrWasm        (UnoSemuxAddr::SP aAddr) noexcept;
                                        ~UnoSemuxAddrWasm       (void) noexcept;

    emscripten::val                     private_key             (void) const;
    emscripten::val                     address                 (void) const;
    emscripten::val                     nonce                   (void) const;
    emscripten::val                     inc_nonce               (void);
    emscripten::val                     set_nonce               (const std::string aNonce);
    emscripten::val                     name                    (void) const;
    emscripten::val                     set_name                (const std::string aName);
    emscripten::val                     sign_transaction        (UnoSemuxTransactionWasm::STDSP aTransactionWasm) const;

private:
    UnoSemuxAddr::SP                    iAddr;
};

}//namespace UnoSemux
