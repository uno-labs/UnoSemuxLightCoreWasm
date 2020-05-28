#include "UnoSemuxAddrWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxAddrWasm::UnoSemuxAddrWasm (void) noexcept
{
}

UnoSemuxAddrWasm::UnoSemuxAddrWasm (UnoSemuxAddrWasm&& aAddrWasm) noexcept:
iAddr(std::move(aAddrWasm.iAddr))
{
}

UnoSemuxAddrWasm::UnoSemuxAddrWasm (UnoSemuxAddr::SP aAddr) noexcept:
iAddr(std::move(aAddr))
{
}

UnoSemuxAddrWasm::~UnoSemuxAddrWasm (void) noexcept
{
}

emscripten::val	UnoSemuxAddrWasm::AddrStrHex (void) const
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);
		return emscripten::val(iAddr.VCn().AddrStrHex());
	});
}

emscripten::val	UnoSemuxAddrWasm::Nonce (void) const
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);
		return emscripten::val(GpStringOps::SFromSI64(iAddr.VCn().Nonce()));
	});
}

emscripten::val	UnoSemuxAddrWasm::IncNonce (void)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);
		return emscripten::val(GpStringOps::SFromSI64(iAddr.Vn().IncNonce()));
	});
}

emscripten::val	UnoSemuxAddrWasm::SetNonce (const std::string aNonce)
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);

		iAddr.Vn().SetNonce(GpStringOps::SToSI64(aNonce));
		return emscripten::val::undefined();
	});
}

emscripten::val	UnoSemuxAddrWasm::Sign1 (UnoSemuxTransactionWasm::STDSP aTransactionWasm) const
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);

		UnoSemuxTransactionSign				sign		= iAddr.VCn().Sign1(aTransactionWasm->_Transaction());
		UnoSemuxTransactionSignWasm::STDSP	signWasm	= std::make_shared<UnoSemuxTransactionSignWasm>(std::move(sign));

		return emscripten::val(signWasm);
	});
}

emscripten::val	UnoSemuxAddrWasm::Sign2 (UnoSemuxTransactionWasm::STDSP aTransactionWasm) const
{
	return WasmExceptionCatcher([&]()
	{
		THROW_GPE_COND_CHECK_M(iAddr.IsNotNULL(), "Address object is null"_sv);

		UnoSemuxTransactionSign				sign		= iAddr.VCn().Sign2(aTransactionWasm->_Transaction());
		UnoSemuxTransactionSignWasm::STDSP	signWasm	= std::make_shared<UnoSemuxTransactionSignWasm>(std::move(sign));

		return emscripten::val(signWasm);
	});
}

emscripten::val	UnoSemuxAddrWasm::SGenerateNew (void)
{
	return WasmExceptionCatcher([&]()
	{
		UnoSemuxAddrWasm::STDSP addrWasm = std::make_shared<UnoSemuxAddrWasm>(std::move(UnoSemuxAddr::SGenerateNew()));

		return emscripten::val(addrWasm);
	});
}

emscripten::val	UnoSemuxAddrWasm::SImportPrivateKeyStrHex (const std::string aPrivateStrHex)
{
	return WasmExceptionCatcher([&]()
	{
		UnoSemuxAddrWasm::STDSP addrWasm = std::make_shared<UnoSemuxAddrWasm>(std::move(UnoSemuxAddr::SImportPrivateKeyStrHex(aPrivateStrHex)));

		return emscripten::val(addrWasm);
	});
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxAddrWasm_bind)
{
	emscripten::class_<UnoSemux::UnoSemuxAddrWasm>("UnoSemuxAddr")
		.smart_ptr_constructor("UnoSemuxAddr", &std::make_shared<UnoSemux::UnoSemuxAddrWasm>)
		.function("addrStrHex", &UnoSemux::UnoSemuxAddrWasm::AddrStrHex)
		.function("nonce", &UnoSemux::UnoSemuxAddrWasm::Nonce)
		.function("incNonce", &UnoSemux::UnoSemuxAddrWasm::IncNonce)
		.function("setNonce", &UnoSemux::UnoSemuxAddrWasm::SetNonce)
		.function("sign1", &UnoSemux::UnoSemuxAddrWasm::Sign1)
		.function("sign2", &UnoSemux::UnoSemuxAddrWasm::Sign2)
		.class_function("sGenerateNew",  &UnoSemux::UnoSemuxAddrWasm::SGenerateNew)
		.class_function("sImportPrivateKeyStrHex",  &UnoSemux::UnoSemuxAddrWasm::SImportPrivateKeyStrHex)
	;
}

//https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
