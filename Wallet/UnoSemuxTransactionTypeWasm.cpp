#include "UnoSemuxTransactionTypeWasm.hpp"

EMSCRIPTEN_BINDINGS(UnoSemuxTransactionType_bind) {
	emscripten::enum_<UnoSemux::UnoSemuxTransactionType::EnumT>("UnoSemuxTransactionType")
		.value("COINBASE", UnoSemux::UnoSemuxTransactionType::COINBASE)
		.value("TRANSFER", UnoSemux::UnoSemuxTransactionType::TRANSFER)
		.value("DELEGATE", UnoSemux::UnoSemuxTransactionType::DELEGATE)
		.value("VOTE", UnoSemux::UnoSemuxTransactionType::VOTE)
		.value("UNVOTE", UnoSemux::UnoSemuxTransactionType::UNVOTE)
		.value("CREATE", UnoSemux::UnoSemuxTransactionType::CREATE)
		.value("CALL", UnoSemux::UnoSemuxTransactionType::CALL)
		;
}
