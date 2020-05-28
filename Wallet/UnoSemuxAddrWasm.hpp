#pragma once

#include "UnoSemuxTransactionSignWasm.hpp"
#include "UnoSemuxTransactionWasm.hpp"

namespace UnoSemux {

class UnoSemuxAddrWasm
{
public:
	using STDSP = std::shared_ptr<UnoSemuxAddrWasm>;

public:
										UnoSemuxAddrWasm		(void) noexcept;
										UnoSemuxAddrWasm		(const UnoSemuxAddrWasm& aAddrWasm) = delete;
										UnoSemuxAddrWasm		(UnoSemuxAddrWasm&& aAddrWasm) noexcept;
										UnoSemuxAddrWasm		(UnoSemuxAddr::SP aAddr) noexcept;
										~UnoSemuxAddrWasm		(void) noexcept;

	emscripten::val						AddrStrHex				(void) const;

	emscripten::val						Nonce					(void) const;
	emscripten::val						IncNonce				(void);
	emscripten::val						SetNonce				(const std::string aNonce);

	emscripten::val						Sign1					(UnoSemuxTransactionWasm::STDSP aTransactionWasm) const;
	emscripten::val						Sign2					(UnoSemuxTransactionWasm::STDSP aTransactionWasm) const;

	static emscripten::val				SGenerateNew			(void);
	static emscripten::val				SImportPrivateKeyStrHex	(const std::string aPrivateStrHex);

	UnoSemuxAddr::SP					_Addr					(void) {return iAddr;}

private:
	UnoSemuxAddr::SP					iAddr;
};

}//namespace UnoSemux
