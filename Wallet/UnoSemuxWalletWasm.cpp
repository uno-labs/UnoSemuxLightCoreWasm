#include "UnoSemuxWalletWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxWalletWasm::UnoSemuxWalletWasm (void) noexcept
{
}

UnoSemuxWalletWasm::UnoSemuxWalletWasm (UnoSemuxWallet::SP aWallet) noexcept:
iWallet(std::move(aWallet))
{
}

UnoSemuxWalletWasm::~UnoSemuxWalletWasm (void) noexcept
{
}

emscripten::val UnoSemuxWalletWasm::generate_random_address (void)
{
    return WasmExceptionCatcher([&]()
    {
        UnoSemuxAddr::SP        addr        = iWallet.V().GenRndAddr();
        UnoSemuxAddrWasm::STDSP addrWasm    = std::make_shared<UnoSemuxAddrWasm>(addr);

        return emscripten::val(addrWasm);
    });
}

emscripten::val UnoSemuxWalletWasm::generate_next_hd_address (const std::string aHDGroupId)
{
    return WasmExceptionCatcher([&]()
    {
        UnoSemuxAddr::SP        addr        = iWallet.V().GenNextHDAddr(count_t::SMake(GpStringOps::SToSI64(aHDGroupId)));
        UnoSemuxAddrWasm::STDSP addrWasm    = std::make_shared<UnoSemuxAddrWasm>(addr);

        return emscripten::val(addrWasm);
    });
}

emscripten::val UnoSemuxWalletWasm::delete_address (const std::string aAddrStrHex)
{
    return WasmExceptionCatcher([&]()
    {
        iWallet.V().DeleteAddr(aAddrStrHex);
        return emscripten::val::null();
    });
}

emscripten::val UnoSemuxWalletWasm::find_address (const std::string aAddrStrHex)
{
    return WasmExceptionCatcher([&]()
    {
        UnoSemuxAddr::SP        addr        = iWallet.V().FindAddr(aAddrStrHex);
        UnoSemuxAddrWasm::STDSP addrWasm    = std::make_shared<UnoSemuxAddrWasm>(addr);

        return emscripten::val(addrWasm);
    });
}

emscripten::val UnoSemuxWalletWasm::add_hd_group (const std::string aMnemonic, const std::string aPassword)
{
    return WasmExceptionCatcher([&]()
    {
        const count_t hdGroupId = iWallet.V().AddHDGroup(aMnemonic, aPassword);
        return emscripten::val(GpStringOps::SFromSI64(hdGroupId.ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxWalletWasm::delete_hd_group (const std::string aHDGroupId)
{
    return WasmExceptionCatcher([&]()
    {
        iWallet.V().DeleteHDGroup(count_t::SMake(GpStringOps::SToSI64(aHDGroupId)));
        return emscripten::val::null();
    });
}

emscripten::val UnoSemuxWalletWasm::seserialize (const std::string aPassword) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iWallet.VC().SeserializeHex(aPassword));
    });
}

emscripten::val UnoSemuxWalletWasm::deseserialize (const std::string aDataStrHex, const std::string aPassword)
{
    return WasmExceptionCatcher([&]()
    {
        iWallet.V().DeseserializeHex(aDataStrHex, aPassword);
        return emscripten::val::null();
    });
}

emscripten::val UnoSemuxWalletWasm::new_wallet (void)
{
    return WasmExceptionCatcher([&]()
    {
        UnoSemuxWallet::SP          wallet      = UnoSemuxWallet::SP::SNew();
        UnoSemuxWalletWasm::STDSP   walletWasm  = std::make_shared<UnoSemuxWalletWasm>(std::move(wallet));

        return emscripten::val(walletWasm);
    });
}

emscripten::val UnoSemuxWalletWasm::new_mnemonic_pharase (void)
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(std::string(UnoSemuxWalletUtils::SNewMnemonic().ViewR().R().AsStringView()));
    });
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxWalletWasm_bind)
{
    emscripten::class_<UnoSemux::UnoSemuxWalletWasm>("UnoSemuxWallet")
        .smart_ptr_constructor("UnoSemuxWallet", &std::make_shared<UnoSemux::UnoSemuxWalletWasm>)
        .function("generate_random_address", &UnoSemux::UnoSemuxWalletWasm::generate_random_address)
        .function("generate_next_hd_address", &UnoSemux::UnoSemuxWalletWasm::generate_next_hd_address)
        .function("delete_address", &UnoSemux::UnoSemuxWalletWasm::delete_address)
        .function("find_address", &UnoSemux::UnoSemuxWalletWasm::find_address)
        .function("add_hd_group", &UnoSemux::UnoSemuxWalletWasm::add_hd_group)
        .function("delete_hd_group", &UnoSemux::UnoSemuxWalletWasm::delete_hd_group)
        .function("seserialize", &UnoSemux::UnoSemuxWalletWasm::seserialize)
        .function("deseserialize", &UnoSemux::UnoSemuxWalletWasm::deseserialize)
        .class_function("new_wallet", &UnoSemux::UnoSemuxWalletWasm::new_wallet)
        .class_function("new_mnemonic_pharase", &UnoSemux::UnoSemuxWalletWasm::new_mnemonic_pharase)
    ;
};
