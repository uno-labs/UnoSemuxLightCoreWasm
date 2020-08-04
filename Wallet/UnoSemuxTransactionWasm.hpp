#pragma once

#include "../UnoSemuxLightCoreWasm_global.hpp"

namespace UnoSemux {

class UnoSemuxTransactionWasm
{
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxTransactionWasm)

public:
    using STDSP = std::shared_ptr<UnoSemuxTransactionWasm>;

    using NetworkTypeT          = UnoSemuxNetworkType;
    using NetworkTypeTE         = NetworkTypeT::EnumT;

    using TransactionTypeT      = UnoSemuxTransactionType;
    using TransactionTypeTE     = TransactionTypeT::EnumT;

public:
                                UnoSemuxTransactionWasm     (void) noexcept;
                                UnoSemuxTransactionWasm     (UnoSemuxTransaction&& aTransaction) noexcept;
                                ~UnoSemuxTransactionWasm    (void) noexcept;

    emscripten::val             network_type                (void) const;
    emscripten::val             transaction_type            (void) const;
    emscripten::val             address_to                  (void) const;
    emscripten::val             value                       (void) const;
    emscripten::val             fee                         (void) const;
    emscripten::val             nonce                       (void) const;
    emscripten::val             timestamp                   (void) const;
    emscripten::val             data                        (void) const;
    emscripten::val             gas                         (void) const;
    emscripten::val             gas_price                   (void) const;
    emscripten::val             encode                      (void) const;

    static emscripten::val      new_transaction             (const NetworkTypeTE        aNetworkType,
                                                             const TransactionTypeTE    aType,
                                                             const std::string          aAddrToHexStr,
                                                             const std::string          aValue/*nanosem*/,
                                                             const std::string          aFee/*nanosem*/,
                                                             const std::string          aNonce,
                                                             const std::string          aTimestamp/*ms*/,
                                                             const std::string          aDataStrHex,
                                                             const std::string          aGas/*gas*/,
                                                             const std::string          aGasPrice/*nanosem*/);

    const UnoSemuxTransaction&  Transaction                 (void) const noexcept {return iTransaction;}

private:
    UnoSemuxTransaction         iTransaction;
};

}//namespace UnoSemux
