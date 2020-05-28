#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

class UnoSemuxTransactionSignWasm
{
public:
	using STDSP = std::shared_ptr<UnoSemuxTransactionSignWasm>;

public:
							UnoSemuxTransactionSignWasm		(void) noexcept;
							UnoSemuxTransactionSignWasm		(const UnoSemuxTransactionSignWasm& aSignWasm) = delete;
							UnoSemuxTransactionSignWasm		(UnoSemuxTransactionSignWasm&& aSignWasm) noexcept;
							UnoSemuxTransactionSignWasm		(UnoSemuxTransactionSign&& aSign) noexcept;
							~UnoSemuxTransactionSignWasm	(void) noexcept;

	emscripten::val			TxData							(void) const;
	emscripten::val			TxHash							(void) const;
	emscripten::val			Sign							(void) const;
	emscripten::val			PubKeyNoPrefix					(void) const;

	emscripten::val			Encode							(void) const;

private:
	UnoSemuxTransactionSign	iSign;
};

}//namespace UnoSemux
