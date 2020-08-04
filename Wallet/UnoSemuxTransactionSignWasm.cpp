#include "UnoSemuxTransactionSignWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxTransactionSignWasm::UnoSemuxTransactionSignWasm (void) noexcept
{
}

UnoSemuxTransactionSignWasm::UnoSemuxTransactionSignWasm (UnoSemuxTransactionSign&& aSign) noexcept:
iSign(std::move(aSign))
{
}

UnoSemuxTransactionSignWasm::~UnoSemuxTransactionSignWasm (void) noexcept
{
}

emscripten::val UnoSemuxTransactionSignWasm::data (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iSign.DataHex());
    });
}

emscripten::val UnoSemuxTransactionSignWasm::hash (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iSign.HashHex());
    });
}

emscripten::val UnoSemuxTransactionSignWasm::sign (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iSign.SignHex());
    });
}

emscripten::val UnoSemuxTransactionSignWasm::public_key (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iSign.PublicKeyHex());
    });
}

emscripten::val UnoSemuxTransactionSignWasm::encode (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iSign.EncodeHex());
    });
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxTransactionSignWasm_bind)
{
    emscripten::class_<UnoSemux::UnoSemuxTransactionSignWasm>("UnoSemuxTransactionSign")
        .smart_ptr_constructor("UnoSemuxTransactionSign", &std::make_shared<UnoSemux::UnoSemuxTransactionSignWasm>)
        .function("data", &UnoSemux::UnoSemuxTransactionSignWasm::data)
        .function("hash", &UnoSemux::UnoSemuxTransactionSignWasm::hash)
        .function("sign", &UnoSemux::UnoSemuxTransactionSignWasm::sign)
        .function("public_key", &UnoSemux::UnoSemuxTransactionSignWasm::public_key)
        .function("encode", &UnoSemux::UnoSemuxTransactionSignWasm::encode)
    ;
};
