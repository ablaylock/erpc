#ifndef KEIL_TCPTRANSPORT_H
#define KEIL_TCPTRANSPORT_H

#include "erpc_threading.h"
#include "framed_transport.h"
#include "rl_net.h"

namespace erpc {

class Keil_TCPTransport : public FramedTransport
{
public:
    Keil_TCPTransport(bool isServer, const int32_t tcpSock, const uint16_t port);

    /*!
     * @brief This function will create host on server side, or connect client to the server.
     *
     * @retval #kErpcStatus_Success When creating host was successful or client connected successfully.
     * @retval #kErpcStatus_ConnectionFailure Connecting to the specified host failed.
     */
    virtual erpc_status_t open();

    /*!
     * @brief This function disconnects client or stop server host.
     *
     * @retval #kErpcStatus_Success Always return this.
     */
    virtual erpc_status_t close();

protected:
    bool m_isServer;
    int32_t m_tcpSocket;
    uint16_t m_port;
    /*!
     * @brief This function read data.
     *
     * @param[inout] data Preallocated buffer for receiving data.
     * @param[in] size Size of data to read.
     *
     * @retval #kErpcStatus_Success When data was read successfully.
     * @retval #kErpcStatus_ReceiveFailed When reading data ends with error.
     * @retval #kErpcStatus_ConnectionClosed Peer closed the connection.
     */
    virtual erpc_status_t underlyingReceive(uint8_t *data, uint32_t size);

    /*!
     * @brief This function writes data.
     *
     * @param[in] data Buffer to send.
     * @param[in] size Size of data to send.
     *
     * @retval #kErpcStatus_Success When data was written successfully.
     * @retval #kErpcStatus_SendFailed When writing data ends with error.
     * @retval #kErpcStatus_ConnectionClosed Peer closed the connection.
     */
    virtual erpc_status_t underlyingSend(const uint8_t *data, uint32_t size);
};

}

#endif // KEIL_TCPTRANSPORT_H
