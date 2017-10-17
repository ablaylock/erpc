#ifndef KEIL_BSDTRANSPORT_H
#define KEIL_BSDTRANSPORT_H

#include "framed_transport.h"

namespace erpc {

class Keil_BSDTransport : public FramedTransport
{
public:
    Keil_BSDTransport(const int32_t tcpSock) : m_tcpSocket(tcpSock) {}

    /*!
     * @brief This function disconnects client or stop server host.
     *
     * @retval #kErpcStatus_Success Always return this.
     */
    virtual erpc_status_t close();

protected:
    int32_t m_tcpSocket;
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

#endif // KEIL_BSDTRANSPORT_H
