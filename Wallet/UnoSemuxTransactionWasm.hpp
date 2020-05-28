#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

class UnoSemuxTransactionWasm
{
public:
	using STDSP = std::shared_ptr<UnoSemuxTransactionWasm>;

	using NetworkTypeT			= UnoSemuxNetworkType;
	using NetworkTypeTE			= NetworkTypeT::EnumT;

	using TransactionTypeT		= UnoSemuxTransactionType;
	using TransactionTypeTE		= TransactionTypeT::EnumT;

public:
								UnoSemuxTransactionWasm			(void) noexcept;
								UnoSemuxTransactionWasm			(const UnoSemuxTransactionWasm& aTransactionWasm) = delete;
								UnoSemuxTransactionWasm			(UnoSemuxTransactionWasm&& aTransactionWasm) noexcept;
								UnoSemuxTransactionWasm			(UnoSemuxTransaction&& aTransaction) noexcept;
								~UnoSemuxTransactionWasm		(void) noexcept;

	static emscripten::val		SNew							(const NetworkTypeTE		aNetworkType,
																 const TransactionTypeTE	aType,
																 const std::string			aAddrToHexStr,
																 const std::string			aValue/*nanosem*/,
																 const std::string			aFee/*nanosem*/,
																 const std::string			aNonce,
																 const std::string			aTimestamp/*ms*/,
																 const std::string			aDataStrHex,
																 const std::string			aGas/*gas*/,
																 const std::string			aGasPrice/*nanosem*/);

	emscripten::val				Encode							(void) const;

	const UnoSemuxTransaction&	_Transaction					(void) const noexcept {return iTransaction;}
	UnoSemuxTransaction&		_Transaction					(void) noexcept {return iTransaction;}

private:
	UnoSemuxTransaction			iTransaction;
};

}//namespace UnoSemux
