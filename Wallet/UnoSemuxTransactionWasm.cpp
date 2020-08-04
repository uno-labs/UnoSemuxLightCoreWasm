#include "UnoSemuxTransactionWasm.hpp"
#include "../WasmUtils/UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

UnoSemuxTransactionWasm::UnoSemuxTransactionWasm (void) noexcept
{
}

UnoSemuxTransactionWasm::UnoSemuxTransactionWasm (UnoSemuxTransaction&& aTransaction) noexcept:
iTransaction(std::move(aTransaction))
{
}

UnoSemuxTransactionWasm::~UnoSemuxTransactionWasm (void) noexcept
{
}

emscripten::val UnoSemuxTransactionWasm::network_type (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iTransaction.NetworkType().Value());
    });
}

emscripten::val UnoSemuxTransactionWasm::transaction_type (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iTransaction.Type().Value());
    });
}

emscripten::val UnoSemuxTransactionWasm::address_to (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iTransaction.AddrToStrHex());
    });
}

emscripten::val UnoSemuxTransactionWasm::value (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.Value().ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxTransactionWasm::fee (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.Fee().ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxTransactionWasm::nonce (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.Nonce()));
    });
}

emscripten::val UnoSemuxTransactionWasm::timestamp (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.Timestamp().ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxTransactionWasm::data (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iTransaction.DataStrHex());
    });
}

emscripten::val UnoSemuxTransactionWasm::gas (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.Gas().ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxTransactionWasm::gas_price (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(GpStringOps::SFromSI64(iTransaction.GasPrice().ValueAs<s_int_64>()));
    });
}

emscripten::val UnoSemuxTransactionWasm::encode (void) const
{
    return WasmExceptionCatcher([&]()
    {
        return emscripten::val(iTransaction.EncodeHex());
    });
}



emscripten::val UnoSemuxTransactionWasm::new_transaction (const NetworkTypeTE       aNetworkType,
                                                          const TransactionTypeTE   aType,
                                                          const std::string         aAddrToHexStr,
                                                          const std::string         aValue/*nanosem*/,
                                                          const std::string         aFee/*nanosem*/,
                                                          const std::string         aNonce,
                                                          const std::string         aTimestamp/*ms*/,
                                                          const std::string         aDataStrHex,
                                                          const std::string         aGas/*gas*/,
                                                          const std::string         aGasPrice/*nanosem*/)
{
    return WasmExceptionCatcher([&]()
    {
        NetworkTypeTE       networkType = aNetworkType;
        TransactionTypeTE   type        = aType;
        GpBytesArray        addrTo      = GpStringOps::SToBytes(aAddrToHexStr);
        nanosem_t           value       = nanosem_t::SMake(GpStringOps::SToSI64(aValue));
        nanosem_t           fee         = nanosem_t::SMake(GpStringOps::SToSI64(aFee));
        s_int_64            nonce       = GpStringOps::SToSI64(aNonce);
        unix_ts_ms_t        timestamp   = unix_ts_ms_t::SMake(GpStringOps::SToSI64(aTimestamp));
        GpBytesArray        data        = GpStringOps::SToBytes(aDataStrHex);
        semgas_t            gas         = semgas_t::SMake(GpStringOps::SToSI64(aGas));
        nanosem_t           gasPrice    = nanosem_t::SMake(GpStringOps::SToSI64(aGasPrice));

        UnoSemuxTransaction transaction(networkType,
                                        type,
                                        std::move(addrTo),
                                        value,
                                        fee,
                                        nonce,
                                        timestamp,
                                        std::move(data),
                                        gas,
                                        gasPrice);

        UnoSemuxTransactionWasm::STDSP  transactionWasm = std::make_shared<UnoSemuxTransactionWasm>(std::move(transaction));

        return emscripten::val(transactionWasm);
    });
}

}//namespace UnoSemux

EMSCRIPTEN_BINDINGS(UnoSemuxTransactionWasm_bind)
{
    emscripten::class_<UnoSemux::UnoSemuxTransactionWasm>("UnoSemuxTransaction")
        .smart_ptr_constructor("UnoSemuxTransaction", &std::make_shared<UnoSemux::UnoSemuxTransactionWasm>)
        .function("network_type", &UnoSemux::UnoSemuxTransactionWasm::network_type)
        .function("transaction_type", &UnoSemux::UnoSemuxTransactionWasm::transaction_type)
        .function("address_to", &UnoSemux::UnoSemuxTransactionWasm::address_to)
        .function("value", &UnoSemux::UnoSemuxTransactionWasm::value)
        .function("fee", &UnoSemux::UnoSemuxTransactionWasm::fee)
        .function("nonce", &UnoSemux::UnoSemuxTransactionWasm::nonce)
        .function("timestamp", &UnoSemux::UnoSemuxTransactionWasm::timestamp)
        .function("data", &UnoSemux::UnoSemuxTransactionWasm::data)
        .function("gas", &UnoSemux::UnoSemuxTransactionWasm::gas)
        .function("gas_price", &UnoSemux::UnoSemuxTransactionWasm::gas_price)
        .function("encode", &UnoSemux::UnoSemuxTransactionWasm::encode)
        .class_function("new_transaction", &UnoSemux::UnoSemuxTransactionWasm::new_transaction)
    ;
};
