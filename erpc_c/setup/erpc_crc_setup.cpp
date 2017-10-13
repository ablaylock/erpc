#include "erpc_crc_setup.h"
#include "crc16.h"
#include <new>

using namespace erpc;
using namespace std;

const uint16_t CRC_16_CCITT = 0x1021;
const uint16_t CRC_16_IBM = 0x8005;
const uint16_t CRC_16_T10_DIF = 0x8BB7;
const uint16_t CRC_16_DNP = 0x3D65;
const uint16_t CRC_16_DECT = 0x0589;

#ifdef ERPC_CRC_DYNAMIC

erpc_crc_t erpc_crc16_init(const uint16_t polynomial)
{
	return reinterpret_cast<erpc_crc_t>(new (nothrow) Crc16(erpc_generated_crc));
}

erpc_crc_t erpc_crc_none_init()
{
	return erpc_crc_t();
}

void erpc_crc_reset(erpc_crc_t crc)
{
}

void erpc_crc_deinit(erpc_crc_t crc)
{
	delete reinterpret_cast<CrcAlgorithm*>(crc);
}

#else
#include "manually_constructed.h"
static ManuallyConstructed<Crc16> s_crc16;

erpc_crc_t erpc_crc16_init(const uint16_t polynomial)
{
	s_crc16.construct(polynomial);
	return reinterpret_cast<erpc_crc_t>(s_crc16.get());
}

erpc_crc_t erpc_crc_none_init()
{
	return erpc_crc_t();
}

void erpc_crc_reset(erpc_crc_t crc)
{
}


void erpc_crc_deinit(erpc_crc_t crc)
{
	s_crc16.destroy();
}


#endif
