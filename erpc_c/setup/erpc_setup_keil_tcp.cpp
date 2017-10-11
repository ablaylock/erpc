#include "erpc_transport_setup.h"
#include "manually_constructed.h"
#include "keil_tcptransport.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static ManuallyConstructed<Keil_TCPTransport> s_transport;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

erpc_transport_t erpc_transport_keil_tcp_init(bool isServer, const int32_t tcpSock, const uint16_t port)
{
    s_transport.construct(isServer,tcpSock,port);
    if (s_transport->open() == kErpcStatus_Success)
    {
        return reinterpret_cast<erpc_transport_t>(s_transport.get());
    }
    return nullptr;
}
