#include "keil_bsdtransport.h"
#include "rl_net.h"

using namespace erpc;


erpc_status_t Keil_BSDTransport::close()
{
    if(m_tcpSocket > 0)
    {
        const auto result = closesocket(m_tcpSocket);
        if(result != BSD_SUCCESS)
        {
            asm ("BKPT");
        }
    }
    return kErpcStatus_Success;
}

erpc_status_t Keil_BSDTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    if(m_tcpSocket < 0)
    {
        return kErpcStatus_ConnectionClosed;
    }
    const auto start_size = size;
    while(size && start_size >= size)
    {
        const auto res = ::recv(m_tcpSocket,reinterpret_cast<char*>(data),static_cast<int>(size),0);
        switch (res) {
        case BSD_ERROR_SOCKET:
            return kErpcStatus_ReceiveFailed;
        case BSD_ERROR_PARAMETER:
            return kErpcStatus_ReceiveFailed;
        case BSD_ERROR_CLOSED:
            return kErpcStatus_ConnectionClosed;
        case BSD_ERROR_LOCKED:
            return kErpcStatus_Timeout;
        case BSD_ERROR_TIMEOUT:
            return kErpcStatus_Timeout;
        case BSD_ERROR:
            return kErpcStatus_ReceiveFailed;
        case BSD_ERROR_WOULDBLOCK:
            return kErpcStatus_Timeout;
        default:
            break;
        }
        if(res < 0)
        {
            return kErpcStatus_ReceiveFailed;
        }
        size -= static_cast<uint32_t>(res);
    }
    return start_size >= size ? kErpcStatus_Success : kErpcStatus_ReceiveFailed;
}

erpc_status_t Keil_BSDTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    if(m_tcpSocket < 0)
    {
        return kErpcStatus_ConnectionClosed;
    }
    const auto start_size = size;
    while(size && start_size >= size)
    {
        const auto res = ::send(m_tcpSocket,reinterpret_cast<const char*>(data),static_cast<int>(size),0);
        switch (res) {
        case BSD_ERROR_SOCKET:
            return kErpcStatus_SendFailed;
        case BSD_ERROR_PARAMETER:
            return kErpcStatus_SendFailed;
        case BSD_ERROR_CLOSED:
            return kErpcStatus_ConnectionClosed;
        case BSD_ERROR_LOCKED:
            return kErpcStatus_Timeout;
        case BSD_ERROR:
            return kErpcStatus_SendFailed;
        case BSD_ERROR_WOULDBLOCK:
            return kErpcStatus_Timeout;
        default:
            break;
        }
        if(res < 0)
        {
            return kErpcStatus_SendFailed;
        }
        size -= static_cast<uint32_t>(res);
    }
    return start_size >= size ? kErpcStatus_Success : kErpcStatus_SendFailed;
}
