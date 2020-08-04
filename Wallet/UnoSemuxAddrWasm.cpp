#include "UnoSemuxAddrWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxAddrWasm::UnoSemuxAddrWasm (void) noexcept
{
}

UnoSemuxAddrWasm::UnoSemuxAddrWasm (UnoSemuxAddr::SP aAddr) noexcept:
iAddr(std::move(aAddr))
{
}

UnoSemuxAddrWasm::~UnoSemuxAddrWasm (void) noexcept
{
}

emscripten::val UnoSemuxAddrWasm::private_key (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(std::string(iAddr.VC().PrivateKeyStrHex().ViewR().R().AsStringView()));
    });
}

emscripten::val UnoSemuxAddrWasm::address (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iAddr.VC().AddrStrHex());
    });
}

emscripten::val UnoSemuxAddrWasm::nonce (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iAddr.VC().Nonce()));
    });
}

emscripten::val UnoSemuxAddrWasm::inc_nonce (void)
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iAddr.V().IncNonce()));
    });
}

emscripten::val UnoSemuxAddrWasm::set_nonce (const std::string aNonce)
{
    return WasmExceptionCatcher([&]()
    {
        iAddr.V().SetNonce(GpStringOps::SToSI64(aNonce));
        return emscripten::val::null();
    });
}

emscripten::val UnoSemuxAddrWasm::name (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(std::string(iAddr.VC().Name()));
    });
}

emscripten::val UnoSemuxAddrWasm::set_name (const std::string aName)
{
    return WasmExceptionCatcher([&]()
    {
        iAddr.V().SetName(aName);
        return emscripten::val::null();
    });
}

emscripten::val UnoSemuxAddrWasm::sign_transaction (UnoSemuxTransactionWasm::STDSP aTransactionWasm) const
{
    return WasmExceptionCatcher([&]()
    {
        UnoSemuxTransactionSign             sign        = iAddr.VC().Sign1(aTransactionWasm->Transaction());
        UnoSemuxTransactionSignWasm::STDSP  signWasm    = std::make_shared<UnoSemuxTransactionSignWasm>(std::move(sign));

        return emscripten::val(signWasm);
    });
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxAddrWasm_bind)
{
    emscripten::class_<UnoSemux::UnoSemuxAddrWasm>("UnoSemuxAddr")
        .smart_ptr_constructor("UnoSemuxAddr", &std::make_shared<UnoSemux::UnoSemuxAddrWasm>)
        .function("private_key", &UnoSemux::UnoSemuxAddrWasm::private_key)
        .function("address", &UnoSemux::UnoSemuxAddrWasm::address)
        .function("nonce", &UnoSemux::UnoSemuxAddrWasm::nonce)
        .function("inc_nonce", &UnoSemux::UnoSemuxAddrWasm::inc_nonce)
        .function("set_nonce", &UnoSemux::UnoSemuxAddrWasm::set_nonce)
        .function("name", &UnoSemux::UnoSemuxAddrWasm::name)
        .function("set_name", &UnoSemux::UnoSemuxAddrWasm::set_name)
        .function("sign_transaction", &UnoSemux::UnoSemuxAddrWasm::sign_transaction)
        //.class_function("sGenerateNew",  &UnoSemux::UnoSemuxAddrWasm::SGenerateNew)
    ;
};

//https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
