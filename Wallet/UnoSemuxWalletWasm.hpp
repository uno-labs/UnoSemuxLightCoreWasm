#pragma once

#include "UnoSemuxAddrWasm.hpp"

namespace UnoSemux {

class UnoSemuxWalletWasm
{
    CLASS_REMOVE_CTRS_EXCEPT_DEFAULT(UnoSemuxWalletWasm)

public:
    using STDSP = std::shared_ptr<UnoSemuxWalletWasm>;

public:
                            UnoSemuxWalletWasm          (void) noexcept;
                            UnoSemuxWalletWasm          (UnoSemuxWallet::SP aWallet) noexcept;
                            ~UnoSemuxWalletWasm         (void) noexcept;

    emscripten::val         generate_random_address     (void);
    emscripten::val         generate_next_hd_address    (const std::string aHDGroupId);
    emscripten::val         delete_address              (const std::string aAddrStrHex);
    emscripten::val         find_address                (const std::string aAddrStrHex);
    emscripten::val         add_hd_group                (const std::string aMnemonic, const std::string aPassword);
    emscripten::val         delete_hd_group             (const std::string aHDGroupId);
    emscripten::val         serialize                   (const std::string aPassword) const;
    emscripten::val         deserialize                 (const std::string aDataStrHex, const std::string aPassword);

    static emscripten::val  new_wallet                  (void);
    static emscripten::val  new_mnemonic_phrase         (void);

private:
    UnoSemuxWallet::SP      iWallet;
};

}//namespace UnoSemux
