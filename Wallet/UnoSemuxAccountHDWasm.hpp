#pragma once

#include "UnoSemuxAddrWasm.hpp"

namespace UnoSemux {

class UnoSemuxAccountHDWasm
{
public:
	using STDSP = std::shared_ptr<UnoSemuxAccountHDWasm>;

public:
										UnoSemuxAccountHDWasm	(void) noexcept;
										UnoSemuxAccountHDWasm	(const UnoSemuxAccountHDWasm& aAccountHDWasm) = delete;
										UnoSemuxAccountHDWasm	(UnoSemuxAccountHDWasm&& aAccountHDWasm) noexcept;
										UnoSemuxAccountHDWasm	(UnoSemuxAccountHD::SP aAccountHD) noexcept;
										~UnoSemuxAccountHDWasm	(void) noexcept;

	emscripten::val						AddrFindByName			(const std::string aAddrName);
	emscripten::val						AddrFindByHexStr		(const std::string aAddrHex);
	emscripten::val						AddrAdd					(UnoSemuxAddrWasm::STDSP aAddr);
	emscripten::val						AddrDeleteByName		(const std::string aAddrName);
	emscripten::val						AddrDeleteByHexStr		(const std::string aAddrHex);
	emscripten::val						AddrHexStrByName		(const std::string aAddrName) const;

	emscripten::val						AddrAddNextHD			(void);

	static emscripten::val				SImportFromMnemonic		(const std::string aMnemonic,
																 const std::string aPassword);
	static emscripten::val				SNewMnemonic			(void);

private:
	UnoSemuxAccountHD::SP				iAccountHD;
};

}//namespace UnoSemux
