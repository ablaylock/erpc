#include "erpc_transport_setup.h"
#include "manually_constructed.h"
#include "keil_bsdtransport.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static ManuallyConstructed<Keil_BSDTransport> s_transport;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

erpc_transport_t erpc_transport_keil_bsd_init(const int32_t tcpSock)
{
    s_transport.construct(tcpSock);
    return reinterpret_cast<erpc_transport_t>(s_transport.get());
}

void erpc_transport_keil_bsd_deinit()
{
    s_transport.get()->close();
}
