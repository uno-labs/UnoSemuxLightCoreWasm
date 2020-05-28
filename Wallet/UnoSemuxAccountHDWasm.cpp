#include "UnoSemuxAccountHDWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxAccountHDWasm::UnoSemuxAccountHDWasm (void) noexcept
{
}

UnoSemuxAccountHDWasm::UnoSemuxAccountHDWasm (UnoSemuxAccountHDWasm&& aAccountHDWasm) noexcept:
iAccountHD(std::move(aAccountHDWasm.iAccountHD))
{
}

UnoSemuxAccountHDWasm::UnoSemuxAccountHDWasm (UnoSemuxAccountHD::SP aAccountHD) noexcept:
iAccountHD(std::move(aAccountHD))
{
}

UnoSemuxAccountHDWasm::~UnoSemuxAccountHDWasm (void) noexcept
{
}

emscripten::val	UnoSemuxAccountHDWasm::AddrFindByName (const std::string aAddrName)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		UnoSemuxAddr::SP		addr		= iAccountHD.Vn().AddrFindByName(aAddrName);
		UnoSemuxAddrWasm::STDSP	addrWasm	= std::make_shared<UnoSemuxAddrWasm>(addr);

		return emscripten::val(addrWasm);
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrFindByHexStr (const std::string aAddrHex)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		UnoSemuxAddr::SP		addr		= iAccountHD.Vn().AddrFindByHexStr(aAddrHex);
		UnoSemuxAddrWasm::STDSP	addrWasm	= std::make_shared<UnoSemuxAddrWasm>(addr);

		return emscripten::val(addrWasm);
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrAdd (UnoSemuxAddrWasm::STDSP aAddr)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		iAccountHD.Vn().AddrAdd(aAddr->_Addr());

		return emscripten::val::undefined();
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrDeleteByName (const std::string aAddrName)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		iAccountHD.Vn().AddrDeleteByName(aAddrName);

		return emscripten::val::undefined();
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrDeleteByHexStr (const std::string aAddrHex)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		iAccountHD.Vn().AddrDeleteByHexStr(aAddrHex);

		return emscripten::val::undefined();
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrHexStrByName (const std::string aAddrName) const
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		std::string addrHexStr = std::string(iAccountHD.VCn().AddrHexStrByName(aAddrName));

		return emscripten::val(addrHexStr);
	});
}

emscripten::val	UnoSemuxAccountHDWasm::AddrAddNextHD (void)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAccountHD.IsNotNULL(), "Account object is null"_sv);

		UnoSemuxAddr::SP		addr		= iAccountHD.Vn().AddrAddNextHD();
		UnoSemuxAddrWasm::STDSP	addrWasm	= std::make_shared<UnoSemuxAddrWasm>(addr);

		return emscripten::val(addrWasm);
	});
}

emscripten::val	UnoSemuxAccountHDWasm::SImportFromMnemonic (const std::string aMnemonic,
															const std::string aPassword)
{
	return WasmExceptionCatcher([&]()
	{
		UnoSemuxAccountHD::SP			accountHD		= UnoSemuxAccountHD::SImportFromMnemonic(aMnemonic,
																								 aPassword,
																								 GpCryptoHDNetworkType::MAIN_NET);
		UnoSemuxAccountHDWasm::STDSP	accountHDWasm	= std::make_shared<UnoSemuxAccountHDWasm>(accountHD);

		return emscripten::val(accountHDWasm);
	});
}

emscripten::val	UnoSemuxAccountHDWasm::SNewMnemonic (void)
{
	return WasmExceptionCatcher([&]()
	{
		std::string mnemonicStr;
		{
			GpSecureStorage			mnemonic		= UnoSemuxAccountHD::SNewMnemonic();
			GpSecureStorageViewR	mnemonicView	= mnemonic.ViewR();
			mnemonicStr = std::string(mnemonicView.AsStringView());
		}

		return emscripten::val(mnemonicStr);
	});
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxAccountHDWasm_bind)
{
	emscripten::class_<UnoSemux::UnoSemuxAccountHDWasm>("UnoSemuxAccountHD")
		.smart_ptr_constructor("UnoSemuxAccountHD", &std::make_shared<UnoSemux::UnoSemuxAccountHDWasm>)
		.function("addrFindByName", &UnoSemux::UnoSemuxAccountHDWasm::AddrFindByName)
		.function("addrFindByHexStr", &UnoSemux::UnoSemuxAccountHDWasm::AddrFindByHexStr)
		.function("addrAdd", &UnoSemux::UnoSemuxAccountHDWasm::AddrAdd)
		.function("addrDeleteByName", &UnoSemux::UnoSemuxAccountHDWasm::AddrDeleteByName)
		.function("addrDeleteByHexStr", &UnoSemux::UnoSemuxAccountHDWasm::AddrDeleteByHexStr)
		.function("addrHexStrByName", &UnoSemux::UnoSemuxAccountHDWasm::AddrHexStrByName)
		.function("addrAddNextHD", &UnoSemux::UnoSemuxAccountHDWasm::AddrAddNextHD)
		.class_function("sImportFromMnemonic",  &UnoSemux::UnoSemuxAccountHDWasm::SImportFromMnemonic)
		.class_function("sNewMnemonic",  &UnoSemux::UnoSemuxAccountHDWasm::SNewMnemonic)
	;
}
