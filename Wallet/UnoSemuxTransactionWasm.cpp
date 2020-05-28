#include "UnoSemuxTransactionWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxTransactionWasm::UnoSemuxTransactionWasm (void) noexcept
{
}

UnoSemuxTransactionWasm::UnoSemuxTransactionWasm (UnoSemuxTransactionWasm&& aTransactionWasm) noexcept:
iTransaction(std::move(aTransactionWasm.iTransaction))
{
}

UnoSemuxTransactionWasm::UnoSemuxTransactionWasm (UnoSemuxTransaction&& aTransaction) noexcept:
iTransaction(std::move(aTransaction))
{
}

UnoSemuxTransactionWasm::~UnoSemuxTransactionWasm (void) noexcept
{
}

emscripten::val	UnoSemuxTransactionWasm::SNew (const NetworkTypeTE		aNetworkType,
											  const TransactionTypeTE	aType,
											  const std::string			aAddrToHexStr,
											  const std::string			aValue/*nanosem*/,
											  const std::string			aFee/*nanosem*/,
											  const std::string			aNonce,
											  const std::string			aTimestamp/*ms*/,
											  const std::string			aDataStrHex,
											  const std::string			aGas/*gas*/,
											  const std::string			aGasPrice/*nanosem*/)
{
	return WasmExceptionCatcher([&]()
	{
		NetworkTypeTE		networkType	= aNetworkType;
		TransactionTypeTE	type		= aType;
		GpBytesArray		addrTo		= GpStringOps::SToBytes(aAddrToHexStr);
		nanosem_t			value		= nanosem_t::SMake(GpStringOps::SToSI64(aValue));
		nanosem_t			fee			= nanosem_t::SMake(GpStringOps::SToSI64(aFee));
		s_int_64			nonce		= GpStringOps::SToSI64(aNonce);
		unix_ts_ms_t		timestamp	= unix_ts_ms_t::SMake(GpStringOps::SToSI64(aTimestamp));
		GpBytesArray		data		= GpStringOps::SToBytes(aDataStrHex);
		semgas_t			gas			= semgas_t::SMake(GpStringOps::SToSI64(aGas));
		nanosem_t			gasPrice	= nanosem_t::SMake(GpStringOps::SToSI64(aGasPrice));

		UnoSemuxTransaction				transaction(networkType,
													type,
													std::move(addrTo),
													value,
													fee,
													nonce,
													timestamp,
													std::move(data),
													gas,
													gasPrice);

		UnoSemuxTransactionWasm::STDSP	transactionWasm = std::make_shared<UnoSemuxTransactionWasm>(std::move(transaction));

		return emscripten::val(transactionWasm);
	});
}

emscripten::val	UnoSemuxTransactionWasm::Encode (void) const
{
	return WasmExceptionCatcher([&]()
	{
		const GpBytesArray data = iTransaction.Encode();
		return emscripten::val(GpStringOps::SFromBytes(data));
	});
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxTransactionWasm_bind)
{
	emscripten::class_<UnoSemux::UnoSemuxTransactionWasm>("UnoSemuxTransaction")
		.smart_ptr_constructor("UnoSemuxTransaction", &std::make_shared<UnoSemux::UnoSemuxTransactionWasm>)
		.class_function("sNew", &UnoSemux::UnoSemuxTransactionWasm::SNew)
		.function("encode", &UnoSemux::UnoSemuxTransactionWasm::Encode)
	;
}
