#include "Wallet/UnoSemuxAccountHDWasm.hpp"

#include <iostream>

using namespace UnoSemux;

int main()
{
	try
	{
		/*GpCryptoCore::SInit();

		UnoSemuxAccountHD::SP semuxAccountHD = UnoSemuxAccountHD::SImportFromMnemonic("garbage banner bar limb canyon width maple alien soda grow say brass"_sv,
																					  GpCryptoHDNetworkType::TEST_NET);

		UnoSemuxAddr::SP addr1 = semuxAccountHD.V().AddrAddNextHD();
		UnoSemuxAddr::SP addr2 = semuxAccountHD.V().AddrAddNextHD();
		UnoSemuxAddr::SP addr3 = semuxAccountHD.V().AddrAddNextHD();

		std::cout << "addr1: " << addr1.VC().AddrStrHex() << std::endl;
		std::cout << "addr2: " << addr2.VC().AddrStrHex() << std::endl;
		std::cout << "addr3: " << addr3.VC().AddrStrHex() << std::endl;

		addr1.Vn().SetNonce(1);

		{
			GpBytesArray addrTo = GpStringOps::SToBytes("0x82c38263217817de2ef28937c7747716eb1e7228"_sv);
			GpBytesArray data;

			UnoSemuxTransaction t(UnoSemuxNetworkType::TESTNET,
								  UnoSemuxTransactionType::VOTE,
								  addrTo,
								  10000000_usem,
								  5000000_usem,
								  addr1.VCn().Nonce(),
								  GpDateTimeOps::SUnixTS_s(),
								  data,
								  0_semgas,
								  0_usem);

			std::cout << "Transaction: " << GpStringOps::SFromBytes(t.Encode()) << std::endl;

			UnoSemuxTransactionSign sign		= addr1.VC().Sign1(t);
			const GpBytesArray		signBytes	= sign.Encode();
			std::cout << "Signature: " << GpStringOps::SFromBytes(signBytes) << std::endl;
		}

		GpCryptoCore::SClear();*/
	} catch (const std::exception& e)
	{
		GpExceptionsSink::SSink(e);
	} catch (...)
	{
		GpExceptionsSink::SSinkUnknown();
	}

	return 0;
}
