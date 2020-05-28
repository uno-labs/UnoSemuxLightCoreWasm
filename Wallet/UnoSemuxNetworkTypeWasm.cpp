#include "UnoSemuxNetworkTypeWasm.hpp"

EMSCRIPTEN_BINDINGS(UnoSemuxNetworkType_bind) {
	emscripten::enum_<UnoSemux::UnoSemuxNetworkType::EnumT>("UnoSemuxNetworkType")
		.value("MAINNET", UnoSemux::UnoSemuxNetworkType::MAINNET)
		.value("TESTNET", UnoSemux::UnoSemuxNetworkType::TESTNET)
		.value("DEVNET", UnoSemux::UnoSemuxNetworkType::DEVNET)
		;
}
