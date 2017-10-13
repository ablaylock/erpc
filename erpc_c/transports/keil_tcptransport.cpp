#include "keil_tcptransport.h"
#include "rl_net.h"
#include <algorithm>
#include "rx-data.h"

using namespace erpc;

RTX::MemoryPool<struct RXDataBlock, 15> rx_memory_pool;
RTX::MessageQueue<struct RXDataBlock*, 2> eth_recive_queue(nullptr);
RTX::MessageQueue<struct RXDataBlock*, 2> usb_recive_queue(nullptr);

Keil_TCPTransport::Keil_TCPTransport(bool isServer, const int32_t tcpSock, const uint16_t port) :
    m_isServer(isServer)
  , m_tcpSocket(tcpSock)
  , m_port(port)
{

}

erpc_status_t Keil_TCPTransport::open()
{

    if (m_tcpSocket >= 0)
    {
        const auto res = netTCP_Listen(m_tcpSocket, m_port);
        switch (res) {
        case netOK:
            break;
        case netBusy:
        case netDriverError:
        case netError:
        case netInvalidParameter:
        case netServerError:
        case netWrongState:
            return kErpcStatus_ConnectionFailure;
        }
    }
    return kErpcStatus_Success;

}

erpc_status_t Keil_TCPTransport::close()
{
    if(m_tcpSocket >= 0)
    {
        netTCP_Abort(m_tcpSocket);
    }
    return kErpcStatus_Success;
}

erpc_status_t Keil_TCPTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    struct RXDataBlock* block = nullptr;
	const auto start_size = size;
    while(size && start_size >= size)
    {
        eth_recive_queue.pop(block,BLOCK::FOREVER);
        memcpy(data,block->buffer,block->size);
        data += block->size;
        size -= block->size;
        rx_memory_pool.free(block);
    }
    return start_size >= size ? kErpcStatus_Success : kErpcStatus_ReceiveFailed;
}

erpc_status_t Keil_TCPTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    if(m_tcpSocket < 0)
    {
        return kErpcStatus_Success;
    }
    while(size)
    {
        const auto num2write = std::min(size,netTCP_GetMaxSegmentSize(m_tcpSocket));
        auto buffer = netTCP_GetBuffer(num2write);
        memcpy(buffer, data, num2write);
        while (!netTCP_SendReady(m_tcpSocket)) {
            asm volatile (""); // Wait for not busy
        }
        const auto ret = netTCP_Send(m_tcpSocket,buffer,num2write);
        if(ret != netOK)
        {
            return kErpcStatus_SendFailed;
        }
        size -= num2write;
    }
    return kErpcStatus_Success;
}
