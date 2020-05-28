#include "UnoSemuxTransactionSignWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxTransactionSignWasm::UnoSemuxTransactionSignWasm (void) noexcept
{
}

UnoSemuxTransactionSignWasm::UnoSemuxTransactionSignWasm (UnoSemuxTransactionSignWasm&& aSignWasm) noexcept:
iSign(std::move(aSignWasm.iSign))
{
}

UnoSemuxTransactionSignWasm::UnoSemuxTransactionSignWasm (UnoSemuxTransactionSign&& aSign) noexcept:
iSign(std::move(aSign))
{
}

UnoSemuxTransactionSignWasm::~UnoSemuxTransactionSignWasm (void) noexcept
{
}

emscripten::val	UnoSemuxTransactionSignWasm::TxData (void) const
{
	return WasmExceptionCatcher([&]()
	{
		return emscripten::val(GpStringOps::SFromBytes(iSign.TxData()));
	});
}

emscripten::val	UnoSemuxTransactionSignWasm::TxHash (void) const
{
	return WasmExceptionCatcher([&]()
	{
		return emscripten::val(GpStringOps::SFromBytes(iSign.TxHash()));
	});
}

emscripten::val	UnoSemuxTransactionSignWasm::Sign (void) const
{
	return WasmExceptionCatcher([&]()
	{
		return emscripten::val(GpStringOps::SFromBytes(iSign.Sign()));
	});
}

emscripten::val	UnoSemuxTransactionSignWasm::PubKeyNoPrefix (void) const
{
	return WasmExceptionCatcher([&]()
	{
		return emscripten::val(GpStringOps::SFromBytes(iSign.PubKeyNoPrefix()));
	});
}

emscripten::val	UnoSemuxTransactionSignWasm::Encode (void) const
{
	return WasmExceptionCatcher([&]()
	{
		const GpBytesArray data = iSign.Encode();
		return emscripten::val(GpStringOps::SFromBytes(data));
	});
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxTransactionSignWasm_bind)
{
	emscripten::class_<UnoSemux::UnoSemuxTransactionSignWasm>("UnoSemuxTransactionSign")
		.smart_ptr_constructor("UnoSemuxTransactionSign", &std::make_shared<UnoSemux::UnoSemuxTransactionSignWasm>)
		.function("txData", &UnoSemux::UnoSemuxTransactionSignWasm::TxData)
		.function("txHash", &UnoSemux::UnoSemuxTransactionSignWasm::TxHash)
		.function("sign", &UnoSemux::UnoSemuxTransactionSignWasm::Sign)
		.function("pubKeyNoPrefix", &UnoSemux::UnoSemuxTransactionSignWasm::PubKeyNoPrefix)
		.function("encode", &UnoSemux::UnoSemuxTransactionSignWasm::Encode)
	;
}
